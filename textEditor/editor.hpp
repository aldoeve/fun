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
        if (clearScreen() == static_cast<int>(DEFINES::ERROR))
            std::cerr << std::format("Failed to clean up screen.");
    }

    // Starts the editor.
    void start();

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

    //Branchless min function.
    int min(int a, int b) const noexcept {
        return a ^ ((b ^ a) & -(b < a));
    }

    //Adhoc way to clear the screen.
    int clearScreen() const noexcept {
        //Clears screen.
        int clear {static_cast<int>(write(STDOUT_FILENO, "\x1b[2J", static_cast<int>(DEFINES::CLEAR_SCREEN_BYTES)))};    
        //Repositions cursor.
        int reposition {static_cast<int>(write(STDOUT_FILENO, "\x1b[H", static_cast<int>(DEFINES::REPOSITION_BYTES)))};
        return min(clear, reposition); 
    }

    //Draws ~ on the left side like vim.
    int drawLines() const noexcept {
        int error {0};
        for(int i {0}; i < 24; ++i)
            error = static_cast<int>(write(STDOUT_FILENO, "~\r\n", static_cast<int>(DEFINES::REPOSITION_BYTES)));
        error = min(error, static_cast<int>(write(STDOUT_FILENO, "\x1b[H", static_cast<int>(DEFINES::REPOSITION_BYTES))));
        return error;
    }
};

#endif