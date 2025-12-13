#include <windows.h>
#include <vector>
#include <iostream>

#include "terminal.h"
#include "widget.h"


void Terminal::render(){

    
    for(int i = 0; i < widgets.size(); i++){
        widgets[i]->render(char_buf_vec);
    }
    
    const int buf_size = rows*col;
    COORD bufferSize;
    bufferSize.X = col;
    bufferSize.Y = rows;
    COORD bufferCoord;
    bufferCoord.X = 0;
    bufferCoord.Y = 0;
    SMALL_RECT writeRegion;
    writeRegion.Left = 0;
    writeRegion.Top = 0;
    writeRegion.Right = bufferSize.X - 1;
    writeRegion.Bottom = bufferSize.Y - 1;
    
    CHAR_INFO char_buf[buf_size];
    

    for(int i = 0; i < char_buf_vec.size(); i++){
        for(int j = 0; j < char_buf_vec[0].size(); j++){
            char_buf[i*col+j] = char_buf_vec[i][j];
        }
    }


    WriteConsoleOutput(h_out, char_buf, bufferSize, bufferCoord, &writeRegion);
  
    

    //resize terminal when a resize event is detected
    DWORD num_read;
    INPUT_RECORD input_records[128];
    if (checkForEvents(h_input)){
        ReadConsoleInput(h_input, input_records, 128, &num_read);

        for(int i = 0; i < num_read; i++){
            switch (input_records[i].EventType){
                case WINDOW_BUFFER_SIZE_EVENT:{
                    int new_rows = input_records[i].Event.WindowBufferSizeEvent.dwSize.Y;
                    int new_col = input_records[i].Event.WindowBufferSizeEvent.dwSize.X;
                    this->resizeTerminal(new_rows, new_col);
                    return;
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

    char_buf_vec.clear();
    for(int i = 0; i < r; i++){
        std::vector<CHAR_INFO> row;
        for(int j = 0; j < c; j++){
            CHAR_INFO placeholder;
            placeholder.Char.AsciiChar = '*';
            placeholder.Attributes = BLUE;
            row.push_back(placeholder);
        }
        // std::cout << row.size() << '\n';
        char_buf_vec.push_back(row);
        row.clear();
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

    //clear terminal and clear scroll buffer respectively
    std::cout << "\x1b[2J";
    std::cout << "\x1b[3J";

    resizeTerminal(rows,col);



}

Terminal::~Terminal() {
    for (Widget* w : widgets) {
        delete w;  //free the memory
    }
}