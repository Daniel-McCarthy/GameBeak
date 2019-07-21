#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>

class Memory;
class Gpu;
class Screen : public QWidget
{
    Q_OBJECT
public:
    Screen(QWidget *parent, Memory& memory, Gpu& gpu);
private:
    Memory& memory;
    Gpu& gpu;

    int gpuMode = 1; //BGB defaults this to 1, V-Blank. This should be true.
    int getGPUMode();
};

#endif // SCREEN_H
