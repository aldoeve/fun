#ifndef YATE
#define YATE
#include <termios.h>
#include <unistd.h>
#include <utility>
#include <iostream>
#include <format>

#include "myDefines.hpp"

//Yet another simple terminal text editor.
class TextEditor {
public:
    //Creates the text editor object. Note that start() must be run to start the editor.
    TextEditor() noexcept: fatal{false}, originalTerminalState{currentTerminalState()}{;}

    ~TextEditor() noexcept {
        if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalTerminalState) == static_cast<int>(DEFINES::ERROR) ||
            fatal)
            std::cerr << std::format("Failed to restore terminal defaults. Run [reset].\r\n");
        }
    //Starts the editor and returns int where 1 is failure.
    void start();
private:
    char c;     //Data is read and stored here.
    bool fatal; //Used to check if any errors have been encountered that are unrecoverable.
    const termios originalTerminalState; //original state of the terminal before the editor did anything.

    //Returns the current state of the terminal.
    termios currentTerminalState() noexcept{
        termios raw;
        fatal = tcgetattr(STDIN_FILENO, &raw) == static_cast<int>(DEFINES::ERROR) ? true : false;
        return raw;
    }

    //Enables the proper flags on the terminal.
    void enableRawMode() noexcept{
        termios changes{originalTerminalState};
        changes.c_iflag &= ~(IXON | ICRNL);
        changes.c_oflag &= ~(OPOST);
        changes.c_lflag &= ~(ECHO | ICANON | IEXTEN);
        changes.c_cc[VMIN] = static_cast<int>(DEFINES::MY_VMIN);
        changes.c_cc[VTIME]= static_cast<int>(DEFINES::MY_VTIME);
        fatal = tcsetattr(STDIN_FILENO, TCSAFLUSH, &changes) == static_cast<int>(DEFINES::ERROR) ? true : false; 
    }
};

#endif