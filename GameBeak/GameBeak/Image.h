#pragma once

#include "Color.h"
#include <vector>

using namespace std;

#ifndef IMAGEH
#define IMAGEH

//Get Pixel
//Set Pixel
//Get PIXELS[]

struct Size {
	int x;
	int y;
};

class Image
{



public:
	//int width;
	//int height;
	Size sizeValues;
	//unsigned char* pixels;
	vector<Color> pixels;

	Image()
	{
		sizeValues.x = 1;
		sizeValues.y = 1;
		pixels.push_back(Color(0, 0, 0, 255));
	}

	Image(int width, int height)
	{
		Color defaultColor = Color(255, 255, 255, 255); //It's possible this should have 0 alpha

		sizeValues.x = width;
		sizeValues.y = height;

		int finalSize = width*height;

		for (int i = 0; i < finalSize; i++)
		{
			pixels.push_back(defaultColor);
		}
	}

	Image(int width, int height, Color defaultColor)
	{
		sizeValues.x = width;
		sizeValues.y = height;

		int finalSize = width*height;

		for (int i = 0; i < finalSize; i++)
		{
			pixels.push_back(defaultColor);
		}
	}

	/*
	Image(int width, int height, Color* colorArray, Color)
	{
		this->width = width;
		this->height = height;

		pixels = colorArray;
	}
	*/

	Color getPixel(int x, int y)
	{
		return pixels[x + (x*y)];
	}

	bool setPixel(int x, int y, Color pixel)
	{
		if ((x < 0) || (x > sizeValues.x) || (y < 0) || (y > sizeValues.y))
		{
			return false;
		}
		else
		{
			pixels[x + (sizeValues.x*y)] = pixel;
			return true;
		}
	}

	Size getSize()
	{
		return sizeValues;
	}

	//Not sure for default constructor
	//Have a constructor that allows setting of a default color across all of the array
	//Have a constructor that allows creation of an image from array of colors

	void getIntArray(int* intValues)
	{

		for (int i = 0; i < pixels.size(); i++)
		{
			intValues[i] = pixels[i].getInt();
		}

	}

	}

};


#endif