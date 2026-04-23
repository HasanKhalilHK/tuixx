#ifndef STYLE_H
#define STYLE_H


#ifdef _WIN32
#include <windows.h>

    
    #ifdef BUILDING_DLL
        #define TUI_DLL __declspec(dllexport)
    #else
        #define TUI_DLL __declspec(dllimport)
    #endif
    typedef WORD Colour;
#else
    #define TUI_DLL __attribute__((visibility("default")))
    #include <string>
    typedef std::string Colour;
#endif

namespace Colours{
    #ifdef _WIN32
    inline Colour FG_RED = FOREGROUND_RED;
    inline Colour FG_BLUE = FOREGROUND_BLUE;
    inline Colour FG_GREEN = FOREGROUND_GREEN;
    inline Colour FG_WHITE = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
    
    inline Colour BG_RED = BACKGROUND_RED;
    inline Colour BG_BLUE = BACKGROUND_BLUE;
    inline Colour BG_GREEN = BACKGROUND_GREEN;
    inline Colour BG_WHITE = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN;
    #else
    inline Colour FG_RED = "\033[31m";
    inline Colour FG_BLUE = "\033[34m";
    inline Colour FG_GREEN = "\033[32m";
    
    #endif
    
}

enum Align{
    NONE,
    CENTER,
    RIGHT,
    LEFT
};

enum ContainerType { FLEX_ROW, FLEX_COL };

struct TUI_DLL Style{
    int width, height;
    Align align;
    ContainerType container_type;
};


#endif