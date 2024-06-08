#include <format>
#include <iostream>
#include <string>

#include "editor.hpp"

int main() 
{
    std::cout << std::format("[ctrl] + [c] still works to exit by force.") << std::endl;
    std::cout << std::format("[ctrl] + [q] to cleanly quit the program.") << std::endl;
    std::cout << std::format("Starting") << std::flush;

    for (unsigned int i{0}; i < 12; ++i){
        if (i  == 6) std::cout << std::format("\b\b\b\b\b\b") << std::flush;
        if (i < 6) std::cout << std::format(".") << std::flush;
        if (i >= 6) std::cout << std::format("=") << std::flush;
        sleep(1);
    }

    TextEditor editor{};
    try{
        editor.start();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what();
        return 1;
    }

    return 0;
}