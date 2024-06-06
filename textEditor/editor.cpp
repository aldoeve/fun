#include "editor.hpp"
#include <ctype.h>
#include <iostream>
#include <format>

void TextEditor::start() noexcept 
{
    enableRawMode();

    for(;;){
        c = '\0';
        if(read(STDIN_FILENO, &c, 1) == 0) break;
        if(iscntrl(c))
            std::cout << std::format("{}\r\n", c);
        else
            std::cout << std::format("{} ('{}')\r\n", static_cast<int>(c), c);
        if(c == 'q') break;
    }
    return;
}