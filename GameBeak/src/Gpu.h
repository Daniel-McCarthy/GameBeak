#pragma once

#include <QList>
#include <QColor>
#include <QFile>

struct Palette {
  QString paletteName;
  QColor paletteColors[12];
};

class Core;
class Memory;
class Screen;
class Gpu
{
private:
    Memory& memory;
    Screen& screen;
    bool& GBCMode;

    const QColor darkestPink = QColor(82, 5, 40, 255); //Darkest Pink //FFF0F5FF
    const QColor darkPink = QColor(255, 116, 217, 255); //Dark Pink //FFBADEFF
    const QColor lightPink = QColor(255, 186, 222, 255); //Light Pink //FF74D9FF
    const QColor lightestPink = QColor(255, 240, 245, 255); //Lightest Pink //520528FF

public:
    const Palette defaultPalette = {
        "Default Palette",
        {
            lightestPink, lightPink, darkPink, darkestPink,
            lightestPink, lightPink, darkPink, darkestPink,
            lightestPink, lightPink, darkPink, darkestPink
        }
    };

    unsigned int paletteSetting = 0; // gamebeakPinkAlt;
    QList<Palette> gameBeakPalette = QList<Palette>({defaultPalette});

    unsigned char gameboyColorBackGroundPalette[64]; //2 unsigned chars per color, 4 colors per BG Palette, 8 BG Palettes
    unsigned char gameboyColorSpritePalette[64]; //2 unsigned chars per color, 4 colors per Sprite Palette, 8 Sprite Palettes

    Gpu(Memory& memory, Screen& screen, bool& gbcMode);
    ~Gpu();
    unsigned char getLCDStatus();
    void setLCDStatus(unsigned char newStatus);
    void setLCDMode(unsigned char status);
    unsigned char getLCDLYCompare();
    unsigned char getLCDLY();
    unsigned char getLCDMode();
    unsigned char getLCDLYCCheckEnabled();
    unsigned char getLCDControl();
    bool getLCDOn();
    bool getWindowTileMapLocation();
    bool getWindowEnabled();
    bool getBackGroundWindowTileSetLocation();
    bool getBackGroundTileMapLocation();
    bool getSpriteSize();
    bool getSpriteEnabled();
    bool getBackGroundEnabled();
    unsigned char getScrollX();
    unsigned char getScrollY();
    unsigned char getWindowX();
    unsigned char getWindowY();
    void drawDebugTile(int tileNumber, QList<QList<QColor>> tile);
    void drawLineFromBGMap(unsigned char  lineY);
    void drawLineFromWindowMap(unsigned char  lineY);
    void drawLineFromSpriteMap(unsigned char  lineY);
    void drawAllTiles();
    QColor returnColor(int colorNumber);
    QColor returnColor(int colorNumber, int palette);
    QColor returnGBCSpriteColor(unsigned char colorNumber, unsigned char palette);
    QColor returnGBCBackgroundColor(unsigned char colorNumber, unsigned char palette);
    unsigned char returnPalette(unsigned char palette);
    void loadPalettesFromXML(QFile* file);
    QString openCreatePalettesXML();
    void savePalettesToFile();
    void resetGPU();
};

