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
    std::cout << rows << " " << col << '\n';

    //30 rows 120 col






    // std::cout << "\033]0;My Custom Title\007";

    Terminal main(rows, col);
    std::vector<std::vector<std::string>>& buffer = main.getBuffer(); // main buffer we are using

    TextBox bold("bold", true, false, 0 ,0);
    TextBox bold_italic("bold and italic?", true, true, 0 ,1);
    TextBox italic("italic", false, true, 10 ,0);
    
    bold.render(buffer);
    bold_italic.render(buffer);
    italic.render(buffer);
    
    DWORD num_events;
    DWORD num_read;
    INPUT_RECORD input_records[128];
    
    int counter = 0;
    while (true){    
        main.render(h_input);
        
        /*if (num_events != 0){
            std::cout << '\n';
            ReadConsoleInput(h_input, input_records, 128, &num_read);
            // std::cout << "Error: " << GetLastError() << '\n';
            // std::cout << "Size of read buffer: " << num_read << '\n';
            
            for(int i = 0; i < num_read; i++){
    
                switch (input_records[i].EventType){
                    case WINDOW_BUFFER_SIZE_EVENT:{
                        int new_rows = input_records[i].Event.WindowBufferSizeEvent.dwSize.Y;
                        int new_col = input_records[i].Event.WindowBufferSizeEvent.dwSize.X;
                        main.resizeTerminal(new_rows, new_col);
                        // std::cout << "New x: " << input_records[i].Event.WindowBufferSizeEvent.dwSize.X << '\n';
                        // std::cout << "New y: " << input_records[i].Event.WindowBufferSizeEvent.dwSize.Y << '\n';
                        break;
                    }
    
                    case KEY_EVENT:
                        // std::cout << "Ireelevant input \n";
                        break;
                    case MOUSE_EVENT:
                        // std::cout << "Ireelevant input \n";
                        break; 
                    case FOCUS_EVENT:
                        // std::cout << "Ireelevant input \n";
                        break;  
                    case MENU_EVENT:  
                        // std::cout << "Ireelevant input \n";
                        break;
    
                    default:
                        break;
                }
            }
        }*/


    }
    return 0;
}