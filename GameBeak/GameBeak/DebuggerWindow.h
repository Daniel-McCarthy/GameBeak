#pragma once

//#include <SDL.h>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

#ifndef DEBUGWINDOWH
#define DEBUGWINDOWH

class DebuggerWindow
{
public:
	DebuggerWindow();
	~DebuggerWindow();

	DebuggerWindow(string title, int width, int height);
	DebuggerWindow(RenderWindow* tempWindow);
	void setIcon(int width, int height, string path);
	void displayRegisters();
	void displayMemory();
	void displayDisassembly();
	void printText(string text);
	void printText(string text, int x, int y);
	void printText(string text, int x, int y, Color color);
	void drawButton(int x, int y);
	void drawButton(int x, int y, float scaleX, float scaleY);
	void runLoop();

	RenderWindow window;
	Texture texture;
	Uint8* pixels;
	bool run = true;
	Font font;

	Sprite buttonSprite;
	Texture buttonTexture;

	int memoryPosition = 0x0;
	int debuggerPage = 0;
};

#endif
