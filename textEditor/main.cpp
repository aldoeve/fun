#include <format>
#include <iostream>

#include "editor.hpp"

int main() 
{
    //need to work on error handeling for this simple model.
    std::cout << std::format("[ctrl] + [c] still works to exit by force") << std::endl;
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