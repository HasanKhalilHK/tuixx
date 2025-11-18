#include <windows.h>
#include <minwindef.h>
#include <consoleapi.h>
#include <consoleapi3.h>
#include <iostream>
#include <string>
#include <vector>

#include <wincontypes.h>
#include <wincon.h>
#include <errhandlingapi.h>
#include <consoleapi2.h>

#include "widget.h"
#include "terminal.h"

int main(){
    // std::cout << "\x1b[?25l"; // make cursor invisible
    
    
    //get dimensions
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE h_input = GetStdHandle(STD_INPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(h, &info);
    int rows = info.dwSize.Y;
    int col = info.dwSize.X;


    // std::cout << "\033]0;My Custom Title\007";

    Terminal main(rows, col);
    std::vector<std::vector<std::string>>& buffer = main.getBuffer(); // main buffer we are using

    TextBox* bold = new TextBox("bold", true, false, 0, 0);
    TextBox* bold_italic = new TextBox("bold and italic?", true, true, 0 ,1);
    TextBox* italic = new TextBox("italic", false, true, 10 ,0);
    

    main.addWidget(bold);
    main.addWidget(bold_italic);
    main.addWidget(italic);


    int counter = 0;
    while (true){    
        main.render(h_input);


    }
    return 0;
}