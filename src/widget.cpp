#include <string>
#include <vector>

#include <windows.h>
#include "widget.h"
#include "terminal.h"

std::string Widget::getValue(){
     return this->value;
};

void Widget::render(std::vector<std::vector<CHAR_INFO>>& char_buf_vector){};


void Label::setText(std::string value){
    this->value = value;
}

std::string Label::getValue(){
    return this->value;
}

void Label::render(std::vector<std::vector<CHAR_INFO>>& char_buf_vector){
    //!old
    /*std::string value_to_render[value.size()];
    for(int i = 0; i < value.size(); i++){
        std::string v;
        v = value[i];
        value_to_render[i] = v;
        if(this->bold) value_to_render[i] = "\x1b[1m" + value_to_render[i] + "\x1b[22m";
        if(this->italic) value_to_render[i] = "\x1b[3m" + value_to_render[i] + "\x1b[23m";
    }
    
    for(int i = 0; i < value.size(); i++){
        buffer[y][x+i] = value_to_render[i];
    }*/
    
    
    for (int i = 0; i < value.size(); i++){
        CHAR_INFO value_to_render;
        value_to_render.Char.AsciiChar = value[i];
        value_to_render.Char.UnicodeChar = value[i];
        value_to_render.Attributes = text_colour;
        // char_buf_vector.push_back(value_to_render);
        char_buf_vector[y][x+i] = value_to_render;


    }

    
    
};

Label::Label(std::string value, bool bold, bool italic, int x, int y, WORD text_colour) { 
    this->value = value;
    this->bold = bold;
    this->italic = italic;
    this->x = x;
    this->y = y;
    this-> text_colour = text_colour;
}
