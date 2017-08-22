#include "PostProcessing.h"


Color mixColors(Color color1, Color color2)
{
	return Color((color1.r + color2.r) / 2, (color1.g + color2.g) / 2, (color1.b + color2.b) / 2, 0xFF);
}

Color mixColors(Color color1, Color color2, float div)
{
	return Color((color1.r + color2.r) / div, (color1.g + color2.g) / div, (color1.b + color2.b) / div, 0xFF);
}

Color linearInterpolation(Color color1, Color color2, float div)
{
	return Color((color1.r * (1.0 - div) + color2.r * div), (color1.g * (1.0 - div) + color2.g * div), (color1.b * (1.0 - div) + color2.b * div), 0xFF);
}

Color cosineInterpolation(Color color1, Color color2, float div)
{
	div = ((1 - cos(div * 3.14f)) / 2);

	int r = (color1.r * (1 - div) + (color2.r * div));
	int g = (color1.g * (1 - div) + (color2.g * div));
	int b = (color1.b * (1 - div) + (color2.b * div));

	return(Color(r, g, b, 0xFF));
}

Color cosineInterpolation4(Color color1, Color color2, Color color3, Color color4, float div)
{
	Color topInterpolation = cosineInterpolation(color1, color2, div);
	Color bottomInterpolation = cosineInterpolation(color3, color4, div);

	return cosineInterpolation(topInterpolation, bottomInterpolation, div);
}


