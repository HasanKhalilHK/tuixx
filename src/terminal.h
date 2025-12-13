#ifndef TERMINAL_H
#define TERMINAL_H

#include <windows.h>
#include <vector>
#include <string>

class Widget;

class Terminal{
    private:
        HANDLE h_out, h_input;
        SHORT rows;
        SHORT col;
        std::vector<Widget*> widgets;
        std::vector<std::vector<CHAR_INFO>> char_buf_vec;

        bool checkForEvents(HANDLE h_input);
    
    public:
        void resizeTerminal(int r, int c);

        void addWidget(Widget* widget);
        void render();

        
        std::string getInHandle();
        std::string getOutHandle();

        Terminal();
        ~Terminal();

};

#endif //TERMINAL_H