#pragma once

#include <QList>
#include <QColor>
#include <QFile>

class Core;
class Memory;
class Screen;
class Gpu
{
private:
    Memory& memory;
    Screen& screen;
    bool& GBCMode;
    unsigned char& paletteSetting;

    const QColor darkestPink = QColor(72, 24, 59, 255); //Pink Black //48183BFF
    const QColor darkPink = QColor(255, 131, 217, 255); //Dark Pink //FF83D9FF
    const QColor lightPink = QColor(255, 214, 245, 255); //Light Pink //FFD6F5FF
    const QColor lightestPink = QColor(255, 241, 254, 255); //Pink WHITE //FFF1FEFF

public:
    QColor gameBeakPalette[4000] = { lightestPink, lightPink, darkPink, darkestPink,
									lightestPink, lightPink, darkPink, darkestPink,
									lightestPink, lightPink, darkPink, darkestPink };

    unsigned char gameboyColorBackGroundPalette[64]; //2 unsigned chars per color, 4 colors per BG Palette, 8 BG Palettes
    unsigned char gameboyColorSpritePalette[64]; //2 unsigned chars per color, 4 colors per Sprite Palette, 8 Sprite Palettes

    Gpu(Memory& memory, Screen& screen, bool& gbcMode, unsigned char& paletteSetting);
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
    void loadPalettesFromXML(QFile file);
    QString openCreatePalettesXML();

};