Image eagleFilter(Image screen)
{
	int screenX = screen.getSize().x;
	int screenY = screen.getSize().y;

	Image scaledScreen(screenX * 2, screenY * 2, Color(0,0,0,255));

	Color pixel1;
	Color pixel2;
	Color pixel3;
	Color pixel4;

	for (int x = 1; x < (screenX - 1); x++) //This ensures every pixel indexed will not be an edge. It will always have 8 surrounding pixels.
	{
		for (int y = 1; y < (screenY - 1); y++)
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

	return scaledScreen;
}

/*
	Scale2X Scaling Algorithm by Andrea Mazzoleni.
*/
Image scale2XFilter(Image screen)
{
	Image scaledScreen(screen.getSize().x * 2, screen.getSize().y * 2, Color(0, 0, 0, 255));

	int screenX = screen.getSize().x;
	int screenY = screen.getSize().y;

	Color pixel1;
	Color pixel2;
	Color pixel3;
	Color pixel4;

	for (int x = 1; x < (screenX - 1); x++) //This ensures every pixel indexed will not be an edge. It will always have 8 surrounding pixels.
	{
		for (int y = 1; y < (screenY - 1); y++)
		{

			Color currentPixel = screen.getPixel(x, y); //Center
			Color upColor = screen.getPixel(x, y - 1); //Up
			Color downColor = screen.getPixel(x, y + 1); //Down
			Color leftColor = screen.getPixel(x - 1, y); //Left
			Color rightColor = screen.getPixel(x + 1, y); //Right

			if ( (leftColor == upColor) && (upColor != rightColor) && (leftColor != downColor) )
			{
				pixel1 = leftColor;
			}
			else
			{
				pixel1 = currentPixel;
			}

			if ( (upColor == rightColor) && (upColor != leftColor) && (rightColor != downColor) )
			{
				pixel2 = rightColor;
			}
			else
			{
				pixel2 = currentPixel;
			}

			if ( (leftColor == downColor) && (leftColor != upColor) && (downColor != rightColor))
			{
				pixel3 = leftColor;
			}
			else
			{
				pixel3 = currentPixel;
			}

			if ( (downColor == rightColor) && (leftColor != downColor) && (upColor != rightColor))
			{
				pixel4 = rightColor;
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

	return scaledScreen;
}

/*
	Scale3X Scaling Algorithm by Andrea Mazzoleni.
*/
Image scale3XFilter(Image screen)
{
	Image scaledScreen(screen.getSize().x * 3, screen.getSize().y * 3, Color(0, 0, 0, 255));

	int screenX = screen.getSize().x;
	int screenY = screen.getSize().y;

	Color pixel0;
	Color pixel1;
	Color pixel2;

	Color pixel3;
	Color pixel4;
	Color pixel5;

	Color pixel6;
	Color pixel7;
	Color pixel8;

	for (int x = 1; x < (screenX - 1); x++) //This ensures every pixel indexed will not be an edge. It will always have 8 surrounding pixels.
	{
		for (int y = 1; y < (screenY - 1); y++)
		{

			Color currentPixel = screen.getPixel(x, y);

			Color upColor = screen.getPixel(x, y - 1); 
			Color downColor = screen.getPixel(x, y + 1); 
			Color leftColor = screen.getPixel(x - 1, y); 
			Color rightColor = screen.getPixel(x + 1, y);

			Color upLeftColor = screen.getPixel(x - 1, y - 1);
			Color upRightColor = screen.getPixel(x + 1, y - 1);
			Color downLeftColor = screen.getPixel(x - 1, y + 1);
			Color downRightColor = screen.getPixel(x + 1, y + 1);

			//E0
			if ((leftColor ==  upColor) && (upColor != rightColor) && (leftColor != downColor))
			{
				pixel0 = leftColor;
			}
			else
			{
				pixel0 = currentPixel;
			}

			//E1
			if ( ( (leftColor == upColor) && (upColor != rightColor) && (leftColor != downColor) && (currentPixel != upRightColor) )
				|| ( (upColor == rightColor) && (leftColor != upColor) && (downColor != rightColor) && (currentPixel != upLeftColor) ))
			{
				pixel1 = upColor;
			}
			else
			{
				pixel1 = currentPixel;
			}

			//E2
			if ( (upColor == rightColor) && (upColor != leftColor) && (rightColor != downColor) )
			{
				pixel2 = rightColor;
			}
			else
			{
				pixel2 = currentPixel;
			}

			//E3
			if ( ((leftColor == upColor) &&  (upColor != rightColor) && (leftColor !=  downColor) && (currentPixel != downLeftColor))
				|| ( (leftColor == downColor) && (leftColor != upColor) && (downColor != rightColor) && (currentPixel != upLeftColor)))
			{
				pixel3 = leftColor;
			}
			else
			{
				pixel3 = currentPixel;
			}

			//E4
			pixel4 = currentPixel;


			//E5
			if ( ( (upColor == rightColor) && (upColor != leftColor) && (rightColor != downColor) && (currentPixel != downRightColor) )  || ( (downColor == rightColor) && (leftColor != downColor) && (upColor != rightColor) && (currentPixel != upRightColor) ) )
			{
				pixel5 = rightColor;
			}
			else
			{
				pixel5 = currentPixel;
			}

			//E6
			if ( (leftColor == downColor) && (leftColor != upColor) && (downColor != rightColor) )
			{
				pixel6 = leftColor;
			}
			else
			{
				pixel6 = currentPixel;
			}

			//E7
			if ( ( (leftColor == downColor) && (leftColor != upColor) && (downColor != rightColor) && (currentPixel != downRightColor) ) 
				|| ( (downColor == rightColor) && (leftColor != downColor) && (upColor != rightColor) && (currentPixel != downLeftColor)))
			{
				pixel7 = downColor;
			}
			else
			{
				pixel7 = currentPixel;
			}

			//E8
			if ( (downColor == rightColor) && (leftColor != downColor) && (upColor != rightColor))
			{
				pixel8 = rightColor;
			}
			else
			{
				pixel8 = currentPixel;
			}


			scaledScreen.setPixel(x * 3, y * 3, pixel0);
			scaledScreen.setPixel((x * 3) + 1, y * 3, pixel1);
			scaledScreen.setPixel((x * 3) + 2, y * 3, pixel2);
			scaledScreen.setPixel(x * 3, (y * 3) + 1, pixel3);
			scaledScreen.setPixel((x * 3) + 1, (y * 3) + 1, pixel4);
			scaledScreen.setPixel((x * 3) + 2, (y * 3) + 1, pixel5);
			scaledScreen.setPixel((x * 3), (y * 3) + 2, pixel6);
			scaledScreen.setPixel((x * 3) + 1, (y * 3) + 2, pixel7);
			scaledScreen.setPixel((x * 3) + 2, (y * 3) + 2, pixel8);

		}
	}

	return scaledScreen;
}

Image emboldenFilter(Image screen)
{
	for (int x = 0; x < 159; x++)
	{
		for (int y = 0; y < 144; y++)
		{
			Color pixel1 = screen.getPixel(x, y);
			Color pixel2 = screen.getPixel(x + 1, y);

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
				if (y < 143)
				{
					if (x > 0)
					{
						if (screen.getPixel(x - 1, y + 1) == blackPixel) //if Down-Left pixel is black
						{
							screen.setPixel(x - 1, y, mixColors(pixel1, screen.getPixel(x - 1, y), 3.5)); //Left
						}
					}

					if (x < 159)
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

Image blurFilter(Image screen)
{
	
	for (int x = 0; x < 160; x++)
	{
		for (int y = 0; y < 144; y++)
		{
			Color pixel1 = screen.getPixel(x, y);

			if (y > 0)
			{
				if (x > 0)
				{
					pixel1 = mixColors(pixel1, screen.getPixel(x - 1, y - 1)); //Up-Left
					pixel1 = mixColors(pixel1, screen.getPixel(x - 1, y)); //Left
				}

				if (x < 159)
				{
					pixel1 = mixColors(pixel1, screen.getPixel(x + 1, y - 1)); //Up-Right
					pixel1 = mixColors(pixel1, screen.getPixel(x + 1, y)); //Right
				}

				pixel1 = mixColors(pixel1, screen.getPixel(x, y - 1)); //Up

			}

			if (y < 143)
			{
				if (x > 0)
				{
					pixel1 = mixColors(pixel1, screen.getPixel(x - 1, y + 1)); //Down-Left
				}

				if (x < 160)
				{
					pixel1 = mixColors(pixel1, screen.getPixel(x + 1, y + 1)); //Down-Right
				}

				pixel1 = mixColors(pixel1, screen.getPixel(x, y + 1)); //Down
			}

			screen.setPixel(x, y, pixel1);
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
							screen.setPixel(x - 1, y, mixColors(pixel1, screen.getPixel(x - 1, y), 2)); //Left
						}
					}

					if (x < 159)
					{
						if (screen.getPixel(x + 1, y - 1) == blackPixel) //if Up-Right pixel is black
						{
							screen.setPixel(x + 1, y, mixColors(pixel1, screen.getPixel(x + 1, y), 2));; //Right
						}
					}

				}

				if (y < 143)
				{
					if (x > 0)
					{
						if (screen.getPixel(x - 1, y + 1) == blackPixel) //if Down-Left pixel is black
						{
							screen.setPixel(x - 1, y, mixColors(pixel1, screen.getPixel(x - 1, y), 2)); //Left
						}
					}

					if (x < 159)
					{
						if (screen.getPixel(x + 1, y + 1) == blackPixel) //if Down-Right pixel is black
						{
							screen.setPixel(x + 1, y, mixColors(pixel1, screen.getPixel(x + 1, y), 2)); //Right
						}
					}
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

Image lcdFilter1(Image screen)
{

	for (int y = 0; y < 144; y += 2)
	{
		for (int x = 0; x < 160; x++)
		{
			screen.setPixel(x, y, mixColors(screen.getPixel(x, y), Color(50, 50, 50, 255)));
		}
	}

	return screen;
}


/*
	2xSaI Scaling Algorithm by Derek Liauw Kie Fa. 
*/
Image saI2X(Image screen)
{

	auto compareColors = [](auto color1, auto color2, auto color3, auto color4, auto invert)
	{
		int a = 0, b = 0, c = 0;

		if (color1 == color3)
		{
			a++;
		}
		else if (color2 == color3)
		{
			b++;
		}

		if (color1 == color4)
		{
			a++;
		}
		else if (color2 == color4)
		{
			b++;
		}

		if (!invert)
		{
			if (a <= 1)
			{
				c++;
			}

			if (b <= 1)
			{
				c--;
			}
		}
		else
		{

			if (a <= 1)
			{
				c--;
			}

			if (b <= 1)
			{
				c++;
			}
		}

		return c;
	};

	int screenX = screen.getSize().x;
	int screenY = screen.getSize().y;

	Image scaledScreen(screenX * 2, screenY * 2);

	Color a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;

	Color color1, color2, color3;

	for (int y = 0; y < screenY; y++)
	{

		for (int x = 0; x < screenX; x++)
		{
			/*
			A B C D
			E F G H
			I J K L
			M N O P

			F is current pixel
			*/

			if (x < 1)
			{
				if (y > 0)
				{
					a = screen.getPixel(x - 1, y - 1);
					b = screen.getPixel(x, y - 1);
					c = screen.getPixel(x + 1, y - 1);
					d = screen.getPixel(x + 2, y - 1);
				}
				else
				{
					a = screen.getPixel(x - 1, y);
					b = screen.getPixel(x, y);
					c = screen.getPixel(x + 1, y);
					d = screen.getPixel(x + 2, y);
				}

				e = screen.getPixel(x - 1, y);
				f = screen.getPixel(x, y);
				g = screen.getPixel(x + 1, y);
				h = screen.getPixel(x + 2, y);


				if((y + 1) <= screenY)
				{
					i = screen.getPixel(x - 1, y + 1);
					j = screen.getPixel(x, y + 1);
					k = screen.getPixel(x + 1, y + 1);
					l = screen.getPixel(x + 2, y + 1);
				}
				else
				{
					i = e;
					j = f;
					k = g;
					l = h;
				}

				if((y + 2) <= screenY)
				{
					m = screen.getPixel(x - 1, y + 2);
					n = screen.getPixel(x, y + 2);
					o = screen.getPixel(x + 1, y + 2);
					p = screen.getPixel(x + 2, y + 2);
				}
				else
				{
					m = i;
					n = j;
					o = k;
					p = l;
				}
			}
			else
			{
				if (y > 0)
				{
					a = screen.getPixel(x, y - 1);
					b = screen.getPixel(x, y - 1);
					c = screen.getPixel(x + 1, y - 1);
					d = screen.getPixel(x + 2, y - 1);
				}
				else
				{
					a = screen.getPixel(x, y);
					b = screen.getPixel(x, y);
					c = screen.getPixel(x + 1, y);
					d = screen.getPixel(x + 2, y);
				}

				e = screen.getPixel(x, y);
				f = screen.getPixel(x, y);
				g = screen.getPixel(x + 1, y);
				h = screen.getPixel(x + 2, y);

				i = screen.getPixel(x, y + 1);
				j = screen.getPixel(x, y + 1);
				k = screen.getPixel(x + 1, y + 1);
				l = screen.getPixel(x + 2, y + 1);

				m = screen.getPixel(x, y + 2);
				n = screen.getPixel(x, y + 2);
				o = screen.getPixel(x + 1, y + 2);
				p = screen.getPixel(x + 2, y + 2);
			}


			if ((f == k) && (g != j))
			{
				if (((f == b) && (g == l)) || ((f == j) && (f == c) && (g != b) && (g == d)))
				{
					color1 = f;
				}
				else
				{
					color1 = cosineInterpolation(f, g, .5);
				}

				if (((f == e) && (j == o)) || ((f == g) && (f == i) && (e != j) && (j == m)))
				{
					color2 = f;
				}
				else
				{
					color2 = cosineInterpolation(f, j, .5);
				}

				color3 = f;

			}
			else if ((g == j) && (f != k))
			{
				if (((g == c) && (f == i)) || ((g == b) && (g == k) && (f != c) && (h == i)))
				{
					color1 = g;
				}
				else
				{
					color1 = cosineInterpolation(f, g, .5);
				}

				if (((j == i) && (f == c)) || ((j == e) && (j == k) && (f != i) && (f == a)))
				{
					color2 = j;
				}
				else
				{
					color2 = cosineInterpolation(f, j, .5);
				}

				color3 = g;
			}
			else if ((f == k) && (g == j))
			{

				if (f == g)
				{
					color1 = f;
					color2 = f;
					color3 = f;
				}
				else
				{
					color1 = cosineInterpolation(f, j, .5);
					color2 = cosineInterpolation(f, g, .5);

					int compareValue = 0;

					compareValue += compareColors(f, g, e, b, false);
					compareValue += compareColors(g, f, h, c, true);
					compareValue += compareColors(g, f, i, n, true);
					compareValue += compareColors(f, g, l, o, false);

					if (compareValue > 0)
					{
						color3 = f;
					}
					else if (compareValue < 0)
					{
						color3 = g;
					}
					else
					{
						color3 = cosineInterpolation4(f, g, j, k, .5);
					}
				}

			}
			else
			{
				color3 = cosineInterpolation4(f, g, j, k, .5);

				if ((f == j) && (f == c) && (g != b) && (g == d))
				{
					color1 = f;
				}
				else if ((g == b) && (g == k) && (f != c) && (a == f))
				{
					color1 = g;
				}
				else
				{
					color1 = cosineInterpolation(f, g, .5);
				}

				if ((f == g) && (f == i) && (e != j) && (j == m))
				{
					color2 = f;
				}
				else if ((j == e) && (j == k) && (f != i) && (a == f))
				{
					color2 = j;
				}
				else
				{
					color2 = cosineInterpolation(f, j, .5);
				}

			}

			scaledScreen.setPixel((x * 2), (y * 2), f);
			scaledScreen.setPixel((x * 2) + 1, (y * 2), color1);
			scaledScreen.setPixel((x * 2), (y * 2) + 1, color2);
			scaledScreen.setPixel((x * 2) + 1, (y * 2) + 1, color3);

		}

	}

	return scaledScreen;
}

/*
	Super 2xSaI Scaling Algorithm by Derek Liauw Kie Fa.
*/
Image super2xSaI(Image screen)
{

	auto compareColors = [](auto color1, auto color2, auto color3, auto color4, auto invert)
	{
		int a = 0, b = 0, c = 0;

		if (color1 == color3)
		{
			a++;
		}
		else if (color2 == color3)
		{
			b++;
		}

		if (color1 == color4)
		{
			a++;
		}
		else if (color2 == color4)
		{
			b++;
		}

		if (!invert)
		{
			if (a <= 1)
			{
				c++;
			}

			if (b <= 1)
			{
				c--;
			}
		}
		else
		{

			if (a <= 1)
			{
				c--;
			}

			if (b <= 1)
			{
				c++;
			}
		}

		return c;
	};

	int screenX = screen.getSize().x;
	int screenY = screen.getSize().y;

	Image scaledScreen(screenX * 2, screenY * 2);

	Color a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;

	Color color1, color2, color3, color4;

	for (int y = 0; y < screenY; y++)
	{

		for (int x = 0; x < screenX; x++)
		{
			/*
			A B C D
			E F G H
			I J K L
			M N O P

			F is current pixel
			*/

			if (x < 1)
			{
				if (y > 0)
				{
					a = screen.getPixel(x - 1, y - 1);
					b = screen.getPixel(x, y - 1);
					c = screen.getPixel(x + 1, y - 1);
					d = screen.getPixel(x + 2, y - 1);
				}
				else
				{
					a = screen.getPixel(x - 1, y);
					b = screen.getPixel(x, y);
					c = screen.getPixel(x + 1, y);
					d = screen.getPixel(x + 2, y);
				}

				e = screen.getPixel(x - 1, y);
				f = screen.getPixel(x, y);
				g = screen.getPixel(x + 1, y);
				h = screen.getPixel(x + 2, y);


				if ((y + 1) <= 144)
				{
					i = screen.getPixel(x - 1, y + 1);
					j = screen.getPixel(x, y + 1);
					k = screen.getPixel(x + 1, y + 1);
					l = screen.getPixel(x + 2, y + 1);
				}
				else
				{
					i = e;
					j = f;
					k = g;
					l = h;
				}

				if ((y + 2) <= 144)
				{
					m = screen.getPixel(x - 1, y + 2);
					n = screen.getPixel(x, y + 2);
					o = screen.getPixel(x + 1, y + 2);
					p = screen.getPixel(x + 2, y + 2);
				}
				else
				{
					m = i;
					n = j;
					o = k;
					p = l;
				}
			}
			else
			{
				if (y > 0)
				{
					a = screen.getPixel(x, y - 1);
					b = screen.getPixel(x, y - 1);
					c = screen.getPixel(x + 1, y - 1);
					d = screen.getPixel(x + 2, y - 1);
				}
				else
				{
					a = screen.getPixel(x, y);
					b = screen.getPixel(x, y);
					c = screen.getPixel(x + 1, y);
					d = screen.getPixel(x + 2, y);
				}

				e = screen.getPixel(x, y);
				f = screen.getPixel(x, y);
				g = screen.getPixel(x + 1, y);
				h = screen.getPixel(x + 2, y);

				i = screen.getPixel(x, y + 1);
				j = screen.getPixel(x, y + 1);
				k = screen.getPixel(x + 1, y + 1);
				l = screen.getPixel(x + 2, y + 1);

				m = screen.getPixel(x, y + 2);
				n = screen.getPixel(x, y + 2);
				o = screen.getPixel(x + 1, y + 2);
				p = screen.getPixel(x + 2, y + 2);
			}


			if ((j == g) && (f != k))
			{
				color4 = j;
				color2 = j;
			}
			else if ((f == k) && (j != g))
			{
				color4 = f;
				color2 = f;
			}
			else if ((f == k) && (j == g))
			{
				int compareValue = 0;

				compareValue += compareColors(g, f, i, n, false); //done
				compareValue += compareColors(g, f, e, b, false);
				compareValue += compareColors(g, f, o, l, false);
				compareValue += compareColors(g, f, c, h, false); //done

				if (compareValue > 0)
				{
					color2 = g;
					color4 = g;
				}
				else if (compareValue < 0)
				{
					color2 = f;
					color4 = f;
				}
				else
				{
					color2 = cosineInterpolation(f, g, .5);
					color4 = cosineInterpolation(f, g, .5);
				}

				//color4 = color2;
			}
			else
			{
				if ((g == k) && (k == n) && (j != o) && (k != m))
				{
					color4 = cosineInterpolation4(k, k, k, j, .5);
				}
				else if ((f == j) && (j == o) && (n != k) && (j != p))
				{
					color4 = cosineInterpolation4(j, j, j, k, .5);
				}
				else
				{
					color4 = cosineInterpolation(j, k, .5);
				}

				if ((g == k) && (g == b) && (f != c) && (g != a))
				{
					color2 = cosineInterpolation4(g, g, g, f, .5);
				}
				else if ((f == j) && (f == c) && (b != g) && (f != d))
				{
					color2 = cosineInterpolation4(g, f, f, f, .5);
				}
				else
				{
					color2 = cosineInterpolation(f, g, .5);
				}
			}
				
			if ((f == k) && (j != g) && (e == f) && (f != o))
			{
				color3 = cosineInterpolation(j, f, .5);
			}
			else if ((f == i) && (g == f) && (e != j) && (f != m))
			{
				color3 = cosineInterpolation(f, j, .5);
			}
			else
			{
				color3 = j;
			}

			if ((j == g) && (f != k) && (i == j) && (j != c))
			{
				color1 = cosineInterpolation(j, f, .5);
			}
			else if ((e == j) && (k == j) && (i != f) && (j != a))
			{
				color1 = cosineInterpolation(f, j, .5);
			}
			else
			{
				color1 = f;
			}
				
			



			scaledScreen.setPixel((x * 2), (y * 2), color1);
			scaledScreen.setPixel((x * 2) + 1, (y * 2), color2);
			scaledScreen.setPixel((x * 2), (y * 2) + 1, color3);
			scaledScreen.setPixel((x * 2) + 1, (y * 2) + 1, color4);

		}

	}

	return scaledScreen;

}

/*
	Super Eagle Scaling Algorithm by Derek Liauw Kie Fa.
*/
Image superEagle(Image screen)
{

	auto compareColors = [](auto color1, auto color2, auto color3, auto color4, auto invert)
	{
		int a = 0, b = 0, c = 0;

		if (color1 == color3)
		{
			a++;
		}
		else if (color2 == color3)
		{
			b++;
		}

		if (color1 == color4)
		{
			a++;
		}
		else if (color2 == color4)
		{
			b++;
		}

		if (!invert)
		{
			if (a <= 1)
			{
				c++;
			}

			if (b <= 1)
			{
				c--;
			}
		}
		else
		{

			if (a <= 1)
			{
				c--;
			}

			if (b <= 1)
			{
				c++;
			}
		}

		return c;
	};

	int screenX = screen.getSize().x;
	int screenY = screen.getSize().y;

	Image scaledScreen(screen.getSize().x * 2, screen.getSize().y * 2);

	Color a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;

	Color color1, color2, color3, color4;

	for (int y = 0; y < screenY; y++)
	{

		for (int x = 0; x < screenX; x++)
		{
			/*
			A B C D
			E F G H
			I J K L
			M N O P

			F is current pixel
			*/

			if (x < 1)
			{
				if (y > 0)
				{
					a = screen.getPixel(x - 1, y - 1);
					b = screen.getPixel(x, y - 1);
					c = screen.getPixel(x + 1, y - 1);
					d = screen.getPixel(x + 2, y - 1);
				}
				else
				{
					a = screen.getPixel(x - 1, y);
					b = screen.getPixel(x, y);
					c = screen.getPixel(x + 1, y);
					d = screen.getPixel(x + 2, y);
				}

				e = screen.getPixel(x - 1, y);
				f = screen.getPixel(x, y);
				g = screen.getPixel(x + 1, y);
				h = screen.getPixel(x + 2, y);


				if ((y + 1) <= screenY)
				{
					i = screen.getPixel(x - 1, y + 1);
					j = screen.getPixel(x, y + 1);
					k = screen.getPixel(x + 1, y + 1);
					l = screen.getPixel(x + 2, y + 1);
				}
				else
				{
					i = e;
					j = f;
					k = g;
					l = h;
				}

				if ((y + 2) <= screenY)
				{
					m = screen.getPixel(x - 1, y + 2);
					n = screen.getPixel(x, y + 2);
					o = screen.getPixel(x + 1, y + 2);
					p = screen.getPixel(x + 2, y + 2);
				}
				else
				{
					m = i;
					n = j;
					o = k;
					p = l;
				}
			}
			else
			{
				if (y > 0)
				{
					a = screen.getPixel(x, y - 1);
					b = screen.getPixel(x, y - 1);
					c = screen.getPixel(x + 1, y - 1);
					d = screen.getPixel(x + 2, y - 1);
				}
				else
				{
					a = screen.getPixel(x, y);
					b = screen.getPixel(x, y);
					c = screen.getPixel(x + 1, y);
					d = screen.getPixel(x + 2, y);
				}

				e = screen.getPixel(x, y);
				f = screen.getPixel(x, y);
				g = screen.getPixel(x + 1, y);
				h = screen.getPixel(x + 2, y);

				i = screen.getPixel(x, y + 1);
				j = screen.getPixel(x, y + 1);
				k = screen.getPixel(x + 1, y + 1);
				l = screen.getPixel(x + 2, y + 1);

				m = screen.getPixel(x, y + 2);
				n = screen.getPixel(x, y + 2);
				o = screen.getPixel(x + 1, y + 2);
				p = screen.getPixel(x + 2, y + 2);
			}


			if ((j == g) && (f != k))
			{
				color2 = j;
				color3 = j;

				if ((i == j) || (g == c))
				{
					color1 = cosineInterpolation(j, f, .5);
					color1 = cosineInterpolation(j, color1, .5);
				}
				else
				{
					color1 = cosineInterpolation(f, g, .5);
				}

				if ((g == h) || (j == n))
				{
					color4 = cosineInterpolation(j, k, .5);
					color4 = cosineInterpolation(j, color4, .5);
				}
				else
				{
					color4 = cosineInterpolation(j, k, .5);
				}

			}
			else if ((f == k) && (j != g))
			{
				color4 = f;
				color1 = f;

				if ((b == f) && (k == l))
				{
					color2 = cosineInterpolation(f, g, .5);
					color2 = cosineInterpolation(f, color2, .5);
				}
				else
				{
					color2 = cosineInterpolation(f, g, .5);
				} 

				if ((k == o) || (e == f))
				{
					color3 = cosineInterpolation(f, j, .5);
					color3 = cosineInterpolation(f, color3, .5);
				}
				else
				{
					color3 = cosineInterpolation(j, k, .5);
				}
			}
			else if ((f == k) && (g == j))
			{

				int compareValue = 0;

				compareValue += compareColors(g, f, i, n, false);
				compareValue += compareColors(g, f, e, b, false);
				compareValue += compareColors(g, f, o, l, false);
				compareValue += compareColors(g, f, c, h, false);

				if (compareValue > 0)
				{
					color2 = j;
					color3 = j;
					color1 = cosineInterpolation(f, g, .5);
					color4 = cosineInterpolation(f, g, .5);
				}
				else if (compareValue < 0)
				{
					color4 = f;
					color1 = f;
					color2 = cosineInterpolation(f, g, .5);
					color3 = cosineInterpolation(f, g, .5);
				}
				else
				{
					color4 = f;
					color1 = f;
					color2 = j;
					color3 = j;
				}
				

			}
			else
			{
				color4 = cosineInterpolation(j, g, .5);
				color1 = cosineInterpolation(j, g, .5);
				color4 = cosineInterpolation4(k, k, k, color4, .5);
				color1 = cosineInterpolation4(f, f, f, color1, .5);

				color3 = cosineInterpolation(f, k, .5);
				color2 = cosineInterpolation(f, k, .5);
				color3 = cosineInterpolation4(j, j, j, color3, .5);
				color2 = cosineInterpolation4(g, g, g, color2, .5);


			}

			scaledScreen.setPixel((x * 2), (y * 2), color1);
			scaledScreen.setPixel((x * 2) + 1, (y * 2), color2);
			scaledScreen.setPixel((x * 2), (y * 2) + 1, color3);
			scaledScreen.setPixel((x * 2) + 1, (y * 2) + 1, color4);

		}

	}

	return scaledScreen;
}

/*
	xBR Scaling Algorithm by Hyllian.
*/
Image xBR2(Image screen)
{
	/*
	   a  b  c
	d  e  f  g  h
	i  j  k  l  m
	n  o  p  q  r
	   s  t  u
	
	Current pixel is k
	*/

	auto compareColors = [](auto color1, auto color2)
	{
		int y = (abs(color1.r - color2.r) * .299f) + (abs(color1.g - color2.g) * .587f) + (abs(color1.b - color2.b) * .114f);
		int u = (abs(color1.r - color2.r) * -.168736f) + (abs(color1.g - color2.g) * -.331264f) + (abs(color1.b - color2.b) * .5f);
		int v = (abs(color1.r - color2.r) * .5f) + (abs(color1.g - color2.g) * -.418688f) + (abs(color1.b - color2.b) * 0.081312f);

		return (y * 48) + (u * 7) + (v * 6); //Multiplication values can be modified for different results
	};

	int screenX = screen.getSize().x;
	int screenY = screen.getSize().y;

	Image scaledScreen(screen.getSize().x * 2, screen.getSize().y * 2);

	Color a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u;

	int xOffsetLeftEndRow = 0;
	int xOffsetLeftInnerRow = 0;
	int xOffsetRightEndRow = 0;
	int xOffsetRightInnerRow = 0;
	int yOffsetTopEndRow = 0;
	int yOffsetTopInnerRow = 0;
	int yOffsetBottomEndRow = 0;
	int yOffsetBottomInnerRow = 0;

	Color color1, color2, color3, color4;

	for (int y = 0; y < screenY; y++)
	{
		for (int x = 0; x < screenX; x++)
		{
			//Keeps from indexing pixels before the top side of the image
			if (y < 4)
			{
				if (y > 1) //No offset needed
				{
					yOffsetTopEndRow = 0;
					yOffsetTopInnerRow = 0;
				}
				else if (y == 1)
				{
					yOffsetTopEndRow = 1;
					yOffsetTopInnerRow = 0;
				}
				else
				{
					yOffsetTopEndRow = 2;
					yOffsetTopInnerRow = 1;
				}
			}
			else
			{
				//Keeps from indexing pixels past the bottom side of the image
				if (y < (screenY - 2))
				{
					yOffsetBottomEndRow = 0;
					yOffsetBottomInnerRow = 0;
				}
				else if (y == (screenY - 2))
				{
					yOffsetBottomEndRow = -1;
					yOffsetBottomInnerRow = 0;
				}
				else
				{
					 yOffsetBottomEndRow = -2;
					 yOffsetBottomInnerRow = -1;
				}
			}

			//Keeps from indexing pixels before the left side of the image
			if (x < 4)
			{

				if (x > 1)
				{
					xOffsetLeftEndRow = 0;
					xOffsetLeftInnerRow = 0;
				}
				else if (x == 1)
				{
					xOffsetLeftEndRow = 1;
					xOffsetLeftInnerRow = 0;
				}
				else
				{
					xOffsetLeftEndRow = 2;
					xOffsetLeftInnerRow = 1;
				}
			}
			else
			{
				//Keeps from indexing pixels past the right side of the image
				if (x < (screenX - 2))
				{
					xOffsetRightEndRow = 0;
					xOffsetRightInnerRow = 0;
				}
				else if (x == (screenX - 2))
				{
					xOffsetRightEndRow = -1;
					xOffsetRightInnerRow = 0;
				}
				else
				{
					xOffsetRightEndRow = -2;
					xOffsetRightInnerRow = -1;
				}
			}



			//First 3 Colors: Row 1
			a = screen.getPixel(x - 1 + xOffsetLeftInnerRow, y - 2 + yOffsetTopEndRow);
			b = screen.getPixel(x, y - 2 + yOffsetTopEndRow);
			c = screen.getPixel(x + 1 + xOffsetRightInnerRow, y - 2 + yOffsetTopEndRow);
	
			//Next 5 Colors: Row 2
			d = screen.getPixel(x - 2 + xOffsetLeftEndRow, y - 1 + yOffsetTopInnerRow);
			e = screen.getPixel(x - 1 + xOffsetLeftInnerRow, y - 1 + yOffsetTopInnerRow);
			f = screen.getPixel(x, y - 1 + yOffsetTopInnerRow);
			g = screen.getPixel(x + 1 + xOffsetRightInnerRow, y - 1 + yOffsetTopInnerRow);
			h = screen.getPixel(x + 2 + xOffsetRightEndRow, y - 1 + yOffsetTopInnerRow);

			//Next 5 Colors: Row 3
			i = screen.getPixel(x - 2 + +xOffsetLeftEndRow, y);
			j = screen.getPixel(x - 1 + xOffsetLeftInnerRow, y);
			k = screen.getPixel(x, y);
			l = screen.getPixel(x + 1 + xOffsetRightInnerRow, y);
			m = screen.getPixel(x + 2 + +xOffsetRightEndRow, y);

			//Next 5 Colors: Row 4
			n = screen.getPixel(x - 2 + +xOffsetLeftEndRow, y + 1 + yOffsetBottomInnerRow);
			o = screen.getPixel(x - 1 + xOffsetLeftInnerRow, y + 1 + yOffsetBottomInnerRow);
			p = screen.getPixel(x, y + 1 + yOffsetBottomInnerRow);
			q = screen.getPixel(x + 1 + xOffsetRightInnerRow, y + 1 + yOffsetBottomInnerRow);
			r = screen.getPixel(x + 2 + +xOffsetRightEndRow, y + 1 + yOffsetBottomInnerRow);

			//Last 3 Colors: Row 5
			s = screen.getPixel(x - 1 + xOffsetLeftInnerRow, y + 2 + yOffsetBottomEndRow);
			t = screen.getPixel(x, y + 2 + yOffsetBottomEndRow);
			u = screen.getPixel(x + 1 + xOffsetRightInnerRow, y + 2 + yOffsetBottomEndRow);



			int comparison_k_j = compareColors(k, j);
			int comparison_k_f = compareColors(k, f);
			int comparison_k_l = compareColors(k, l);
			int comparison_k_p = compareColors(k, p);
			int comparison_k_o = compareColors(k, o);
			int comparison_k_g = compareColors(k, g);
			int comparison_e_i = compareColors(e, i);
			int comparison_e_b = compareColors(e, b);
			int comparison_j_f = compareColors(j, f);
			int comparison_j_p = compareColors(j, p);
			int comparison_j_d = compareColors(j, d);
			int comparison_f_l = compareColors(f, l);
			int comparison_f_a = compareColors(f, a);
			int comparison_k_e = compareColors(k, e);
			int comparison_k_q = compareColors(k, q);
			int comparison_g_m = compareColors(g, m);
			int comparison_g_b = compareColors(g, b);
			int comparison_l_p = compareColors(l, p);
			int comparison_l_h = compareColors(l, h);
			int comparison_f_c = compareColors(f, c);
			int comparison_o_i = compareColors(o, i);
			int comparison_o_t = compareColors(o, t);
			int comparison_p_s = compareColors(p, s);
			int comparison_j_n = compareColors(j, n);
			int comparison_q_m = compareColors(q, m);
			int comparison_q_t = compareColors(q, t);
			int comparison_p_u = compareColors(p, u);
			int comparison_p_r = compareColors(p, r);

			int detectUpRightDiagonalLine = (comparison_k_o + comparison_k_g + comparison_e_i + comparison_e_b + (4 * comparison_j_f));
			int detectDownRightDiagonalLine = (comparison_j_p + comparison_j_d + comparison_f_l + comparison_f_a + (4 * comparison_k_e));

			//Upper-Left Line Detection
			if (detectUpRightDiagonalLine < detectDownRightDiagonalLine)
			{
				if (comparison_k_j <= comparison_k_f)
				{
					color1 = cosineInterpolation(j, k, .5);
				}
				else
				{
					color1 = cosineInterpolation(f, k, .5);
				}
			}
			else
			{
				color1 = k;
			}

			detectDownRightDiagonalLine = (comparison_k_q + comparison_k_e + comparison_g_m + comparison_g_b + (4 * comparison_f_l));
			detectUpRightDiagonalLine = (comparison_l_p + comparison_l_h + comparison_j_f + comparison_f_c + (4 * comparison_k_g));

			//Upper-Right Line Detection
			if (detectDownRightDiagonalLine < detectUpRightDiagonalLine)
			{
				if (comparison_k_f <= comparison_k_l)
				{
					color2 = cosineInterpolation(f, k, .5);
				}
				else
				{
					color2 = cosineInterpolation(l, k, .5);
				}
			}
			else
			{
				color2 = k;
			}

			detectDownRightDiagonalLine = (comparison_k_e + comparison_k_q + comparison_o_i + comparison_o_t + (4 * comparison_j_p));
			detectUpRightDiagonalLine = (comparison_j_f + comparison_j_n + comparison_l_p + comparison_p_s + (4 * comparison_k_o));

			//Lower-Left Line Detection
			if (detectDownRightDiagonalLine < detectUpRightDiagonalLine)
			{
				if (comparison_k_j <= comparison_k_p)
				{
					color3 = cosineInterpolation(j, k, .5);
				}
				else
				{
					color3 = cosineInterpolation(p, k, .5);
				}
			}
			else
			{
				color3 = k;
			}


			detectUpRightDiagonalLine = (comparison_k_g + comparison_k_o + comparison_q_m + comparison_q_t + (4 * comparison_l_p));
			detectDownRightDiagonalLine = (comparison_j_p + comparison_p_u + comparison_p_r + comparison_f_l + (4 * comparison_k_q));

			//Lower-Right Line Detection
			if (detectUpRightDiagonalLine < detectDownRightDiagonalLine)
			{
				if (comparison_k_l <= comparison_k_p)
				{
					color4 = cosineInterpolation(l, k, .5);
				}
				else
				{
					color4 = cosineInterpolation(p, k, .5);
				}
			}
			else
			{
				color4 = k;
			}


			scaledScreen.setPixel((x * 2), (y * 2), color1);
			scaledScreen.setPixel((x * 2) + 1, (y * 2), color2);
			scaledScreen.setPixel((x * 2), (y * 2) + 1, color3);
			scaledScreen.setPixel((x * 2) + 1, (y * 2) + 1, color4);
		}
	}

	return scaledScreen;
}

Image filterSelect(Image screen, byte filterNumber)
{

	if (filterNumber == 1)
	{
		return eagleFilter(screen);
	}
	if (filterNumber == 2)
	{
		return scale2XFilter(screen);
	}
	if (filterNumber == 3)
	{
		return scale3XFilter(screen);
	}
	if (filterNumber == 4)
	{
		return blurFilter(screen);
	}
	if (filterNumber == 5)
	{
		return customFilter(screen);
	}
	if (filterNumber == 6)
	{
		return zigZagFilter(screen);
	}
	if (filterNumber == 7)
	{
		return rainbowFilter(screen);
	}
	if (filterNumber == 8)
	{
		return lcdFilter1(screen);
	}
	if (filterNumber == 9)
	{
		return superEagle(screen);
	}
	if (filterNumber == 10)
	{
		return saI2X(screen);
	}
	if (filterNumber == 11)
	{
		return super2xSaI(screen);
	}
	if (filterNumber == 12)
	{
		return xBR2(screen);
	}
	else
	{
		return screen;
	}
}
