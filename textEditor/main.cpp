#include "editor.hpp"
#include <format>
#include <iostream>

int main() 
{
    //need to work on error handeling for this simple model.
    std::cout << std::format("[ctrl] + [c] still works to exit by force") << std::endl;
    TextEditor editor{};
    editor.start();
    return 0;
}