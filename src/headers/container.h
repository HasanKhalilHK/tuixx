#ifndef CONTAINER_H
#define CONTAINER_H

#include "widget.h"
#include "style.h"
#include <vector>

class TUI_DLL Container {
friend class Terminal;

private:


    #ifdef _WIN32
    CHAR_INFO* char_buf;
    void render(CHAR_INFO *char_buf, int x, int y, int rows, int cols);
    #else

    Cell* char_buf;
    void render(Cell* char_buf, int x, int y, int rows, int cols);
    #endif
    
    std::vector<Widget*> widgets;
    Rect rect;
    Style style;
    int rows, cols;

    void reinitializeContainer(int rows, int cols);

public:
    Container(Style style);
    Container();
    ~Container();

    void addWidget(Widget *widget);
};

#endif // CONTAINER_H