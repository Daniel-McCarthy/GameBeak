#pragma once

//#include <SDL.h>
#include <Windows.h>
#include <vector>
#include "Windows.h"
#include <SFML\Graphics\Color.hpp>

using namespace std;
using namespace sf;

class gpu
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

	byte gameboyColorBackGroundPalette[64]; //2 bytes per color, 4 colors per BG Palette, 8 BG Palettes
	byte gameboyColorSpritePalette[64]; //2 bytes per color, 4 colors per Sprite Palette, 8 Sprite Palettes
	//byte scrollXHistory[144];
	//byte scrollYHistory[144];

	gpu();
	~gpu();
	byte getLCDStatus();
	void setLCDStatus(byte newStatus);
	void setLCDMode(byte status);
	byte getLCDLYCompare();
	byte getLCDLY();
	byte getLCDMode();
	byte getLCDLYCCheckEnabled();
	byte getLCDControl();
	bool getLCDOn();
	bool getWindowTileMapLocation();
	bool getWindowEnabled();
	bool getBackGroundWindowTileSetLocation();
	bool getBackGroundTileMapLocation();
	bool getSpriteSize();
	bool getSpriteEnabled();
	bool getBackGroundEnabled();
	byte getScrollX();
	byte getScrollY();
	byte getWindowX();
	byte getWindowY();
	void drawDebugTile(int tileNumber, vector<vector<Color>> tile);
	void drawLineFromBGMap(unsigned char  lineY);
	void drawLineFromWindowMap(unsigned char  lineY);
	void drawLineFromSpriteMap(unsigned char  lineY);
	void drawAllTiles();
	Color returnColor(int colorNumber);
	Color returnColor(int colorNumber, int palette);
	Color returnGBCSpriteColor(byte colorNumber, byte palette);
	byte returnPalette(byte palette);
	void loadPalettesFromXML(ifstream file);
	ifstream openCreatePalettesXML();

};

