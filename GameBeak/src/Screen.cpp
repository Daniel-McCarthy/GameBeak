#include "Screen.h"
#include "src/Gpu.h"
#include "src/Memory.h"

Screen::Screen(QWidget *parent, Memory& memory, Gpu& gpu)
    : QWidget(parent), memory(memory), gpu(gpu)
{
}

void Screen::setBGPixel(unsigned char  x, unsigned char  y, QColor color)
{
    uint value = color.rgba();
    bgPixels[x + (y * 256)] = color;
}

QColor Screen::getBGPixel(unsigned char  x, unsigned char  y)
{
    return bgPixels[x + (y * 256)];
}

void Screen::setWindowPixel(unsigned char  x, unsigned char  y, QColor color)
{
    windowPixels[x + (y * 256)] = color;
}

void Screen::setSpritePixel(unsigned char  x, unsigned char  y, QColor color)
{
    spritePixels[x + (y * 256)] = color;
}

void Screen::drawScreenFromMaps(unsigned char  scrollX, unsigned char  scrollY)
{

    if (gpu.getBackGroundEnabled())
    {
        unsigned char x = 0;
        unsigned char y = 0;


        for (int i = 0; i < 160; i++)
        {
            for (int j = 0; j < 144; j++)
            {
                y = scrollY + j;
                x = (unsigned char)(scrollXValues[y] + i);

                QColor pixelColor = bgPixels.at(x + (y * 256));
                uint colorValue = pixelColor.rgba();
                screen.setPixelColor(i, j, colorValue);
            }
        }
    }

    if (gpu.getWindowEnabled())
    {
        //Draw Window
        int winX = gpu.getWindowX() - 7;
        int winY = gpu.getWindowY();

        bool yTest = (winY <=  144) && ((winY + 256) >= 0);
        bool xTest = (winX < 160) && ((winX + 256) > 0);

        if (xTest && yTest)
        {
            int xShift = 0;
            int yShift = 0;
            int x = 0;
            int y = 0;

            if (winX < 0)
            {
                xShift = 0 - winX;
            }
            else
            {
                x = winX;
            }

            if (winY < 0)
            {
                yShift = 0 - winY;
            }
            else
            {
                y = winY;
            }

            for (int i = 0; (i + x + xShift) < 160; i++)
            {
                for (int j = 0; (j + y + yShift) < 144; j++)
                {
                    QColor color = windowPixels[(xShift + i) + ((yShift + j) * 256)];
                    uint colorValue = color.rgba();
                    screen.setPixelColor((x + xShift + i), (y + yShift + j), windowPixels[(xShift + i) + ((yShift + j) * 256)]);
                }
            }
        }
    }


    //Draw Sprites
    if (gpu.getSpriteEnabled())
    {
        int x = 0;
        int y = 0;
        while (y < 144)
        {
            if (spritePixels[((x) + ((y) * 256))].alpha() != 0)
            {
                QColor color = spritePixels[(x) + (y * 256)];
                uint colorValue = color.rgba();
                screen.setPixelColor(x, y, colorValue);
            }

            if (x < 159)
            {
                x++;
            }
            else
            {
                x = 0;
                y++;
            }
        }
    }


    for (int i = 0; i < (256 * 256); i++)
    {
        spritePixels[i].setAlpha(0);
    }


}

void Screen::drawFullScreenMaps()
{
    QImage fullScreen = QImage();

    if (gpu.getBackGroundEnabled())
    {
        for (int x = 0; x < 256; x++)
        {
            for (int y = 0; y < 256; y++)
            {
                fullScreen.setPixelColor(x, y, bgPixels[x + (y * 256)]);
            }
        }
    }

    if (gpu.getWindowEnabled())
    {
        //Draw Window
        int winX = gpu.getWindowX() - 7;
        int winY = gpu.getWindowY();

        bool yTest = (winY <= 256) && ((winY + 256) >= 0);
        bool xTest = (winX < 256) && ((winX + 256) > 0);

        if (xTest && yTest)
        {
            int xShift = 0;
            int yShift = 0;
            int x = 0;
            int y = 0;

            if (winX < 0)
            {
                xShift = 0 - winX;
            }
            else
            {
                x = winX;
            }

            if (winY < 0)
            {
                yShift = 0 - winY;
            }
            else
            {
                y = winY;
            }

            for (int i = 0; (i + x + xShift) < 160; i++)
            {
                for (int j = 0; (j + y + yShift) < 144; j++)
                {
                    fullScreen.setPixelColor((x + xShift + i), (y + yShift + j), windowPixels[(xShift + i) + ((yShift + j) * 256)]);
                }
            }
        }
    }

    //Draw Sprites
    if (gpu.getSpriteEnabled())
    {
        int x = 0;
        int y = 0;
        while (y < 256)
        {
            if (spritePixels[((x)+((y) * 256))].alpha() != 0)
            {
                fullScreen.setPixelColor(x, y, spritePixels[(x)+(y * 256)]);
            }

            if (x < 255)
            {
                x++;
            }
            else
            {
                x = 0;
                y++;
            }

        }
    }

}

int Screen::getGPUMode()
{
    return gpuMode;
}
