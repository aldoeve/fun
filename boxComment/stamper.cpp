//-----------------------------------------------------------------//
//  Developer: Aldo Vera-Espinoza                  ___     _______ //
//  Date: Tue May 21 15:43:52 2024                / \ \   / / ____|//
//                                               / _ \ \ / /|  _|  //
//  Project Name: Box-comment creator           / ___ \ V / | |___ //
//  Description:                               /_/   \_\_/  |_____|//
//    This program creates a simple box comment                    //
//   with a signiture for convinience.                             //
//-----------------------------------------------------------------//

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>

enum class State {
    IMAGE    = 0,
    NO_IMAGE = 1,
    FAIL     = 2, 
};

//Shows appropriate usage of the program.
inline void help() noexcept {
    std::string_view usage{
        "\nUsage:\t./stamper.out [Option...] <CommentStr>\n\n"
    };
    std::string_view noImageOption{
        "\t-n\t\tOutputs only the box comment.\n"
    };
    std::string_view helpOption   {
        "\t-h or --help    Outputs usage message.\n"
    };
    std::cout << usage << noImageOption << helpOption << std::endl;
    return;
}

//Prints a simple box comment. The name is hard coded, but
//it can be changed for anyone else.
inline void boxComment(std::string_view comment) noexcept{
    const int width  {65};
    const int offset {2};
    const int signatureWidth  {20};
    const int projectNameSize {29};
    const std::time_t now         {std::time(0)};
    std::string_view  horizontal  {"-"};
    std::string_view  vertical    {"|"};
    std::string       name        {"Aldo Vera-Espinoza"};
    std::string       projectName {};
    std::string       desc        {};
    std::string       nowStr      {static_cast<std::string>(ctime(&now))};
    
    //Keep this to 5 lines
    std::vector<std::string_view> initals {
        "    ___     _______ ",
        "   / \\ \\   / / ____|",
        "  / _ \\ \\ / /|  _|  ",
        " / ___ \\ V / | |___ ",
        "/_/   \\_\\_/  |_____|",
    };

    std::cout << "Input project name: ";
    std::getline(std::cin, projectName);
    std::cout << "\nInput project description: ";
    std::getline(std::cin, desc);
    std::cout << std::endl;
    //Remember to do a resize if your name is larger like the next line.
    //The reason why it is a string is to allow for future modification.
    projectName.resize(projectNameSize, ' ');
    nowStr.pop_back();

    //Does the horizontal sides of a box comment.
    auto horizontalSides = [&comment, horizontal]{
        std::cout << comment;
        for(short int i{0}; i < width; ++i)
            std::cout << horizontal;
        std::cout << comment << std::endl;
    };

    //Formats the first 5 lines of the box comment
    auto lineFormatWithSigniture = [width, &initals, &comment, signatureWidth, offset](const int index,std::string_view field){
        std::cout << comment << "  " << std::setw(width-signatureWidth - offset) << std::setfill(' ') << std::left << field;
        std::cout << std::setw(signatureWidth) << std::right << std::setfill('8') << initals[index] << comment;
        std::cout << std::endl;
    };

    horizontalSides();
    
    int currentLine {0};
    lineFormatWithSigniture(currentLine++, "Developer: " + name);
    lineFormatWithSigniture(currentLine++, "Date: " + nowStr);
    lineFormatWithSigniture(currentLine++, "");
    lineFormatWithSigniture(currentLine++, "Project Name: " + projectName);
    lineFormatWithSigniture(currentLine, "Description: ");


    //Description text that is able to wrap around.
    desc.insert(0, "  ");
    const int cutoff {width - 15};
    std::string buffer {};
    
    for(unsigned long int i{0}; i < desc.size(); ++i){
        if(buffer.size() % cutoff == 0 && !buffer.empty()){
            std::cout << std::setw(cutoff) << std::setfill(' ') << std::left << buffer;
            if(comment.size() > 1)
                for(unsigned long int j{0}; j < comment.size(); ++j) std::cout << ' ';
            std::cout << std::setw(width - cutoff + offset) << std::setfill(' ') << std::right << comment;
            std::cout << std::endl;
            buffer.clear();
        }
        if(buffer.empty()){
            buffer += comment;
            buffer += "  ";
        }
        buffer += desc[i];
    }

    if(!buffer.empty()){
        std::cout << std::setw(cutoff) << std::setfill(' ') << std::left << buffer;
        if(comment.size() > 1)
            for(unsigned long int i{0}; i < comment.size(); ++i) std::cout << ' ';
        std::cout << std::setw(width - cutoff + offset) << std::setfill(' ') << std::right << comment;
        std::cout << std::endl;
    }
    

    horizontalSides();

    return;
}

