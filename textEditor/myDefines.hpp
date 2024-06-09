#ifndef MY_DEFINES
#define MY_DEFINES

//Normal defines over #define to improve code readability.
enum class DEFINES {
    ERROR = -1,
    MY_VMIN = 0,
    MY_VTIME = 60,
    NUM_BYTES = 1,
    DONE = 0,
    VERSION = 0,
};

//Terminal escape sequences. They are strings.
enum class TERMINAL {
    CLEARS_WHOLE_SCREEN,
    CLEAR_ROW,
    HIDE_CUROSR,
    SHOW_CURSOR,
    REPOSITION_CUROSR,
    NEW_LINE,
};

//Singleton to help stringify the TERMINAL enum.
class TerminalTOStr {
public:
    TerminalTOStr()  = default;
    ~TerminalTOStr() = default;
    //Stringification
    std::string str(TERMINAL a)const noexcept {
        switch (a)
        {
        case TERMINAL::CLEARS_WHOLE_SCREEN :
            return "\x1b[2J";
        case TERMINAL::CLEAR_ROW :
            return "\x1b[K";
        case TERMINAL::HIDE_CUROSR :
            return "\x1b[?25l";
        case TERMINAL::SHOW_CURSOR :
            return "\x1b[?25h";
        case TERMINAL::REPOSITION_CUROSR :
            return "\x1b[H";
        case TERMINAL::NEW_LINE :
            return "\r\n";
        default:
            return "";
        }
    }
};

//Key combinations to look for.
enum class KEY_COMBO {
    CTRL_Q = (('Q') & 0x1f)
};

#endif