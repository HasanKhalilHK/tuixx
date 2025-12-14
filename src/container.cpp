#include "container.h"
#include <vector>


Flex::Flex(FlexDirection direction){
    this->direction = direction;
    this->rect = {0,0,0,0};
}

void Flex::render(std::vector<std::vector<CHAR_INFO>>& char_buf_vector, int x, int y){
    if (direction == FlexDirection::Column){
        int x_to_render = x;
        int y_to_render = y;
            
        for(int i = 0; i < widgets.size(); i++){
            // y_to_render += widgets[i]->rect.h;
            widgets[i]->render(char_buf_vector, x_to_render, y_to_render);
            x_to_render += widgets[i]->rect.w;
        
        }
    }

    if (direction == FlexDirection::Row){
        int x_to_render = x;
        int y_to_render = y;
        
        for(int i = 0; i < widgets.size(); i++){
            // x_to_render += widgets[i]->rect.w;
            widgets[i]->render(char_buf_vector, x_to_render, y_to_render);
            y_to_render += widgets[i]->rect.h;
        
        }

    }
}

void Flex::addWidget(Widget* widget){
    widgets.push_back(widget);

    if (direction == FlexDirection::Column){
        
        int max_height = widgets[0]->rect.h;
        for (Widget* w: widgets){
            if(w->rect.h > max_height) max_height = w->rect.h;
        }
        
        this->rect.w += widget->rect.w;
        this->rect.h = max_height;
    }

    if (direction == FlexDirection::Row){
        
        int max_width = widgets[0]->rect.w;
        for (Widget* w: widgets){
            if(w->rect.w > max_width) max_width = w->rect.w;
        }
        
        this->rect.h += widget->rect.h;
        this->rect.w = max_width;
    }
}

Flex::~Flex(){  
    for (Widget* w : widgets) {
        delete w;
    }
}