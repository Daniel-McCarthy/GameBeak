#include "Screen.h"
#include "src/Core.h"
#include "src/Gpu.h"
#include "src/Memory.h"
#include <QtDebug>
#include <QThread>
#include <QTime>

Screen::Screen(QWidget *parent, Memory& memory, Gpu& gpu)
    : QWidget(parent), memory(memory), gpu(gpu)
{
    QColor transparent = QColor(0, 0, 0, 0);
    for(int i = 0; i < (256*256); i++) {
        bgPixels[i] = transparent;
        spritePixels[i] = transparent;
        windowPixels[i] = transparent;
        tileDebugPixels[i] = transparent;
    }
}

void Screen::updateLCD(int clocks, int& lineClocksSinceLastUpdate, int& refreshClocksSinceLastUpdate, int& clocksSinceLastVBlank)
{
    unsigned char ly = memory.getLCDLY();
    unsigned char originalLY = ly;
    if (gpuMode == 0)// || !gpu.getLCDOn()) //(Should be more accurate? Causes Bust A Move to be extremely slow when LCD is off)
    {
        //H-Blank
        if ((clocks - lineClocksSinceLastUpdate) >= 204)//40)//80)//40)//80)//56)//102)//204)
        {
            {
                ly++;
                memory.setLCDLY(ly);
            }

            if (ly >= 144)
            {
                gpu.setLCDMode(1);
                gpuMode = 1;
                clocksSinceLastVBlank = clocks;
                //Set LCD Interrupt if V-Blank Event is set
                if ((gpu.getLCDStatus() & 0x8) > 0)
                {
                    memory.writeMemory(0xFF0F, (unsigned char)(memory.readMemory(0xFF0F) | 0x02));
                }

                if ((clocks - refreshClocksSinceLastUpdate) >= 16384)//32768)//680)//12)
                {
                    if (memory.getLCDEnabled())
                    {
                        drawScreenFromMaps(gpu.getScrollX(), gpu.getScrollY());
                        drawImageToScreen(screen);

                        int millisecondsElapsed = screenUpdateTimer.elapsed();
                        if (millisecondsElapsed == 0)
                        {
                            screenUpdateTimer.start();
                        } else {
                            if (millisecondsElapsed < 17)
                            {
                                QThread::msleep(17 - millisecondsElapsed);
                            }
                            screenUpdateTimer.restart();
                        }
                    }
                    refreshClocksSinceLastUpdate = clocks;
                    processPolling = true;
                }
                //Set VBLANK Interrupt Flag
                if (gpu.getLCDOn())
                {
                    memory.writeMemory((short)0xFF0F, (unsigned char)(memory.readMemory(0xFF0F) | 0x1));
                }

                refreshClocksSinceLastUpdate = clocks;
            }
            else
            {
                gpu.setLCDMode(2);
                gpuMode = 2;

                //Set LCD Interrupt if OAM Event is set
                if ((gpu.getLCDStatus() & 0x10) > 0)
                {
                    memory.writeMemory(0xFF0F, (unsigned char)(memory.readMemory(0xFF0F) | 0x02));
                }
            }

            lineClocksSinceLastUpdate = clocks;
        }

    }
    else if (gpuMode == 1)
    {
        //V-Blank

        if ((clocks - lineClocksSinceLastUpdate) >= 456)//100)//50)//100)//114)//228)//456)
        {
            if (!poweringOn)
            {
                ly++;
                memory.setLCDLY(ly);
            }
            /*
            if (ly >= 154)
            {

                //Set LCD Interrupt if OAM event is enabled
                if ((gpu.getLCDStatus() & 0x10) > 0)
                {
                    memory.writeMemory(0xFF0F, (byte)(memory.readMemory(0xFF0F) | 0x02));
                }

                ly = 0;
                memory.setLCDLY(ly);
            }
            */

            lineClocksSinceLastUpdate = clocks;
        }

        if ((clocks - clocksSinceLastVBlank) >= 4560)
        {

            gpu.setLCDMode(2);
            gpuMode = 2;
            lineClocksSinceLastUpdate = clocks;//-1;
            poweringOn = false;
            //Set LCD Interrupt if OAM event is enabled
            if ((gpu.getLCDStatus() & 0x10) > 0)
            {
                memory.writeMemory(0xFF0F, (unsigned char)(memory.readMemory(0xFF0F) | 0x02));
            }

            ly = 0;
            memory.setLCDLY(ly);
        }
    }
    else if (gpuMode == 2)
    {
        //OAM Mode
        if ((clocks - lineClocksSinceLastUpdate) >= 80)//15)//30)//15)//20)//40)//80)
        {
            gpu.setLCDMode(3);
            gpuMode = 3;

            lineClocksSinceLastUpdate = clocks;

            if (memory.getLCDEnabled())
            {
                if (gpu.getBackGroundEnabled())
                {
                    gpu.drawLineFromBGMap(gpu.getScrollY() + ly);
                    scrollXValues[(unsigned char)(gpu.getScrollY() + ly)] = gpu.getScrollX();
                }
            }
        }
    }
    else
    {
        //VRAM Mode
        if ((clocks - lineClocksSinceLastUpdate) >= 172)//30)//60)//30)//43)//86)//172)
        {
            gpu.setLCDMode(0);
            gpuMode = 0;

            //Set LCD Interrupt if H-Blank Event is set
            if ((gpu.getLCDStatus() & 0x4) > 0)
            {
                memory.writeMemory(0xFF0F, (unsigned char)(memory.readMemory(0xFF0F) | 0x02));
            }

            if (memory.getLCDEnabled())
            {
                if (gpu.getSpriteEnabled())
                {
                    gpu.drawLineFromSpriteMap(ly);
                }

                if (gpu.getWindowEnabled())
                {
                    gpu.drawLineFromWindowMap(ly);
                }
            }
            lineClocksSinceLastUpdate = clocks;
        }
    }

    if (ly != originalLY)
    {
        //LCDLY Compare Interrupt
        if (gpu.getLCDOn() && (gpu.getLCDLY() == gpu.getLCDLYCompare()))
        {
            //Request interrupt of Interrupt for LCDLYCompare set
            if (gpu.getLCDLYCCheckEnabled())
            {
                memory.writeMemory(0xFF0F, (unsigned char)(memory.readMemory(0xFF0F) | 0x02));
            }

            //Enable Coincidence Flag
            gpu.setLCDStatus(gpu.getLCDStatus() | 0x04);
        }
        else
        {
            //Disable Coincidence Flag
            gpu.setLCDStatus(gpu.getLCDStatus() & 0xFB);
        }
    }

}

void Screen::setBGPixel(unsigned char  x, unsigned char  y, QColor color)
{
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
                screen.setPixelColor(i, j, bgPixels[x + (y * 256)]);
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
                screen.setPixelColor(x, y, spritePixels[(x) + (y * 256)]);
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
