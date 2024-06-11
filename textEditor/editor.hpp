#ifndef YATE
#define YATE
#include <format>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <utility>
#include <sys/ioctl.h>

#include "myDefines.hpp"
extern TerminalTOStr interpret;

// Yet another simple terminal text editor.
class TextEditor {
public:
    // Creates the text editor object. Note that start() must be run to start the
    // editor.
    TextEditor() noexcept
        : c{'a'}, fatal{false},rows{0}, cols{0}, buffer{}, originalTerminalState{currentTerminalState()} {
            fatal = getWindowSize() == DEFINES::ERROR ? true : false;
        } 

    ~TextEditor() noexcept;

    // Starts the editor.
    void start();

private:
    char c;     // Data is read and stored here.
    bool fatal; // Used to check if any errors have been encountered that are fatal.
    int  rows;  // The number of rows of the terminal.
    int  cols;  // The number of cols of the terminal.
    std::pair<int, int> coursorLocation {1 , 1}; //Location of the users coursor. (x, y). Same start index as terminal.
    std::string buffer; //Buffer to avoid constantly using write().
    std::string_view welcomeMesssage {"YET ANOTHER TEXT EDITOR VER. 0.0.1"}; //Welcome message.
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

    void boundCoursor() noexcept {
        int& x = coursorLocation.first;
        int& y = coursorLocation.second;
        if (x == 0) x = 1;
        else if (x > cols) x = cols;
        if (y == 0) y = 1;
        else if (y > rows) y = rows;
        return;
    }

    void moveCoursor() noexcept {
        switch (c)
        {
        case 'w':
            coursorLocation.second -= 1;
            break;
        case 'a':
            coursorLocation.first -= 1;
            break;
        case 's':
            coursorLocation.second += 1;
            break;
        case 'd':
            coursorLocation.first += 1;
            break;
        default:
            break;
        }
        boundCoursor();
    }

    //Uses a given integer to add padding and center.
    void center(const int a) noexcept {
        int padding {(cols - a) / 2};
        while (padding--) buffer += " ";
    }

    //Clears screen and draws what it needs to.
    int refreshScreen() noexcept {
        int error {static_cast<int>(DEFINES::DONE)};
        clearScreen();
        drawLines();
        fixCursor();
        error = static_cast<int>(write(STDOUT_FILENO, buffer.c_str(), buffer.size()));
        buffer.clear();
        return error;
    }

    //Repositions coursor to where it is suppose to be.
    void fixCursor() noexcept {
        buffer += interpret.str(TERMINAL::REPOSITION_Y);
        buffer += std::to_string(coursorLocation.second);
        buffer += interpret.str(TERMINAL::REPOSITION_AT);
        buffer += std::to_string(coursorLocation.first);
        buffer += interpret.str(TERMINAL::REPOSITION_X_END);
        return;
    }

    //Adhoc way to clear the screen.
    void clearScreen(bool hideCursor=true) noexcept {
        if(hideCursor)
            buffer += interpret.str(TERMINAL::HIDE_CUROSR);
        buffer += interpret.str(TERMINAL::CLEARS_WHOLE_SCREEN);
        buffer += interpret.str(TERMINAL::REPOSITION_CUROSR_AT_TOP);
        return; 
    }

    //Draws ~ on the left side like vim.
    void drawLines() noexcept;

    //Retrives the size of the terminal and returns DEFINES::ERROR on failure.
    DEFINES getWindowSize() noexcept;
};

#endif