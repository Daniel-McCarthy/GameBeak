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

    QColor getBGPixel(unsigned char  x, unsigned char  y);
    void setBGPixel(unsigned char  x, unsigned char  y, QColor color);
    void setWindowPixel(unsigned char  x, unsigned char  y, QColor color);
    void setSpritePixel(unsigned char  x, unsigned char  y, QColor color);
    void setDebugPixel(unsigned char  x, unsigned char  y, QColor color);
    void drawScreenFromMaps(unsigned char  scrollX, unsigned char  ScrollY);
    void drawFullScreenMaps();

signals:
    void drawImageToScreen(QImage image);

private:
    Memory& memory;
    Gpu& gpu;

    int gpuMode = 1; //BGB defaults this to 1, V-Blank. This should be true.
    int getGPUMode();
};

#endif // SCREEN_H