//Prints an image of smug Pekora.
inline void image(std::string_view comment) noexcept {
    //Hard coded because I do not want another file to keep track of.
    std::vector<const char*> image {
        "⠀⠀⠀⠀⠀⡆⠀⠀⠀⢲⠀⠀⠹⡄⠀⠀⠀⠀⠀⠀⠀⠀⢰⠀⠀⠀⠀⡞⠀⠐⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠸⡀⠀⠀⠀⢣⡀⠀⠱⡄⠀⠀⠀⠀⠀⠀⠀⢸⡓⠛⠳⠺⣇⠀⠀⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠑⢄⠀⠀⢀⣷⣄⡀⠘⢦⣀⣠⡴⠶⠚⠛⠛⠃⠒⠒⠒⠚⠦⢀⣻⡉⠉⠉⠑⠒⠢⠤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⣶⢒⢲⡄⠀⠙⠺⣯⣡⢤⡚⠋⠉⠉⠐⠒⠉⠉⠓⠒⠢⠄⣀⠀⠀⠀⠀⠈⠑⠦⡀⠀⠀⠀⠀⠀⠉⠒⢤⡀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠈⠣⣀⡷⠀⣠⣾⠟⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠑⠂⢀⠀⠀⠀⠀⠑⢄⠀⠀⠀⠀⠀⠀⠈⠑⢄⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠁⢠⣾⠏⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠒⢄⠀⠀⠀⠑⢆⠀⠀⠀⠀⠀⠀⠀⠙⢄⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⡰⡷⠁⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢄⠀⠀⠀⠳⡀⠀⠀⠀⠀⠀⠀⠈⠳⡀⠀⠀",
        "⠀⠀⠀⢀⣼⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠱⡀⠀⠀⠱⡀⠀⠀⠀⠀⠀⠀⠀⠑⡄⠀",
        "⠀⠀⢀⣞⡎⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣄⠀⠀⠱⡀⠀⠀⠀⠀⠀⠀⠀⠘⣄",
        "⠀⠀⡜⡞⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢆⠀⠀⢳⡀⠀⠀⠀⠀⠀⠀⠠⡸",
        "⠀⣰⠱⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢳⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡆⠀⠈⣷⠀⠀⠀⠀⠀⠀⠀⠘",
        "⢠⠇⡆⠀⠀⠀⢠⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠸⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀⠀⠀⢹⡀⠀⢹⡆⠀⠀⠀⠀⠀⢄⠀",
        "⡼⢰⠀⠀⠀⠀⡞⠀⠀⠀⠀⠀⠀⣿⡀⡄⠀⠀⠀⢠⣀⠀⡏⢣⡀⠀⠀⠀⠀⢳⡀⠀⠀⠀⠸⡄⠀⠀⠀⠀⣇⠀⠀⣷⠀⠀⠀⠀⠀⠀⠙",
        "⠣⡇⠀⠀⠀⢠⡇⠀⠀⠀⢰⠂⠀⡏⣇⣷⠀⠀⠀⠈⢯⠉⢻⠒⠳⡄⠀⠀⠀⠀⢳⠀⠀⠀⠀⣇⠀⠀⠀⠀⢸⠀⠀⢻⡄⠀⠀⠀⠀⠀⠀",
        "⠀⠃⠀⠀⠀⢸⠇⠀⠀⠀⢸⠀⢸⡧⢏⢹⡀⠀⠀⠀⠀⠑⠺⡇⠊⠘⢢⠀⠀⠀⠈⣧⡀⠀⠀⢸⠀⠀⠀⠀⢸⡅⠀⢸⡇⠀⠀⠀⠀⠀⠀",
        "⠠⠀⠀⠀⠀⢸⠇⠀⠀⠀⣾⠀⡿⠄⢼⠾⢧⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠑⢤⡀⠀⠸⡳⡀⠀⢸⠀⠀⠀⠀⢸⡄⠀⠈⣷⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⡀⠀⠸⡇⠀⠀⢀⡗⣰⠁⠀⠀⢣⡌⢢⡀⠀⠀⠀⠀⡇⠀⣰⣂⣀⣀⣭⣶⣤⣷⣿⣄⠘⡆⠀⠀⠀⢸⠆⠀⠀⣿⣤⣤⣤⢶⠾⠷",
        "⠀⠀⠰⣧⠀⠀⣇⠀⠀⣼⣷⠃⠀⠀⣀⣠⣿⡀⠑⢄⡀⠀⠀⡇⠀⠙⠿⣿⣿⡿⣿⣿⣿⡆⠈⢲⡇⠀⠀⠀⣼⠀⠀⠀⣿⣧⣐⣤⣮⣼⣷",
        "⢸⠀⠀⣿⡀⠀⢿⠀⣰⣿⣧⣶⣶⣿⣿⣯⠀⠁⠀⠀⠈⠢⢄⡇⠀⠀⢰⡾⠟⠷⠟⠛⣻⠃⠀⢰⠃⠀⠀⣰⡇⠀⠀⠀⣏⣿⡿⢟⢻⣿⣋",
        "⢸⡆⠀⢿⣧⠀⢸⣦⠟⠛⠛⣿⣏⣻⠿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠒⠒⠒⠋⠁⠀⠀⡸⠀⢀⣴⡟⠀⠀⠀⠀⣿⡟⣡⡼⠋⣠⠟",
        "⠨⣇⠀⠘⣿⣦⠀⢿⡀⠀⠺⣟⣉⣉⠴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⢰⡅⠔⠋⣿⠀⠀⠀⠀⠀⣿⡼⠋⠀⢸⣁⠀",
        "⡇⢹⡀⠀⢻⣿⣧⡈⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⠛⠛⢦⠀⠀⠀⠀⠀⠀⠀⣟⠀⠀⠀⠀⠀⡿⠛⠢⣄⠀⠉⣿",
        "⣷⠀⢧⠀⠘⣿⡸⢿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠴⡪⠃⠀⠀⠈⡇⠀⠀⠀⠀⢀⣴⣯⠀⠀⠀⠀⣸⡇⠀⠀⠈⢣⢸⠇",
        "⣿⡄⠈⣧⡀⢸⡇⣹⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠠⡦⠴⠖⠮⠭⠒⠉⠀⠀⠀⢀⡼⠁⠀⠀⣠⣴⣿⡛⡧⠀⠀⠀⠀⣿⠃⠀⠀⠀⠀⠼⣇", 
        "⠙⢳⡀⢸⡙⠲⢷⣸⣿⡷⠦⣀⡀⠀⠀⠀⠀⠀⠀⠳⢄⡀⠀⠀⠀⣀⣀⡠⠔⠋⣀⣠⡴⠛⠉⠀⠀⠉⡧⠀⠀⠀⢸⣿⠀⠀⠀⠀⠀⠠⡟",
        "⠀⠀⠁⠘⣇⠀⠀⠙⣿⡅⢠⡟⠉⠙⠓⠒⠦⠤⠤⠤⣤⡬⣭⣭⣭⠬⠴⡒⢚⡿⠛⠉⠀⠀⠀⠀⠀⠀⡗⠀⠀⠀⢸⡏⠀⠀⠀⠀⠀⠀⠘",
    };

    for(const auto & i: image){
        std::cout << comment << i << std::endl;
    }

    return;
}

int main(int argc, char* argv[]) {
    State nextStep {State::IMAGE};
    std::string comment {"#"};

    //Resolves what flags or input was given to the program.
    if (argc > 3) nextStep = State::FAIL;

    for(int i {1}; nextStep != State::FAIL && i < argc; ++i){
        std::string_view cmdOption {static_cast<std::string_view>(argv[i])};
        if (cmdOption.compare("-n") == 0)
            nextStep = State::NO_IMAGE;
        else
            comment = cmdOption;
    }

    //Decides how to format the output.
    if(nextStep != State::FAIL){
        boxComment(comment);
        std::cout << "\n\n" << std::endl;
        if (nextStep == State::IMAGE) {
            image(comment);
            std::cout << std::endl;
        }
    }
    else
        help();

    return 0;
}