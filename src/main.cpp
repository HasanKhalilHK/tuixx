#include <windows.h>
#include <string>

#include "container.h"
#include "widget.h"
#include "terminal.h"

int main(){
    // std::cout << "\x1b[?25l"; // make cursor invisible
    // std::cout << "\033]0;My Custom Title\007";

    Terminal mainTerminal(FlexDirection::Column);

    Label* label1 = new Label("label1", true, false, RED);
    Label* label2 = new Label("label 2", true, true, GREEN);
    Label* label3 = new Label("label three", false, true, WHITE);

    Flex* button_container = new Flex(FlexDirection::Row);
    Label* b1 = new Label("b1", true, false, RED);
    Label* b2 = new Label("button 2", true, true, GREEN);
    Label* b3 = new Label("butt3", false, true, WHITE);
    button_container->addWidget(b1);
    button_container->addWidget(b2);
    button_container->addWidget(b3);

    mainTerminal.addWidget(label1);
    mainTerminal.addWidget(label2);
    mainTerminal.addWidget(label3);
    mainTerminal.addWidget(button_container);


    while (true){    
        mainTerminal.render();
    }
    return 0;
}