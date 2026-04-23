#include "../headers/container.h"
#include "../headers/widget.h"

Container::Container(Style style){
    this->style = style;
    this->rect = {0,0};
    this->rows = -1;
    this->cols = -1;
    this->char_buf = new CHAR_INFO[0];
}

Container::Container(){
    this->style = {0,0, NONE, FLEX_COL};
    this->rect = {0,0};
    this->rows = -1;
    this->cols = -1;
    this->char_buf = new CHAR_INFO[0];
}

Container::~Container() {
    for (Widget* w : widgets) {
        delete w;
    }
}

void Container::render(CHAR_INFO* char_buf, int x, int y, int rows, int cols) {
    reinitializeContainer(rows, cols);
    for (int i = 0; i < this->rect.h; i++) {
        for (int j = 0; j < this->rect.w; j++) {
            int src_index = (i * this->rect.w) + j;
            int dest_index = ((y + i) * cols) + (x + j);
            if (dest_index >= 0 && dest_index < (rows * cols)) {
                char_buf[dest_index] = this->char_buf[src_index];
            }
        }
    }
}

void Container::reinitializeContainer(int rows, int cols){
    this->rows = rows;
    this->cols = cols;

    int total_width = 0;
    int total_height = 0;
    Widget* widget;
    for(int i = 0; i < widgets.size(); i++){
        widget = widgets[i];
        int w = widget->rect.w;
        int h = widget->rect.h;
        switch(widget->get_type()){
            case WidgetType::LABEL:{
                Label* label = static_cast<Label*>(widget);
                if (this->style.container_type == ContainerType::FLEX_ROW){
                    total_height +=1;
                    if(this->rect.w <= w) {
                        total_width = w;
                    }
                }
                else{ //*ContainerType::FLEX_COl
                    total_height += total_height >=h ? 0: 1;
                    total_width += w;
                }
                break;
            }
        }
    }
    if(total_width > cols) total_width = cols;
    if(total_height > rows) total_height = rows;
    this->rect.w = total_width;
    this->rect.h = total_height;

    delete[] this->char_buf;
    this->char_buf = new CHAR_INFO[total_height * total_width];

    int x_to_render = 0;
    int y_to_render = 0;
    for (int i = 0; i < total_height * total_width; i++) {
        // char_buf[i].Char.AsciiChar = '*';
        char_buf[i].Char.UnicodeChar = '*';
        char_buf[i].Attributes = FOREGROUND_GREEN;
    }
    for(int i = 0; i < widgets.size(); i++){
        widgets[i]->render(this->char_buf, x_to_render, y_to_render, this->rect.h, this->rect.w);
        
        if (this->style.container_type == ContainerType::FLEX_ROW) {
            y_to_render += widgets[i]->rect.h;
        }
        else{
            x_to_render += widgets[i]->rect.w;
        }
    }
}