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
	const Color darkestPink = Color(72, 24, 59, 255); //Pink Black
	const Color darkPink = Color(255, 131, 217, 255); //Dark Pink
	const Color lightPink = Color(255, 214, 245, 255); //Light Pink
	const Color lightestPink = Color(255, 241, 254, 255); //Pink WHITE

	const Color darkestGrey = Color(0, 0, 0, 255); //BLACK
	const Color darkGrey = Color(105, 105, 105, 255); //Dark GREY
	const Color lightGrey = Color(185, 185, 185, 255); //Light Grey
	const Color lightestGrey = Color(255, 255, 255, 255); //WHITE

	const Color gameBeakPalette[8] = { lightestGrey, lightGrey, darkGrey, darkestGrey, lightestPink, lightPink, darkPink, darkestPink };

public:
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
	//void drawTile();
	void drawTiles();
	void drawBGTile(int tileNumber, vector<vector<Color>> tile);
	void drawTileFromBGMap(int x, int y);
	void drawLineFromBGMap(int lineY);
	void drawLineFromWindowMap(int lineY);
	void drawLineFromSpriteMap(int lineY);
	void drawSpriteFromMap(int spriteNumber);
	void drawSprite(int x, int y, vector<vector<Color>> tile);
	void drawAllTiles();
	//void setFullMapPixel(int x, int y, Color color);
	Color returnColor(int colorNumber);
	Color returnColor(int colorNumber, int palette);
	byte returnPalette(byte palette);
	//int gpuMode = 1; //BGB defaults this to 1, V-Blank. This should be true.
	//Texture fullMapTexture;
	//Uint8* fullMapPixels;
};

