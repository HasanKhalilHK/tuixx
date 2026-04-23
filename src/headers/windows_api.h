#pragma once
#ifdef _WIN32
    #ifdef BUILDING_DLL
        #define TUI_DLL __declspec(dllexport)
    #else
        #define TUI_DLL __declspec(dllimport)
    #endif
#else
    #define TUI_DLL __attribute__((visibility("default")))
#endif