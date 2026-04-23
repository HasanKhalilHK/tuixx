#include "../headers/terminal.h"
#include "../headers/container.h"
#include <consoleapi2.h>
#include <iostream>

Terminal::Terminal(Colour background_colour, ContainerType container_type) {
    
    this->h_out = GetStdHandle(STD_OUTPUT_HANDLE);
    this->h_input = GetStdHandle(STD_INPUT_HANDLE);
    this->char_buf = new CHAR_INFO[0];
    this->background_colour = background_colour;
    this->container_type = container_type;
    
    //clear terminal and clear scroll buffer respectively
    std::cout << "\x1b[2J";
    std::cout << "\x1b[3J";

    SetConsoleOutputCP(CP_UTF8);

    handleResize();
}

Terminal::~Terminal() {

}

void Terminal::handleResize() {
    //clear terminal and clear scroll buffer respectively
    std::cout << "\x1b[2J";
    std::cout << "\x1b[3J";

    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(h_out, &info);
    
    this->rows = info.dwSize.Y;
    this->cols = info.dwSize.X;
    
    delete[] char_buf;
    this->char_buf = new CHAR_INFO[rows * cols];
    
    for (int i = 0; i < rows * cols; i++) {
        char_buf[i].Char.AsciiChar = '*';
        char_buf[i].Char.UnicodeChar = '*';
        char_buf[i].Attributes = this->background_colour;
    }

    for (Container* container : containers){
        container->reinitializeContainer(rows, cols);
    }
}

bool Terminal::checkForEvents() {
    DWORD num_events;
    GetNumberOfConsoleInputEvents(h_input, &num_events);
    return num_events != 0;
}


void Terminal::render() {
    DWORD num_read;
    INPUT_RECORD input_records[128];
    
    if (checkForEvents()) {
        ReadConsoleInput(h_input, input_records, 128, &num_read);
        for (int i = 0; i < num_read; i++) {
            switch (input_records[i].EventType) {
                case WINDOW_BUFFER_SIZE_EVENT: {
                    this->handleResize();
                    return;
                }
            }
        }
    }


    int x_to_render = 0;
    int y_to_render = 0;
    for (Container* container : containers) {
        container->render(char_buf, x_to_render, y_to_render, this->rows, this->cols);
    
        if (this->container_type == ContainerType::FLEX_ROW) {
            y_to_render += container->rect.h;
        }
        else{
            x_to_render += container->rect.w;
        }
    }
    
    COORD bufferSize = {SHORT(cols), SHORT(rows)};
    COORD bufferCoord = {0, 0};
    SMALL_RECT writeRegion = {0, 0, SHORT(bufferSize.X - 1), SHORT(bufferSize.Y - 1)};
    WriteConsoleOutputW(h_out, char_buf, bufferSize, bufferCoord, &writeRegion);
    SetConsoleCursorPosition(h_out, {5,0});
}