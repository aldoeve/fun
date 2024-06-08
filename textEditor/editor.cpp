#include <ctype.h>

#include "editor.hpp"

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