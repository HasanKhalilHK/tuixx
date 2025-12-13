#include <windows.h>
#include <string>

#include "widget.h"
#include "terminal.h"

int main(){
    // std::cout << "\x1b[?25l"; // make cursor invisible
    // std::cout << "\033]0;My Custom Title\007";

    Terminal mainTerminal;

    Label* bold = new Label("bold", true, false, 0, 0, RED);
    Label* bold_italic = new Label("bold and italic?", true, true, 0 ,1, GREEN);
    Label* italic = new Label("italic", false, true, 10 ,0, WHITE);

    mainTerminal.addWidget(bold);
    mainTerminal.addWidget(bold_italic);
    mainTerminal.addWidget(italic);


    while (true){    
        mainTerminal.render();
    }
    return 0;
}