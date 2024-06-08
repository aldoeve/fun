#ifndef YATE
#define YATE
#include <format>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <utility>

#include "myDefines.hpp"

// Yet another simple terminal text editor.
class TextEditor {
public:
    // Creates the text editor object. Note that start() must be run to start the
    // editor.
    TextEditor() noexcept
        : c{'a'}, fatal{false}, originalTerminalState{currentTerminalState()} {;} 

    ~TextEditor() noexcept {
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalTerminalState) == static_cast<int>(DEFINES::ERROR) 
          || fatal)
          std::cerr << std::format("Failed to restore terminal defaults. Run [reset].\r\n");
    }

    // Starts the editor.
    void start() {
        // Change the terminal flags
        if (fatal) throw std::runtime_error{"tcgetattr() failed."};
        enableRawMode();
        if (fatal) throw std::runtime_error{"tcsetattr() failed."};
        // Core loop for the editor.
        for (;;) {
            if (clearScreen() == static_cast<int>(DEFINES::ERROR)) throw std::runtime_error{"Failed screen clear."};
            if (!processKeypress()) break;
        }
    }

private:
    char c;     // Data is read and stored here.
    bool fatal; // Used to check if any errors have been encountered that are fatal
    const termios originalTerminalState; // original state of the terminal before
                                         // the editor did anything.

    // Returns the current state of the terminal.
    termios currentTerminalState() noexcept {
        termios raw;
        fatal = tcgetattr(STDIN_FILENO, &raw) == static_cast<int>(DEFINES::ERROR)
                    ? true: false;
        return raw;
    }

    // Enables the proper flags on the terminal.
    void enableRawMode() noexcept;

    //Reads data from STDIN and saves it in c.
    void ReadKey();

    //Maps the keypress to one of the combos.
    bool processKeypress();

    //Adhoc way to clear the screen.
    int clearScreen() const {
        return static_cast<int>(write(STDOUT_FILENO, "\x1b[2J", static_cast<int>(DEFINES::CLEAR_SCREEN_BYTES)));    
    }
};

#endif