#ifndef YATE
#define YATE
#include <termios.h>
#include <unistd.h>
#include <utility>

//Yet another simple terminal text editor.
class TextEditor {
public:
    //Creates the text editor object. Note that start() must be run to start the editor.
    TextEditor() noexcept: error{false}, originalTerminalState{currentTerminalState()}
        {;}
    ~TextEditor() noexcept {tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalTerminalState);}
    //Starts the editor.
    void start() noexcept;
private:
    bool error; //Used to check if any errors have been encountered.
    char c;     //Data is read and stored here.
    const termios originalTerminalState; //original state of the terminal before the editor did anything.

    //Returns the current state of the terminal.
    termios currentTerminalState() const noexcept{
        termios raw;
        tcgetattr(STDIN_FILENO, &raw);
        return raw;
    }

    //Enables the proper flags on the terminal.
    void enableRawMode()const noexcept{
        termios changes{originalTerminalState};
        changes.c_iflag &= ~(IXON | ICRNL);
        changes.c_oflag &= ~(OPOST);
        changes.c_lflag &= ~(ECHO | ICANON | IEXTEN);
        changes.c_cc[VMIN] = 0;
        changes.c_cc[VTIME]= 1;
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &changes); 
    }
};

#endif