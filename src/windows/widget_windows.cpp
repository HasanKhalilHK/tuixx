#include "../headers/widget.h"
#include <string>


void Widget::render(CHAR_INFO* char_buf, int x, int y, int rows, int cols) {}
void Widget::initWidget(int rows, int cols){}

std::wstring StringToWString(std::string& str) {
    if (str.empty()) return std::wstring();
    int size = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstring(size, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstring[0], size);
    return wstring;
}

Label::Label(std::string value, Colour colour) {
    setValue(value);
    this->colour = colour;
    this->rect = {0,0};
    this->widget_type = LABEL;
    this->initWidget(0, 0);
}

void Label::initWidget(int rows, int cols){
    this->rect.w = this->value.size();
    this->rect.h = 1;
}

void Label::setValue(std::string value){
    this->value = StringToWString(value);
}

void Label::render(CHAR_INFO* char_buf, int x, int y, int rows, int cols) {
    for (int i = 0; i < value.size(); i++) {
        int index = ((y * cols) + x + i);
        if (index < (rows*cols)) {
            CHAR_INFO value_to_render;
            // value_to_render.Char.AsciiChar = value[i];
            value_to_render.Char.UnicodeChar = value[i];
            value_to_render.Attributes = this->colour;
            char_buf[index] = value_to_render;
            // char_buf[index].character = value[i];
            // char_buf[index].colour = this->colour;
            
        }
    }
}