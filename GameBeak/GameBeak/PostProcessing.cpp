#include "PostProcessing.h"


Color mixColors(Color color1, Color color2)
{
	return Color((color1.r + color2.r) / 2, (color1.g + color2.g) / 2, (color1.b + color2.b) / 2, 0xFF);
}

Color mixColors(Color color1, Color color2, float div)
{
	return Color((color1.r + color2.r) / div, (color1.g + color2.g) / div, (color1.b + color2.b) / div, 0xFF);
}



Image eagleFilter(Image screen)
{
	Image scaledScreen;
	scaledScreen.create(screen.getSize().x * 2, screen.getSize().y * 2, Color(0,0,0,255));

	Color pixel1;
	Color pixel2;
	Color pixel3;
	Color pixel4;

	for (int x = 1; x < (screen.getSize().x - 1); x++) //This ensures every pixel indexed will not be an edge. It will always have 8 surrounding pixels.
	{
		for (int y = 1; y < (screen.getSize().y - 1); y++)
		{

			Color currentPixel = screen.getPixel(x, y);
			Color compareColor = screen.getPixel(x - 1, y); //Left

			if ((screen.getPixel(x - 1, y - 1) == compareColor) && (screen.getPixel(x, y - 1) == compareColor)) //Up-Left & Up
			{
				pixel1 = compareColor;
			}
			else
			{
				pixel1 = currentPixel;
			}

			compareColor = screen.getPixel(x, y - 1); //Up
			if ((screen.getPixel(x + 1, y - 1) == compareColor) && (screen.getPixel(x + 1, y) == compareColor)) //Up-Right & Right
			{
				pixel2 = compareColor;
			}
			else
			{
				pixel2 = currentPixel;
			}

			compareColor = screen.getPixel(x - 1, y); //Left
			if ((screen.getPixel(x - 1, y - 1) == compareColor) && (screen.getPixel(x, y - 1) == compareColor)) //Down-Left & Down
			{
				pixel3 = compareColor;
			}
			else
			{
				pixel3 = currentPixel;
			}

			compareColor = screen.getPixel(x + 1, y); //Right
			if ((screen.getPixel(x + 1, y + 1) == compareColor) && (screen.getPixel(x, y + 1) == compareColor)) //Down-Right & Down
			{
				pixel4 = compareColor;
			}
			else
			{
				pixel4 = currentPixel;
			}

			scaledScreen.setPixel(x * 2, y * 2, pixel1);
			scaledScreen.setPixel((x * 2) + 1, y * 2, pixel2);
			scaledScreen.setPixel(x * 2, (y * 2) + 1, pixel3);
			scaledScreen.setPixel((x * 2) + 1, (y * 2) + 1, pixel4);

		}
	}
	/*
	for (int i = 0; i < 160; i++)
	{
		Color oldPixel1 = screen.getPixel(i, 0);

		scaledScreen.setPixel((i * 2) + 1, 0, oldPixel1);
		scaledScreen.setPixel((i * 2), 0, oldPixel1);
		scaledScreen.setPixel((i * 2) + 1, 1, oldPixel1);
		scaledScreen.setPixel((i * 2), 1, oldPixel1);

		Color oldPixel2 = screen.getPixel(i, 143);

		scaledScreen.setPixel((i * 2) + 1, (143 * 2), oldPixel2);
		scaledScreen.setPixel((i * 2), (143 * 2) + 1, oldPixel2);
		scaledScreen.setPixel((i * 2) + 1, (143 * 2) + 1, oldPixel2);
		scaledScreen.setPixel((i * 2), (143 * 2), oldPixel2);
	}

	for (int i = 1; i < 143; i++)
	{
		Color oldPixel1 = screen.getPixel(0, i);

		scaledScreen.setPixel(0, (i * 2) + 1, oldPixel1);
		scaledScreen.setPixel(0, (i * 2), oldPixel1);
		scaledScreen.setPixel(1, (i * 2) + 1, oldPixel1);
		scaledScreen.setPixel(1, (i * 2), oldPixel1);

		Color oldPixel2 = screen.getPixel(159, i);

		scaledScreen.setPixel((159 * 2), (i * 2) + 1, oldPixel2);
		scaledScreen.setPixel((159 * 2) + 1, (i * 2), oldPixel2);
		scaledScreen.setPixel((159 * 2) + 1, (i * 2) + 1, oldPixel2);
		scaledScreen.setPixel((159 * 2), (i * 2), oldPixel2);
	}
	
	*/

	return scaledScreen;
}

