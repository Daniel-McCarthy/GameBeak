#include "Core.h"

Core::Core(QWidget *parent) : QWidget(parent)
{

}

Memory* Core::getMemoryPointer() {
    return memory;
}

