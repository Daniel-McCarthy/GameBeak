#pragma once

#include <QList>

using namespace std;

class Gpu
{
private:
	const Color darkestPink = Color(72, 24, 59, 255); //Pink Black //48183BFF
	const Color darkPink = Color(255, 131, 217, 255); //Dark Pink //FF83D9FF
	const Color lightPink = Color(255, 214, 245, 255); //Light Pink //FFD6F5FF
	const Color lightestPink = Color(255, 241, 254, 255); //Pink WHITE //FFF1FEFF

public:
	Color gameBeakPalette[4000] = { lightestPink, lightPink, darkPink, darkestPink,
									lightestPink, lightPink, darkPink, darkestPink,
									lightestPink, lightPink, darkPink, darkestPink };

    unsigned char gameboyColorBackGroundPalette[64]; //2 unsigned chars per color, 4 colors per BG Palette, 8 BG Palettes
    unsigned char gameboyColorSpritePalette[64]; //2 unsigned chars per color, 4 colors per Sprite Palette, 8 Sprite Palettes

    Gpu();
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
	void drawDebugTile(int tileNumber, vector<vector<Color>> tile);
	void drawLineFromBGMap(unsigned char  lineY);
	void drawLineFromWindowMap(unsigned char  lineY);
	void drawLineFromSpriteMap(unsigned char  lineY);
	void drawAllTiles();
	Color returnColor(int colorNumber);
	Color returnColor(int colorNumber, int palette);
    Color returnGBCSpriteColor(unsigned char colorNumber, unsigned char palette);
    Color returnGBCBackgroundColor(unsigned char colorNumber, unsigned char palette);
    unsigned char returnPalette(unsigned char palette);
	void loadPalettesFromXML(ifstream file);
	ifstream openCreatePalettesXML();

};

