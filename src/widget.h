#ifndef WIDGET_H
#define WIDGET_H

#include <windows.h>
#include <string>
#include <vector>

#define BLUE FOREGROUND_BLUE
#define GREEN FOREGROUND_GREEN
#define RED FOREGROUND_RED
#define WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

enum class WidgetType{
    Flex,
    Label

};

struct Rect {int x, y, w, h;};

class Widget{
    private:
        std::string value;
        bool bold, italic;
    
    public:
        Rect rect;
        WidgetType type;
        virtual std::string getValue();
        virtual void setRect(Rect rect);
        
        virtual void render(std::vector<std::vector<CHAR_INFO>>& char_buf_vector, int x, int y);
};

class Label : public Widget{
    private:
        std::string value;
        bool bold, italic;
        WORD text_colour;
        
    public:
        WidgetType type = WidgetType::Label;
        void setText(std::string value);
        std::string getValue() override;

        void render(std::vector<std::vector<CHAR_INFO>>& char_buf_vector, int x, int y) override;

        Label(std::string value, bool bold, bool italic, WORD text_colour);

};

#endif //WIDGET_H