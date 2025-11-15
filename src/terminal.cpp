#include <windows.h>
#include <wincontypes.h>
#include <vector>
#include <string>
#include <iostream>

#include "terminal.h"

std::vector<std::vector<std::string>>& Terminal::getBuffer(){
    return buffer;
}

void Terminal::render(HANDLE h_input){
    DWORD num_read;
    INPUT_RECORD input_records[128];

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < col; j++){
            printf("\x1b[%d;%dH", i+1, j+1); // move cursor to line # and column #
            std::cout << buffer[i][j];

            //check if there is an event to resize terminal
            if (checkForEvents(h_input)){
                ReadConsoleInput(h_input, input_records, 128, &num_read);

                for(int i = 0; i < num_read; i++){
                    switch (input_records[i].EventType){
                        case WINDOW_BUFFER_SIZE_EVENT:{
                            int new_rows = input_records[i].Event.WindowBufferSizeEvent.dwSize.Y;
                            int new_col = input_records[i].Event.WindowBufferSizeEvent.dwSize.X;
                            this->resizeTerminal(new_rows, new_col);
                            // std::cout << "New x: " << input_records[i].Event.WindowBufferSizeEvent.dwSize.X << '\n';
                            // std::cout << "New y: " << input_records[i].Event.WindowBufferSizeEvent.dwSize.Y << '\n';
                            return;
                        }
                    }
                }
                
            }



        }
    }
}


bool Terminal::checkForEvents(HANDLE h_input){
    DWORD num_events;
    GetNumberOfConsoleInputEvents(h_input, &num_events);

    return num_events != 0;
}

void Terminal::resizeTerminal(int r, int c){
    this->rows = r;
    this->col = c;
    buffer.resize(r);
    for (auto& row : buffer) {
        row.resize(c, ".");
    }

    //clear terminal and clear scroll buffer respectively
    std::cout << "\x1b[2J";
    std::cout << "\x1b[3J";

}


Terminal::Terminal(int r, int c) : rows(r), col(c), buffer(r, std::vector<std::string>(c, ".")){}