Image blurFilter(Image screen)
{
	for (int x = 0; x < 159; x++)
	{
		for (int y = 0; y < 144; y++)
		{
			sf::Color pixel1 = screen.getPixel(x, y);
			sf::Color pixel2 = screen.getPixel(x + 1, y);

			screen.setPixel(x, y, pixel1*pixel2);
		}
	}

	return screen;
}

Image customFilter(Image screen)
{
	for (int x = 0; x < 160; x++)
	{
		for (int y = 0; y < 144; y++)
		{
			Color blackPixel = beakGPU.returnColor(3);
			Color pixel1 = screen.getPixel(x, y);

			if (pixel1 == blackPixel)
			{
				if (y < 144)
				{
					if (x > 0)
					{
						if (screen.getPixel(x - 1, y + 1) == blackPixel) //if Down-Left pixel is black
						{
							screen.setPixel(x - 1, y, mixColors(pixel1, screen.getPixel(x - 1, y), 3.5)); //Left
						}
					}

					if (x < 160)
					{
						if (screen.getPixel(x + 1, y + 1) == blackPixel) //if Down-Right pixel is black
						{
							screen.setPixel(x + 1, y, mixColors(pixel1, screen.getPixel(x + 1, y), 3.5)); //Right
						}
					}

					//screen.setPixel(x, y + 1, mixColors(pixel1, screen.getPixel(x, y + 1))); //Down
				}
			}
		}
	}

	return screen;
}

Image zigZagFilter(Image screen)
{
	for (int x = 0; x < 160; x++)
	{
		for (int y = 0; y < 144; y += 2)
		{
			sf::Color blackPixel = beakGPU.returnColor(3);
			sf::Color pixel1 = screen.getPixel(x, y);

			if (pixel1 == blackPixel)
			{
				if (y > 0)
				{
					if (x > 0)
					{
						if (screen.getPixel(x - 1, y - 1) == blackPixel) //if Up-Left pixel is black
						{
							screen.setPixel(x - 1, y, mixColors(pixel1, screen.getPixel(x - 1, y), 2)); //Left
						}
					}

					if (x < 160)
					{
						if (screen.getPixel(x + 1, y - 1) == blackPixel) //if Up-Right pixel is black
						{
							screen.setPixel(x + 1, y, mixColors(pixel1, screen.getPixel(x + 1, y), 2));; //Right
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
							screen.setPixel(x - 1, y, mixColors(pixel1, screen.getPixel(x - 1, y), 2)); //Left
						}
					}

					if (x < 160)
					{
						if (screen.getPixel(x + 1, y + 1) == blackPixel) //if Down-Right pixel is black
						{
							screen.setPixel(x + 1, y, mixColors(pixel1, screen.getPixel(x + 1, y), 2)); //Right
						}
					}

					//screen.setPixel(x, y + 1, mixColors(pixel1, screen.getPixel(x, y + 1))); //Down
				}
			}
		}
	}


	return screen;
}

Image rainbowFilter(Image screen)
{
	for (int x = 0; x < 160; x++)
	{
		for (int y = 0; y < 144; y++)
		{
			Color pixel1 = screen.getPixel(x, y);

			screen.setPixel(x, y, mixColors(pixel1, Color(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0, 0xFF), 3.5));
		}
	}
	return screen;
}




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



Image filterSelect(Image screen, byte filterNumber)
{
	if (filterNumber == 0)
	{
		return eagleFilter(screen);
	}
	else
	{
		return screen;
	}
}
