#ifndef WIDGET_H
#define WIDGET_H

#include <windows.h>
#include <string>
#include <vector>

class Widget{
    private:
        std::string value;
        int x, y;
        bool bold, italic;
    public:
        virtual std::string getValue();
        
        virtual void render(std::vector<std::vector<CHAR_INFO>>& char_buf_vector);
};

class TextBox : public Widget{
    private:
        std::string value;
        int x, y;
        bool bold, italic;
    
    public:
        void setText(std::string value);

        std::string getValue() override;

        void render(std::vector<std::vector<CHAR_INFO>>& char_buf_vector) override;

        TextBox(std::string value, bool bold, bool italic, int x, int y);

};

#endif //WIDGET_H