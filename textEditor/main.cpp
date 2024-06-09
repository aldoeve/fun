#include <format>
#include <iostream>
#include <string>
#include <thread>

#include "editor.hpp"

TerminalTOStr interpret{};

//Thinking of changing this to a more complex object that yeilds itself to inheritance.
void sanityCheck(int wait) noexcept {
    std::cout << std::format("Sanity checks [.]") << std::flush;
    sleep(wait);
    std::cout << std::format("\b\b") << std::flush;
    #ifdef __linux__
    std::cout << std::format("✓") << std::flush;
    #else
    std::cout << std::format("x") << std::flush;
    #endif
    return;
}

int main() 
{
    std::cout << std::format("[ctrl] + [c] still works to exit by force.") << std::endl;
    std::cout << std::format("[ctrl] + [q] to cleanly quit the program.") << std::endl;
    
    std::thread checks {sanityCheck, 1};
    
    sleep(5);
    checks.join();

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