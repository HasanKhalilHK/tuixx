#ifndef WIDGET_H
#define WIDGET_H

#ifdef _WIN32
#include <windows.h>
#endif
#include <string>
#include "style.h"


struct TUI_DLL Cell{
    std::string character;
    std::string colour;
};

struct TUI_DLL Rect{
    int w,h;
};

enum WidgetType{
    LABEL
};


class TUI_DLL Widget {
friend class Container;

protected:
    Rect rect;
    WidgetType widget_type;

    #ifdef _WIN32
    virtual void render(CHAR_INFO* char_buf, int x, int y, int rows, int cols);
    #else
    virtual void render(Cell* char_buf, int x, int y, int rows, int cols);
    #endif
    
    virtual void initWidget(int rows, int cols);

public:
    virtual WidgetType get_type();

};

class TUI_DLL Label : public Widget {
friend class Container;

private:
    Colour colour;

    #ifdef _WIN32
    virtual void render(CHAR_INFO* char_buf, int x, int y, int rows, int cols) override;
    std::wstring value;
    #else
    virtual void render(Cell* char_buf, int x, int y, int rows, int cols) override;
    std::string value;
    #endif
    
    void initWidget(int rows, int cols) override;

public:
    Label(std::string value, Colour colour);
    void setValue(std::string value);
};

#endif //WIDGET_H