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
        std::vector<std::vector<std::string>> buffer;
        std::vector<Widget*> widgets;

        bool checkForEvents(HANDLE h_input);
    
    public:
        std::vector<std::vector<std::string>>& getBuffer();
        void resizeTerminal(int r, int c);

        void addWidget(Widget* widget);
        void render();

        
        std::string getInHandle();
        std::string getOutHandle();

        Terminal();
        ~Terminal();

};

#endif //TERMINAL_H