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

    // std::cout << "\033]0;My Custom Title\007";

    Terminal mainTerminal;
    std::vector<std::vector<std::string>>& buffer = mainTerminal.getBuffer(); // main buffer we are using

    TextBox* bold = new TextBox("bold", true, false, 0, 0);
    TextBox* bold_italic = new TextBox("bold and italic?", true, true, 0 ,1);
    TextBox* italic = new TextBox("italic", false, true, 10 ,0);
    

    mainTerminal.addWidget(bold);
    mainTerminal.addWidget(bold_italic);
    mainTerminal.addWidget(italic);


    while (true){    
        mainTerminal.render();


    }
    return 0;
}