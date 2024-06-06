#include <ctype.h>

#include "editor.hpp"

void TextEditor::start()
{
    int readErr{0};
    //Change the terminal flags
    if(fatal) throw std::runtime_error{"tcgetattr() failed."};
    enableRawMode();
    if(fatal) throw std::runtime_error{"tcsetattr() failed."};

    //Core loop for the editor.
    for(;!fatal;){
        c = '\0';
        readErr = static_cast<int>(read(STDIN_FILENO, &c, static_cast<int>(DEFINES::NUM_BYTES)));    
        if(readErr == static_cast<int>(DEFINES::DONE)) break;
        else if(readErr == static_cast<int>(DEFINES::ERROR)){
            throw std::runtime_error{"Failed to properly read from STDIN\r\n"};
        }
        if(iscntrl(c))
            std::cout << std::format("{}\r\n", c);
        else
            std::cout << std::format("{} ('{}')\r\n", static_cast<int>(c), c);
        if(c == static_cast<char>(KEY_COMBO::CTRL_Q)) break;
    }
}