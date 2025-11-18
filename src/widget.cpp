#include <string>
#include <vector>

#include "widget.h"
#include "terminal.h"

std::string Widget::getValue(){
     return this->value;
};

void Widget::render(std::vector<std::vector<std::string>>& buffer){};


void TextBox::setText(std::string value){
    this->value = value;
}

std::string TextBox::getValue(){
    return this->value;
}

void TextBox::render(std::vector<std::vector<std::string>>& buffer){
    std::string value_to_render[value.size()];
    for(int i = 0; i < value.size(); i++){
        std::string v;
        v = value[i];
        value_to_render[i] = v;
        if(this->bold) value_to_render[i] = "\x1b[1m" + value_to_render[i] + "\x1b[22m";
        if(this->italic) value_to_render[i] = "\x1b[3m" + value_to_render[i] + "\x1b[23m";
    }
    
    for(int i = 0; i < value.size(); i++){
        buffer[y][x+i] = value_to_render[i];
    }
    
    
};

TextBox::TextBox(std::string value, bool bold, bool italic, int x, int y) { 
    this->value = value;
    this->bold = bold;
    this->italic = italic;
    this->x = x;
    this->y = y;
}
