#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QTime>

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
    QTime screenUpdateTimer;

    void setIcon(int width, int height, QString path);
    QVector<QColor> bgPixels = QVector<QColor>(256 * 256);
    QColor windowPixels[256 * 256];
    QColor spritePixels[256 * 256];
    QColor tileDebugPixels[256 * 256];
    unsigned char scrollXValues[256];
    int gpuMode = 1; //BGB defaults this to 1, V-Blank. This should be true.
    int getGPUMode();
    QImage screen = QImage(160, 144, QImage::Format_RGB32);
    QImage debugTileScreen;
    bool poweringOn = true;
};

#endif // SCREEN_H
