#pragma once

#include "Main.h"

using namespace std;
using namespace sf;

#ifndef POSTPROCESSH
#define POSTPROCESSH

Color mixColors(Color color1, Color color2);
Color mixColors(Color color1, Color color2, float div);

Image filterSelect(Image screen, byte filterNumber);

Image eagleFilter(Image screen);

Image blurFilter(Image screen);

Image customFilter(Image screen);

Image zigZagFilter(Image screen);

Image rainbowFilter(Image screen);




/*
for (int x = 0; x < 160; x++)
{
for (int y = 0; y < 144; y++)
{
Color blackPixel = beakGPU.returnColor(3);
Color pixel1 = screen.getPixel(x, y);

if (pixel1 == blackPixel)
{
	if (y > 0)
	{
		if (x > 0)
		{
			if (screen.getPixel(x - 1, y - 1) == blackPixel) //if Up-Left pixel is black
			{
				screen.setPixel(x - 1, y, mixColors(pixel1, screen.getPixel(x - 1, y))); //Left
			}
		}

		if (x < 160)
		{
			if (screen.getPixel(x + 1, y - 1) == blackPixel) //if Up-Right pixel is black
			{
			screen.setPixel(x + 1, y, mixColors(pixel1, screen.getPixel(x + 1, y))); //Right
			}
		}

	//screen.setPixel(x, y - 1, mixColors(pixel1, screen.getPixel(x, y - 1))); //Up

	}

	if (y < 144)
	{
		if (x > 0)
		{
			if (screen.getPixel(x - 1, y + 1) == blackPixel) //if Down-Left pixel is black
			{
			screen.setPixel(x - 1, y, mixColors(pixel1, screen.getPixel(x - 1, y))); //Left
			}
		}

		if (x < 160)
		{
			if (screen.getPixel(x + 1, y + 1) == blackPixel) //if Down-Right pixel is black
			{
			screen.setPixel(x + 1, y, mixColors(pixel1, screen.getPixel(x + 1, y))); //Right
			}
		}

		//screen.setPixel(x, y + 1, mixColors(pixel1, screen.getPixel(x, y + 1))); //Down
}
}
}
}
*/





#endif // !POSTPROCESSH