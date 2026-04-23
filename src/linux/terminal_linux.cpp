#include "../headers/terminal.h"
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <cstring>
#include <locale.h>

Terminal::Terminal(Colour background_colour, ContainerType container_type) {
        
    handle_initialized = false;
    if (!handle_initialized) {
        struct sigaction sa;
        memset(&sa, 0, sizeof(sa));
        sa.sa_handler = resize_handler;
        sigaction(SIGWINCH, &sa, nullptr);
        handle_initialized = true;
    }

    this->char_buf = new Cell[0];
    this->background_colour = background_colour;
    this->container_type = container_type;

    handleResize();
}

Terminal::~Terminal() {

}

void Terminal::handleResize() {
    //clear terminal and clear scroll buffer respectively
    // std::cout << "\x1b[2J";
    // std::cout << "\x1b[3J";

    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    this->rows = ws.ws_row;
    this->cols = ws.ws_col;
    
    delete[] char_buf;
    this->char_buf = new Cell[rows * cols];
    
    for (int i = 0; i < rows * cols; i++) {
        char_buf[i].character = "*";
        char_buf[i].colour = this->background_colour;
    }

    for (Container* container : containers){
        container->reinitializeContainer(rows, cols);
    }
}

void Terminal::render() {

    if(resize_pending){
        handleResize();
        resize_pending = false;
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
    
    //move cursor to beginning of terminal (home)
    std::string output = "\033[H";
    std::string last_colour = "";

    for (int i = 0; i < rows * cols; i++) {
        if (char_buf[i].colour != last_colour) {
            output += char_buf[i].colour;
            last_colour = char_buf[i].colour;
        }
        output += char_buf[i].character;
    }
    
    //ansi code for resetting colours
    output += "\033[0m";
    
    write(STDOUT_FILENO, output.c_str(), output.size());


}
