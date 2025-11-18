#include <windows.h>
#include <vector>
#include <string>
#include <iostream>

#include "terminal.h"
#include "widget.h"

std::vector<std::vector<std::string>>& Terminal::getBuffer(){
    return buffer;
}

void Terminal::render(){

    DWORD num_read;
    INPUT_RECORD input_records[128];

    std::vector<std::vector<std::string>>& buffer = this->getBuffer();
    for(int i = 0; i < widgets.size(); i++){
        widgets[i]->render(buffer);
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < col; j++){
            
            
            COORD write_coords;
            write_coords.X = j;
            write_coords.Y = i;
            DWORD num_chars_written;
            const char* write = buffer[i][j].c_str();
            WriteConsoleOutputCharacter(h_out, write, 1, write_coords, &num_chars_written);
            
            
            //!old
            // printf("\x1b[%d;%dH", i+1, j+1); // move cursor to line # and column #
            // std::cout << buffer[i][j];

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

void Terminal::addWidget(Widget* widget){
    widgets.push_back(widget);
}

Terminal::Terminal(){
    
    HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE h_input = GetStdHandle(STD_INPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    
    GetConsoleScreenBufferInfo(h_out, &info);
    SHORT rows = info.dwSize.Y;
    SHORT col = info.dwSize.X;
    
    
    this->rows = info.dwSize.Y;
    this->col = info.dwSize.X;
    this->h_out = h_out;
    this->h_input = h_input;

    buffer.resize(rows);
    for (auto& row : buffer) {
        row.resize(col, ".");
    }


}

Terminal::~Terminal() {
    for (Widget* w : widgets) {
        delete w;  //free the memory
    }
}