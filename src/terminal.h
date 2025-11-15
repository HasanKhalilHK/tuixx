#ifndef TERMINAL_H
#define TERMINAL_H

#include <windows.h>
#include <vector>
#include <string>

class Terminal{
    private:
        int rows;
        int col;
        std::vector<std::vector<std::string>> buffer;

        bool checkForEvents(HANDLE h_input);
    
    public:
        std::vector<std::vector<std::string>>& getBuffer();
        void resizeTerminal(int r, int c);

        
        void render(HANDLE h_input);

        Terminal(int r, int c);

};

#endif //TERMINAL_H