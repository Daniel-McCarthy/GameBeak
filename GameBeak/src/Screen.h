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

};

#endif // SCREEN_H
