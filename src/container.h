#ifndef CONTAINER_H
#define CONTAINER_H

#include "widget.h"
#include <vector>

enum class FlexDirection{
    Row,
    Column
};


class Flex : public Widget{
    private:
        FlexDirection direction; 
        std::vector<Widget*> widgets;


    public:
        WidgetType type = WidgetType::Flex;
        void addWidget(Widget* widget);
        void render(std::vector<std::vector<CHAR_INFO>>& char_buf_vector, int x, int y) override;


        Flex(FlexDirection direction);
        ~Flex();


};




#endif //CONTAINER_H