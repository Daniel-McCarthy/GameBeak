#pragma once

//#ifndef WINDOWH
//#define WINDOWH

#include <SFML\Graphics.hpp>
#include <string>
#include <vector>

#include <Windows.h>

using namespace std;
using namespace sf;

class GameWindow
{
public:
	GameWindow() {}
	GameWindow::GameWindow(RenderWindow* window);
	GameWindow(string title, int width, int height);
	~GameWindow();

	void updateLCD(int clocks, int& lineClocksSinceLastUpdate, int& refreshClocksSinceLastUpdate, int& clocksSinceLastVBlank);
	void setIcon(int width, int height, string path);
	Color getBGPixel(unsigned char  x, unsigned char  y);
	void setBGPixel(unsigned char  x, unsigned char  y, Color color);
	void setWindowPixel(unsigned char  x, unsigned char  y, Color color);
	void setSpritePixel(unsigned char  x, unsigned char  y, Color color);
	void setDebugPixel(unsigned char  x, unsigned char  y, Color color);
	void drawScreenFromMaps(unsigned char  scrollX, unsigned char  ScrollY);
	void drawFullScreenMaps();
	void drawImageToScreen(Image image);
	RenderWindow window;
	Texture texture;
	Color bgPixels[256 * 256];
	Color windowPixels[256 * 256];
	Color spritePixels[256 * 256];
	Color tileDebugPixels[256 * 256];
	uint8_t scrollXValues[256];
	int gpuMode = 1; //BGB defaults this to 1, V-Blank. This should be true.
	int getGPUMode();
	Image screen;
	Image debugTileScreen;
	bool poweringOn = true;
};

//#endif