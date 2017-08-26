#include "GameWindow.h"
#include "PostProcessing.h"
#include "Main.h"
#include "Color.h"
#include "Image.h"
#include <Windows.h>

GameWindow::GameWindow(string title, int width, int height)
{
	//Set Window
	//window = new RenderWindow(VideoMode(width, height), title);
	//window.create(VideoMode(width, height), title);
	//window.setFramerateLimit(60);
	//texture.create(160, 144);
	screen = Image(160, 144, beakGPU.returnColor(0));
	debugTileScreen = Image(160, 144, beakGPU.returnColor(0));

	Color pink = beakGPU.returnColor(0, 0);
	for (int i = 0; i < (256 * 256); i++)
	{
		bgPixels[i] = pink;
		windowPixels[i] = pink;
		spritePixels[i] = pink;
	}


	//Set Icon
	//char path1[MAX_PATH];
	//string path;
	//GetModuleFileNameA(NULL, path1, MAX_PATH);
	//path = string(path1);
	//path = path.substr(0, path.find_last_of('\\') + 1);
	//setIcon(32, 32, path + "Beak3.png");
}

GameWindow::~GameWindow()
{
}

void GameWindow::updateLCD(int clocks, int& lineClocksSinceLastUpdate, int& refreshClocksSinceLastUpdate, int& clocksSinceLastVBlank)
{
	//if (beakMemory.getLCDEnabled())
	//{
	byte ly = beakMemory.getLCDLY();
	byte originalLY = ly;

	if (gpuMode == 0)// || !beakGPU.getLCDOn()) //(Should be more accurate? Causes Bust A Move to be extremely slow when LCD is off)
	{
		//H-Blank
		//if greater than 204, inc ly, if ly 143 set mode to 1 and draw, else mode 2
		//40: SML 80: Tetris
		if ((clocks - lineClocksSinceLastUpdate) >= 204)//40)//80)//40)//80)//56)//102)//204)
		{
			//if (!poweringOn)
			{
				ly++;
				beakMemory.setLCDLY(ly);
			}

			if (ly >= 144)
			{
				beakGPU.setLCDMode(1);
				gpuMode = 1;
				clocksSinceLastVBlank = clocks;
				//beakGPU.setLCDStatus((beakGPU.getLCDStatus() & 0xC7) | 0x8);
				//Set LCD Interrupt if V-Blank Event is set
				if ((beakGPU.getLCDStatus() & 0x8) > 0)
				{
					beakMemory.writeMemory(0xFF0F, (byte)(beakMemory.readMemory(0xFF0F) | 0x02));
				}

				if ((clocks - refreshClocksSinceLastUpdate) >= 16384)//32768)//680)//12)
				{
					if (beakMemory.getLCDEnabled())
					{
						beakGPU.screenDrawing = true;
						drawScreenFromMaps(beakGPU.getScrollX(), beakGPU.getScrollY());
						beakGPU.screenUpdated = true;
						beakGPU.screenDrawing = false;
					}
					refreshClocksSinceLastUpdate = clocks;
				}
				//Set VBLANK Interrupt Flag
				if (beakGPU.getLCDOn())
				{
					beakMemory.writeMemory((short)0xFF0F, (byte)(beakMemory.readMemory(0xFF0F) | 0x1));
				}

				refreshClocksSinceLastUpdate = clocks;
				memset(spritePixels, 0, 256 * 256 * 4);
			}
			else
			{
				beakGPU.setLCDMode(2);
				gpuMode = 2;
				//beakGPU.setLCDStatus((beakGPU.getLCDStatus() & 0xC7) | 0x10);

				//Set LCD Interrupt if OAM Event is set
				if ((beakGPU.getLCDStatus() & 0x10) > 0)
				{
					beakMemory.writeMemory(0xFF0F, (byte)(beakMemory.readMemory(0xFF0F) | 0x02));
				}
			}


			lineClocksSinceLastUpdate = clocks;
		}

	}
	else if (gpuMode == 1)
	{
		//V-Blank
		//if greater than 456, inc ly, if ly > 153, set mode to 2, set ly to 0
		//50: SML 100: Tetris

		if ((clocks - lineClocksSinceLastUpdate) >= 456)//100)//50)//100)//114)//228)//456)
		{
			if (!poweringOn)
			{
				ly++;
				beakMemory.setLCDLY(ly);
			}
			/*
			if (ly >= 154)
			{

				//Set LCD Interrupt if OAM event is enabled
				if ((beakGPU.getLCDStatus() & 0x10) > 0)
				{
					beakMemory.writeMemory(0xFF0F, (byte)(beakMemory.readMemory(0xFF0F) | 0x02));
				}

				ly = 0;
				beakMemory.setLCDLY(ly);
			}
			*/

			lineClocksSinceLastUpdate = clocks;
		}

		if ((clocks - clocksSinceLastVBlank) >= 4560)
		{

			beakGPU.setLCDMode(2);
			gpuMode = 2;
			//beakGPU.setLCDStatus((beakGPU.getLCDStatus() & 0xC7) | 0x10);
			lineClocksSinceLastUpdate = clocks;//-1;
			poweringOn = false;

			//Set LCD Interrupt if OAM event is enabled
			if ((beakGPU.getLCDStatus() & 0x10) > 0)
			{
				beakMemory.writeMemory(0xFF0F, (byte)(beakMemory.readMemory(0xFF0F) | 0x02));
			}

			ly = 0;
			beakMemory.setLCDLY(ly);
		}

	}
	else if (gpuMode == 2)
	{
		//OAM Mode
		//if greater than 80, set mode to 3
		//15: SML 30: Tetris
		 /*
		if (lineClocksSinceLastUpdate == -1)
		{
			lineClocksSinceLastUpdate = clocks;
		}
		*/
		if ((clocks - lineClocksSinceLastUpdate) >= 80)//15)//30)//15)//20)//40)//80)
		{
			beakGPU.setLCDMode(3);
			gpuMode = 3;
			//beakGPU.setLCDStatus(beakGPU.getLCDStatus() & 0xC7);

			lineClocksSinceLastUpdate = clocks;

			if (beakMemory.getLCDEnabled())
			{
				if (beakGPU.getBackGroundEnabled())
				{
					beakGPU.drawLineFromBGMap(beakGPU.getScrollY() + ly);
				}
			}
		}

	}
	else
	{
		//VRAM Mode
		//if greater than 172, set mode to 0
		//30: SML 60: Tetris
		if ((clocks - lineClocksSinceLastUpdate) >= 172)//30)//60)//30)//43)//86)//172)
		{
			beakGPU.setLCDMode(0);
			gpuMode = 0;
			//beakGPU.setLCDStatus((beakGPU.getLCDStatus() & 0xC7) | 0x4);

			//Set LCD Interrupt if H-Blank Event is set
			if ((beakGPU.getLCDStatus() & 0x4) > 0)
			{
				beakMemory.writeMemory(0xFF0F, (byte)(beakMemory.readMemory(0xFF0F) | 0x02));
			}

			if (beakMemory.getLCDEnabled())
			{
				if (beakGPU.getSpriteEnabled())
				{
					beakGPU.drawLineFromSpriteMap(ly);
				}

				if (beakGPU.getWindowEnabled())
				{
					beakGPU.drawLineFromWindowMap(ly);
				}

			}
			lineClocksSinceLastUpdate = clocks;
		}

	}

	if (ly != originalLY)
	{

		//LCDLY Compare Interrupt
		if (beakGPU.getLCDOn() && (beakGPU.getLCDLY() == beakGPU.getLCDLYCompare()))
		{
			//Request interrupt of Interrupt for LCDLYCompare set
			if (beakGPU.getLCDLYCCheckEnabled())
			{
				beakMemory.writeMemory(0xFF0F, (byte)(beakMemory.readMemory(0xFF0F) | 0x02));
			}

			//Enable Coincidence Flag
			beakGPU.setLCDStatus(beakGPU.getLCDStatus() | 0x04);
		}
		else
		{
			//Disable Coincidence Flag
			beakGPU.setLCDStatus(beakGPU.getLCDStatus() & 0xFB);
		}
		
	}

	//}
	//else
	//{
		//window->clear(Color::White);
		//window->display();
	//}

}

