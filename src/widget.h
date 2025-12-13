#ifndef WIDGET_H
#define WIDGET_H

#include <windows.h>
#include <string>
#include <vector>

#define BLUE FOREGROUND_BLUE
#define GREEN FOREGROUND_GREEN
#define RED FOREGROUND_RED
#define WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

class Widget{
    private:
        std::string value;
        int x, y;
        bool bold, italic;
    public:
        virtual std::string getValue();
        
        virtual void render(std::vector<std::vector<CHAR_INFO>>& char_buf_vector);
};

class Label : public Widget{
    private:
        std::string value;
        int x, y;
        bool bold, italic;
        WORD text_colour;
    
    public:
        void setText(std::string value);

        std::string getValue() override;

        void render(std::vector<std::vector<CHAR_INFO>>& char_buf_vector) override;

        Label(std::string value, bool bold, bool italic, int x, int y, WORD text_colour);

};

#endif //WIDGET_H