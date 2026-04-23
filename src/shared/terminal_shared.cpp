#include "../headers/terminal.h"

void Terminal::addContainer(Container* container){
    this->containers.push_back(container);
    container->reinitializeContainer(rows, cols);
}