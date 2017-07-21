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

public:
	Color gameBeakPalette[400] = { lightestPink, lightPink, darkPink, darkestPink };

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
	void drawLineFromBGMap(int lineY);
	void drawLineFromWindowMap(int lineY);
	void drawLineFromSpriteMap(int lineY);
	void drawAllTiles();
	Color returnColor(int colorNumber);
	Color returnColor(int colorNumber, int palette);
	byte returnPalette(byte palette);
	void loadPalettesFromXML(ifstream file);
	ifstream openCreatePalettesXML();

};

