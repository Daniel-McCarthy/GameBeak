#include "Screen.h"
#include "src/Gpu.h"
#include "src/Memory.h"

Screen::Screen(QWidget *parent, Memory& memory, Gpu& gpu)
    : QWidget(parent), memory(memory), gpu(gpu)
{
}