void GameWindow::setBGPixel(int x, int y, Color color)
{
	bgPixels[x + (y * 256)] = color;
}

Color GameWindow::getBGPixel(int x, int y)
{
	return bgPixels[x + (y * 256)];
}

void GameWindow::setWindowPixel(int x, int y, Color color)
{
	windowPixels[x + (y * 256)] = color;
}

void GameWindow::setSpritePixel(int x, int y, Color color)
{
	spritePixels[x + (y * 256)] = color;
}

void GameWindow::setDebugPixel(int x, int y, Color color)
{
	//tileDebugPixels[x + (y * 256)] = color;
	debugTileScreen.setPixel(x, y, color);
}

void GameWindow::drawScreenFromMaps(int scrollX, int scrollY)
{

	if (beakGPU.getBackGroundEnabled())
	{

		byte x = 0;
		byte y = 0;

		
		for (int i = 0; i < 160; i++)
		{
			x = scrollX + i;

			for (int j = 0; j < 144; j++)
			{
				y = scrollY + j;

				screen.setPixel(i, j, bgPixels[x + (y * 256)]);
			}

		}
	}
	
	if (beakGPU.getWindowEnabled())
	{
		//Draw Window
		int winX = beakGPU.getWindowX() - 7;
		int winY = beakGPU.getWindowY();

		bool yTest = (winY <=  144) && ((winY + 256) >= 0);
		bool xTest = (winX < 160) && ((winX + 256) > 0);

		if (xTest && yTest)
		{
			int xShift = 0;
			int yShift = 0;
			int x = 0;
			int y = 0;

			if (winX < 0)
			{
				xShift = 0 - winX;
			}
			else
			{
				x = winX;
			}

			if (winY < 0)
			{
				yShift = 0 - winY;
			}
			else
			{
				y = winY;
			}

			for (int i = 0; (i + x + xShift) < 160; i++)
			{
				for (int j = 0; (j + y + yShift) < 144; j++)
				{
					screen.setPixel((x + xShift + i), (y + yShift + j), windowPixels[(xShift + i) + ((yShift + j) * 256)]);
				}

			}
			
		}

	}
	

	//Draw Sprites
	if (beakGPU.getSpriteEnabled())
	{
		int x = 0;
		int y = 0;
		while (y < 144)
		{
				if (spritePixels[((x) + ((y) * 256))].a != 0)
				{
					screen.setPixel(x, y, spritePixels[(x) + (y * 256)]);

				}

				if (x < 159)
				{
					x++;
				}
				else
				{
					x = 0;
					y++;
				}

		}
	}

	//drawImageToScreen(screen);

	for (int i = 0; i < (256 * 256); i++)
	{
		spritePixels[i].a = 0;
	}

	
}

