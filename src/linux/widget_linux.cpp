#include "../headers/widget.h"
#include <string>
#include <vector>

std::vector<std::string> get_utf8_chars(const std::string& str) {
    std::vector<std::string> chars;
    for (size_t i = 0; i < str.size(); ) {
        size_t len = 1;
        unsigned char c = str[i];
        if (c >= 0xf0) len = 4;
        else if (c >= 0xe0) len = 3;
        else if (c >= 0xc0) len = 2;
        
        if (i + len <= str.size()) {
            chars.push_back(str.substr(i, len));
        }
        i += len;
    }
    return chars;
}

void Widget::render(Cell* char_buf, int x, int y, int rows, int cols) {}
void Widget::initWidget(int rows, int cols){}

size_t utf8_length(const std::string& str) {
    size_t length = 0;
    for (size_t i = 0; i < str.size(); i++) {
        if ((str[i] & 0xc0) != 0x80) length++;
    }
    return length;
}

Label::Label(std::string value, Colour colour) {
    setValue(value);
    this->colour = colour;
    this->rect = {0,0};
    this->widget_type = LABEL;
    this->initWidget(0, 0);
}

void Label::setValue(std::string value){
    this->value = value;
}

void Label::initWidget(int rows, int cols) {
    auto chars = get_utf8_chars(this->value);
    this->rect.w = chars.size(); 
    this->rect.h = 1;
}

void Label::render(Cell* char_buf, int x, int y, int rows, int cols) {
    auto chars = get_utf8_chars(this->value);
    for (int i = 0; i < chars.size(); i++) {
        int index = ((y * cols) + x + i);
        if (index < (rows * cols)) {
            char_buf[index].character = chars[i]; // Now stores the full UTF-8 sequence
            char_buf[index].colour = this->colour;
        }
    }
}