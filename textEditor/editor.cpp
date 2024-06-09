#include <ctype.h>

#include "editor.hpp"

TextEditor::~TextEditor() noexcept {
    buffer.clear();
    clearScreen(false);
    buffer += interpret.str(TERMINAL::SHOW_CURSOR);
    if(write(STDOUT_FILENO, buffer.c_str(), buffer.size()) == static_cast<int>(DEFINES::ERROR))
        std::cerr << std::format("Failed to clear screen.{}", interpret.str(TERMINAL::NEW_LINE));
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalTerminalState) == static_cast<int>(DEFINES::ERROR) || fatal)
        std::cerr << std::format("Failed to restore terminal defaults. Run [reset].{}", interpret.str(TERMINAL::NEW_LINE));
}

void TextEditor::start() {
    // Change the terminal flags
    if (fatal) throw std::runtime_error{"tcgetattr() failed."};
    enableRawMode();
    if (fatal) throw std::runtime_error{"tcsetattr() failed."};
    // Core loop for the editor.
    for (;;) {
        if (refreshScreen() == static_cast<int>(DEFINES::ERROR)) throw std::runtime_error{"Failed drawing to screen."};
        if (!processKeypress()) break;
    }
}

void TextEditor::enableRawMode() noexcept {
    termios changes{originalTerminalState};
    changes.c_iflag &= ~(IXON | ICRNL);
    changes.c_oflag &= ~(OPOST);
    changes.c_lflag &= ~(ECHO | ICANON | IEXTEN);
    changes.c_cc[VMIN] = static_cast<int>(DEFINES::MY_VMIN);
    changes.c_cc[VTIME] = static_cast<int>(DEFINES::MY_VTIME);
    fatal = tcsetattr(STDIN_FILENO, TCSAFLUSH, &changes) ==
            static_cast<int>(DEFINES::ERROR) ? true : false;
}

void TextEditor::ReadKey() {
    int nRead{0};
    //Reads a singular keypress.
    while ((nRead = static_cast<int>(read(STDIN_FILENO, &c, static_cast<int>(DEFINES::NUM_BYTES)))) 
            != static_cast<int>(DEFINES::NUM_BYTES)){
        if (nRead == static_cast<int>(DEFINES::ERROR) && errno != EAGAIN) 
            throw std::runtime_error("Failed to read from input.");
    }
    return;
}

bool TextEditor::processKeypress() {
    ReadKey();

    switch (c)
    {
        case static_cast<int>(KEY_COMBO::CTRL_Q):
            return false;
        default:
            return true;
    }
}

void TextEditor::drawLines() noexcept {
    for(int i {0}; i < rows; ++i){
        buffer += "~";
        buffer += interpret.str(TERMINAL::CLEAR_ROW);
        if(i < rows - 1) 
            buffer += interpret.str(TERMINAL::NEW_LINE);
    }
    buffer += interpret.str(TERMINAL::REPOSITION_CUROSR);
    buffer += interpret.str(TERMINAL::SHOW_CURSOR);
    return;
}

DEFINES TextEditor::getWindowSize() noexcept {
    winsize ws {};
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == static_cast<int>(DEFINES::ERROR)
        || ws.ws_col < 1) 
        return DEFINES::ERROR;
    else{
        cols = ws.ws_col;
        rows = ws.ws_row;
    }
    return DEFINES::DONE;
}