void GameWindow::drawFullScreenMaps()
{

	Image fullScreen = Image(256, 256, Color(0, 0, 0));

	if (beakGPU.getBackGroundEnabled())
	{
		for (int x = 0; x < 256; x++)
		{

			for (int y = 0; y < 256; y++)
			{
				fullScreen.setPixel(x, y, bgPixels[x + (y * 256)]);
			}

		}
	}

	if (beakGPU.getWindowEnabled())
	{
		//Draw Window
		int winX = beakGPU.getWindowX() - 7;
		int winY = beakGPU.getWindowY();

		bool yTest = (winY <= 256) && ((winY + 256) >= 0);
		bool xTest = (winX < 256) && ((winX + 256) > 0);

		if (xTest && yTest)
		{
			int xShift = 0;
			int yShift = 0;
			int x = 0;
			int y = 0;

			if (winX < 0)
			{
				xShift = 0 - winX;
			}
			else
			{
				x = winX;
			}

			if (winY < 0)
			{
				yShift = 0 - winY;
			}
			else
			{
				y = winY;
			}

			for (int i = 0; (i + x + xShift) < 160; i++)
			{
				for (int j = 0; (j + y + yShift) < 144; j++)
				{
					//fullScreen.setPixel(beakGPU.getScrollX() + (x + xShift + i) , beakGPU.getScrollY() + (y + yShift + j), windowPixels[(xShift + i) + ((yShift + j) * 256)]);
					fullScreen.setPixel((x + xShift + i), (y + yShift + j), windowPixels[(xShift + i) + ((yShift + j) * 256)]);
				}

			}

		}

	}


	//Draw Sprites
	if (beakGPU.getSpriteEnabled())
	{
		int x = 0;
		int y = 0;
		while (y < 256)
		{
			if (spritePixels[((x)+((y) * 256))].a != 0)
			{
				//fullScreen.setPixel(beakGPU.getScrollX() + x, beakGPU.getScrollY() + y, spritePixels[(x)+(y * 256)]);
				fullScreen.setPixel(x, y, spritePixels[(x)+(y * 256)]);
			}

			if (x < 255)
			{
				x++;
			}
			else
			{
				x = 0;
				y++;
			}

		}
	}

	//drawImageToScreen(fullScreen);
}

/*
void GameWindow::drawImageToScreen(Image image)
{
	if (filterSetting > 0)
	{
		image = filterSelect(image, (byte)filterSetting);
	}

	beakWindow.texture.loadFromImage(image);

	Sprite sprite(texture);
	sprite.setScale(window.getView().getSize().x / sprite.getLocalBounds().width, window.getView().getSize().y / sprite.getLocalBounds().height);

	window.clear();
	window.draw(sprite);
	window.display();
}
*/

int GameWindow::getGPUMode()
{
	return gpuMode;
}
