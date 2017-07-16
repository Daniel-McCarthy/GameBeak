#pragma once

//#ifndef WINDOWH
//#define WINDOWH

//#include <SDL.h>
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

	//GameWindow(string title, int xPos, int yPos, int width, int height);
	GameWindow::GameWindow(RenderWindow* window);
	GameWindow(string title, int width, int height);
	~GameWindow();
	//void setPixel(int x, int y, SDL_Color color);
	/*
	void DrawPixel(int x, int y, bool enabled);
	bool XorPixel(int x, int y);
	void DrawSprite(vector<int> spriteData, int x, int y);
	void DrawSprite(vector<int> spriteData, int x, int y, int n);
	void clearScreen();
	*/
	//void drawScreen();
	//void drawScreen(Texture texture);
	//void refreshScreen(int clocks, int& clocksSinceLastUpdate);
	//void updateLCD(int clocks, int& clocksSinceLastUpdate);
	void updateLCD(int clocks, int& lineClocksSinceLastUpdate, int& refreshClocksSinceLastUpdate);
	void setIcon(int width, int height, string path);
	//void setPixel(int x, int y, Color color);
	void setBGPixel(int x, int y, Color color);
	void setWindowPixel(int x, int y, Color color);
	void setSpritePixel(int x, int y, Color color);
	void setDebugPixel(int x, int y, Color color);
	void drawScreenFromMaps(int scrollX, int ScrollY);
	void drawImageToScreen(Image image);
	RenderWindow* window;
	Texture texture;
	//Uint8* bgPixels;
	//Uint8* windowPixels;
	//Uint8* spritePixels;
	Color bgPixels[256 * 256];
	Color windowPixels[256 * 256];
	Color spritePixels[256 * 256];
	Color tileDebugPixels[256 * 256];
	int gpuMode = 1; //BGB defaults this to 1, V-Blank. This should be true.
	int getGPUMode();
	Image screen;
	Image debugTileScreen;
	/*
	vector<vector<SDL_Color>> pixels;
	SDL_Renderer* sdlRenderer;
	SDL_Texture* texture;
	Uint32* canvas;
	SDL_Window* sdlWindow;
	SDL_GLContext sdlGLContext;
	SDL_Surface* sdlSurface;
	*/
};

//#endif