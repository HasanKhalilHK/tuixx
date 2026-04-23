#ifndef TERMINAL_H
#define TERMINAL_H


#include <vector>
#include "container.h"
#include "style.h"

class Widget;
class TUI_DLL Terminal {
    private:
    
    #ifdef _WIN32
    CHAR_INFO* char_buf;
    HANDLE h_out;
    HANDLE h_input;
    bool checkForEvents();

    #else
    
    Cell* char_buf;
    inline static bool resize_pending = false;
    inline static bool handle_initialized = false;
    static void resize_handler(int){resize_pending = true;};
    #endif
    
    ContainerType container_type;
    std::vector<Container*> containers;
    int rows;
    int cols;
    Colour background_colour;
    
    void handleResize();
    
public:
    Terminal(Colour background_colour, ContainerType container_type);
    ~Terminal();
    
    void addContainer(Container* container);
    void render();
};


#endif // TERMINAL_H