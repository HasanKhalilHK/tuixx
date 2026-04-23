#include "../headers/container.h"
#include <stdexcept>

void Container::addWidget(Widget* widget){
    this->widgets.push_back(widget);
    if (this->rows == -1 || this->cols == -1){
        throw std::runtime_error("Widget added to uninitialized container, add container to a terminal first.");
    }
    this->reinitializeContainer(this->rows, this->cols);
}