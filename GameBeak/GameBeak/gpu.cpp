#include "gpu.h"
#include "Main.h"
#include <SFML\System.hpp>
#include <SFML\Graphics\Color.hpp>
#include <vector>

gpu::gpu()
{
}


gpu::~gpu()
{
}


byte gpu::getLCDStatus()
{
	return beakMemory.readMemory(0xFF41);
}

void gpu::setLCDStatus(byte newStatus)
{
	beakMemory.writeMemory(0xFF41, newStatus);
}

void gpu::setLCDMode(byte status)
{
	beakMemory.writeMemory(0xFF41, (byte)((getLCDStatus() & 0xFC) | status));
}

byte gpu::getLCDMode()
{
	//return (getLCDStatus() & 0x01) + ((getLCDStatus() & 0x02) >> 1);
	//return (getLCDStatus() & 0x01) | ((getLCDStatus() & 0x02));
	return (getLCDStatus() & 0x03);
}

byte gpu::getLCDLYCCheckEnabled()
{
	return (getLCDStatus() & 0x40) >> 6;
}

byte gpu::getLCDLYCompare()
{
	return beakMemory.readMemory(0xFF45);
}

byte gpu::getLCDLY()
{
	return beakMemory.readMemory(0xFF44);
}

byte gpu::getLCDControl()
{
	return beakMemory.readMemory(0xFF40);
}

bool gpu::getLCDOn()
{
	return ((getLCDControl() & 0x80) >> 7) > 0;
}

bool gpu::getWindowTileMapLocation()
{
	return ((getLCDControl() & 0x40) >> 6) > 0;
}

bool gpu::getWindowEnabled()
{
	return ((getLCDControl() & 0x20) >> 5) > 0;
}

bool gpu::getBackGroundWindowTileSetLocation()
{
	return ((getLCDControl() & 0x10) >> 4) > 0;
}

bool gpu::getBackGroundTileMapLocation()
{
	return ((getLCDControl() & 0x08) >> 3) > 0;
}

bool gpu::getSpriteSize()
{
	return ((getLCDControl() & 0x04) >> 2) > 0;
}

bool gpu::getSpriteEnabled()
{
	return ((getLCDControl() & 0x02) >> 1) > 0;
}

bool gpu::getBackGroundEnabled()
{
	return (getLCDControl() & 0x01);
}

//Draw All Tiles: Draws each tile directly from vram in the order they are in Vram. Prints out each tile that is loaded into memory
void gpu::drawAllTiles()
{
	int baseAddress;
	if (getBackGroundWindowTileSetLocation())
	{
		baseAddress = 0x8000;
	}
	else
	{
		baseAddress = 0x8800;
		//baseAddress = 0x9000;
	}
	//baseAddress = 0x8000; //temp

	vector<vector<Color>> tile;

	for (int i = 0; i < 640; i++)//<128; i++)//320; i++) //* 20; i++)  //i < 32 * 32; i++) 
	{
		tile.clear();

		int tileOffset = i * 16;

		int tileAddress = baseAddress + tileOffset;

		for (int j = 0; j < 16; j += 2)
		{
			byte rowHalf1 = beakMemory.readMemory(tileAddress + j);
			byte rowHalf2 = beakMemory.readMemory(tileAddress + j + 1);

			vector<Color> row;

			for (int k = 0; k < 8; k++)
			{
				int test = rowHalf1 & 0x01;
				int test2 = rowHalf2 & 0x01;
				int test3 = ((rowHalf1 & 0x01) << 1) | (rowHalf2 & 0x01);
				Color test4 = returnColor(((rowHalf1 & 0x01) << 1) | (rowHalf2 & 0x01));

				//row.push_back(returnColor(((rowHalf1 & 0x01) << 1) | (rowHalf2 & 0x01)));
				//rowHalf1 >>= 1;
				//rowHalf2 >>= 1;

				row.push_back(returnColor((((rowHalf1 & 0x80) >> 7)) | ((rowHalf2 & 0x80) >> 6)));
				rowHalf1 <<= 1;
				rowHalf2 <<= 1;
			}

			tile.push_back(row);
		}

		drawBGTile(i, tile);

	}
}
/*
void gpu::drawTiles()
{
	int scrollY = beakMemory.readMemory(0xFF42);
	int scrollX = beakMemory.readMemory(0xFF43);
	int windowY = beakMemory.readMemory(0xFF4A);
	int windowX = beakMemory.readMemory(0xFF4B);
	int mapAddress;
	int baseAddress;

	if (getBackGroundTileMapLocation())
	{
		mapAddress = 0x9C00;
	}
	else
	{
		mapAddress = 0x9800;
	}

	if (getBackGroundWindowTileSetLocation())
	{
		baseAddress = 0x8000;
	}
	else
	{
		baseAddress = 0x8800;
	}



	vector<vector<Color>> tile;

	//for (int i = 0; i < 32 * 32; i++)
	for (int i = 0; i < 32; i++)
	{
		//int finalLocation = (baseAddress == 0x8000) ? baseAddress + (16 * i) : baseAddress + (16 * (i + 0x80));

		int tileY = i / 32;
		int tileX = i - (32 * i);
		int tileIndex = tileY * (32 * tileX);

		int tileIDAddress = mapAddress + tileIndex;

		int tileID = beakMemory.readMemory(tileIDAddress);
		int tileOffset = tileID * 16;

		int tileAddress = baseAddress + tileOffset;

		for (int j = 0; j < 16; j += 2)
		{
			//byte rowHalf1 = beakMemory.readMemory(finalLocation + j);
			//byte rowHalf2 = beakMemory.readMemory(finalLocation + j + 1);
			byte rowHalf1 = beakMemory.readMemory(tileAddress + j);
			byte rowHalf2 = beakMemory.readMemory(tileAddress + j + 1);

			vector<Color> row;

			for (int k = 0; k < 8; k++)
			{
				row.push_back(returnColor((rowHalf1 & 0x01) + (rowHalf2 & 0x01)));
				rowHalf1 >>= 1;
				rowHalf2 >>= 1;
			}

			tile.push_back(row);
		}

		drawTile(i, tile);
	}
}
*/

//Draw Tiles: Reads tiles from tile map to their proper location on screen on a TILE-TO-TILE BASIS
void gpu::drawTiles()
{
	//int scrollY = beakMemory.readMemory(0xFF42);
	//int scrollX = beakMemory.readMemory(0xFF43);
	//int windowY = beakMemory.readMemory(0xFF4A);
	//int windowX = beakMemory.readMemory(0xFF4B);
	int mapAddress;
	int baseAddress;

	if (getBackGroundTileMapLocation())
	{
		mapAddress = 0x9C00;
	}
	else
	{
		mapAddress = 0x9800;
	}

	if (getBackGroundWindowTileSetLocation())
	{
		baseAddress = 0x8000;
	}
	else
	{
		baseAddress = 0x8800;
	}



	vector<vector<Color>> tile;

	//for (int i = 0; i < 32 * 32; i++)
	for (int i = 0; i < 32 * 18; i++)
	//for (int i = 0; i < 64; i++)
	{
		//int finalLocation = (baseAddress == 0x8000) ? baseAddress + (16 * i) : baseAddress + (16 * (i + 0x80));

		int tileY = i / 32;
		//int tileX = i - (32 * i);
		int tileX = i - (tileY * 32);
		//int tileIndex = tileY * (32 * tileX);
		int tileIndex = tileX + (32 * tileY);

		int tileIDAddress = mapAddress + tileIndex;

		int tileID = beakMemory.readMemory(tileIDAddress);
		int tileOffset = tileID * 16;

		int tileAddress = baseAddress + tileOffset;

		for (int j = 0; j < 16; j += 2)
		{
			//byte rowHalf1 = beakMemory.readMemory(finalLocation + j);
			//byte rowHalf2 = beakMemory.readMemory(finalLocation + j + 1);
			byte rowHalf1 = beakMemory.readMemory(tileAddress + j);
			byte rowHalf2 = beakMemory.readMemory(tileAddress + j + 1);

			vector<Color> row;

			for (int k = 0; k < 8; k++)
			{
				row.push_back(returnColor((rowHalf1 & 0x01) + (rowHalf2 & 0x01)));
				rowHalf1 >>= 1;
				rowHalf2 >>= 1;
			}

			tile.push_back(row);
		}

		drawBGTile(i, tile);
	}
}

//Draw Tile From Map: Draws a specific single tile by reading the tilemap and drawing it to it's proper location
void gpu::drawTileFromBGMap(int x, int y)
{
	int mapAddress;
	int baseAddress;

	if (getBackGroundTileMapLocation())
	{
		mapAddress = 0x9C00;
	}
	else
	{
		mapAddress = 0x9800;
	}

	if (getBackGroundWindowTileSetLocation())
	{
		baseAddress = 0x8000;
	}
	else
	{
		baseAddress = 0x8800;
		//baseAddress = 0x9000;
	}

	vector<vector<Color>> tile;


	int tileIndex = x + (32 * y);

	int tileIDAddress = mapAddress + tileIndex;

	int tileID = beakMemory.readMemory(tileIDAddress);
	int tileOffset = tileID * 16;

	int tileAddress = baseAddress + tileOffset;

	for (int j = 0; j < 16; j += 2)
	{
		byte rowHalf1 = beakMemory.readMemory(tileAddress + j);
		byte rowHalf2 = beakMemory.readMemory(tileAddress + j + 1);

		vector<Color> row;

		for (int k = 0; k < 8; k++)
		{
			row.push_back(returnColor((rowHalf1 & 0x01) + (rowHalf2 & 0x01)));
			rowHalf1 >>= 1;
			rowHalf2 >>= 1;
		}

		tile.push_back(row);
	}

	drawBGTile(tileIndex, tile);

}

//DrawLineFromMap: Draws a single specific line of the background map
void gpu::drawLineFromBGMap(int lineY)
{

	int mapAddress;
	int baseAddress;

	if (getBackGroundTileMapLocation())
	{
		mapAddress = 0x9C00;
	}
	else
	{
		mapAddress = 0x9800;
	}

	if (getBackGroundWindowTileSetLocation())
	{
		baseAddress = 0x8000;
	}
	else
	{
		baseAddress = 0x8800;
	}

	int lineToDraw = lineY % 8;

	int tileY = 0;
	int tileX = 0;
	int tileIndex = 0;
	int tileIDAddress = 0;
	int tileID = 0;
	int tileOffset = 0;
	int tileAddress = 0;
	byte rowHalf1 = 0;
	byte rowHalf2 = 0;

	for (int i = 0; i < 32; i++)
	{
		tileY = (lineY) / 8;
		tileX = (i);
		tileIndex = tileX + (32 * tileY);
		tileIDAddress = mapAddress + tileIndex;

		tileID = beakMemory.readMemory(tileIDAddress);

		if (baseAddress == 0x8800)
		{
			if (tileID > 0x7F)
			{
				tileID -= 0x80;
			}
			else
			{
				tileID += 0x80;
			}
		}

		tileOffset = tileID * 16;
		tileAddress = baseAddress + tileOffset;


		rowHalf1 = beakMemory.readMemory(tileAddress + (lineToDraw * 2));
		rowHalf2 = beakMemory.readMemory(tileAddress + (lineToDraw * 2) + 1);

		for (int j = 0; j < 8; j++)
		{
			beakWindow.setBGPixel((i * 8) + j, lineY, returnColor(((rowHalf1 & 0x80) >> 7) | ((rowHalf2 & 0x80) >> 6), 0));
			rowHalf1 <<= 1;
			rowHalf2 <<= 1;

		}
		
	}

}

void gpu::drawLineFromWindowMap(int lineY)
{

	int mapAddress;
	int baseAddress;

	if (getWindowTileMapLocation())
	{
		mapAddress = 0x9C00;
	}
	else
	{
		mapAddress = 0x9800;
	}

	if (getBackGroundWindowTileSetLocation())
	{
		baseAddress = 0x8000;
	}
	else
	{
		baseAddress = 0x8800;
		//baseAddress = 0x9000;
	}


	//baseAddress = 0x8000; //temp! REMOVE
	//mapAddress = 0x9800; //temp! REMOVE

	//int winX = beakGPU.getWindowX();
	//int winY = beakGPU.getWindowY();
	//int scrollX = beakGPU.getScrollX();
	//int scrollY = beakGPU.getScrollY();

	//bool yTest = (winY <= lineY) && ((winY + 256) >= lineY);
	//bool xTest = (winX < (scrollX + 256)) && ((winX + 256) > scrollX);

	//if (xTest && yTest)
	//{

	int lineToDraw = lineY % 8;

	int tileY = 0;
	int tileX = 0;
	int tileIndex = 0;
	int tileIDAddress = 0;
	int tileID = 0;
	int tileOffset = 0;
	int tileAddress = 0;
	byte rowHalf1 = 0;
	byte rowHalf2 = 0;

	for (int i = 0; i < 32; i++)
	{
		//if ((scrollX + i) >= winX)
		//{
		tileY = (lineY) / 8;
		tileX = (i);
		tileIndex = tileX + (32 * tileY);
		tileIDAddress = mapAddress + tileIndex;

		tileID = beakMemory.readMemory(tileIDAddress);

		if (baseAddress == 0x8800)
		{
			//tileID += 128;
			if (tileID > 0x7F)
			{
				tileID -= 0x80;
			}
			else
			{
				tileID += 0x80;
			}
		}

		tileOffset = tileID * 16;
		tileAddress = baseAddress + tileOffset;

		rowHalf1 = beakMemory.readMemory(tileAddress + (lineToDraw * 2));
		rowHalf2 = beakMemory.readMemory(tileAddress + (lineToDraw * 2) + 1);

		for (int j = 0; j < 8; j++)
		{
			beakWindow.setWindowPixel((i * 8) + j, lineY, returnColor(((rowHalf1 & 0x80) >> 7) | ((rowHalf2 & 0x80) >> 6), 0));
			rowHalf1 &= 0x7F;
			rowHalf1 <<= 1;
			rowHalf2 &= 0x7F;
			rowHalf2 <<= 1;

		}
		//}
	}
	//}

}

#include "Binary.h"

void gpu::drawLineFromSpriteMap(int lineY)
{
	//Todo: Reimplement this function. It currently does NOT support priority OR Y flip. Will need to add logic to go from bottom - up or right - left if these flips are there. Can't do after.

	int mapAddress = 0xFE00;
	int baseAddress = 0x8000;

	//False: 8x8 | True: 8x16
	bool spriteSize = getSpriteSize();

	byte y = 0;
	byte x = 0;
	int tileY = 0;
	int tileX = 0;
	int tileIndex = 0;
	int tileIDAddress = 0;
	int tileID = 0;
	int tileOffset = 0;
	int tileAddress = 0;
	byte rowHalf1 = 0;
	byte rowHalf2 = 0;
	int lineToDraw = 0;

	byte tileNumber = 0;
	byte tileFlags = 0;
	bool priority = false;
	bool yFlip = false;
	bool xFlip = false;
	bool palette = false;

	for (int i = 0; i < 40; i++)
	{
		y = beakMemory.readMemory(mapAddress + (i * 4));

		if (y > 8) //Not the problem, but potentially useless
		{
			y -= 16;
			x = beakMemory.readMemory(mapAddress + (i * 4) + 1) - 8;

			bool isSpriteOnLine = (y <= lineY) && ((y + ((spriteSize == 0) ? 8 : 16)) > lineY);
			//(y <= lineY)  if the start of the sprite is at lineY or before it
			//(y + (spriteSize == 0) ? 8 : 16)) > lineY) if the end of the sprite is past lineY (By way of commenting, this isn't the problem)


			if (isSpriteOnLine)
			{
				lineToDraw = lineY - y;

				tileNumber = beakMemory.readMemory(mapAddress + (i * 4) + 2);
				tileFlags = beakMemory.readMemory(mapAddress + (i * 4) + 3);
				priority = ((tileFlags & 0x80) >> 7) > 0; //If 1, displays in front of window. Otherwise is below window and above BG
				yFlip = ((tileFlags & 0x40) >> 6) > 0; //Vertically flipped if 1, else 0.
				xFlip = ((tileFlags & 0x20) >> 5) > 0; //Horizontally flipped if 1, else 0;
				palette = ((tileFlags & 0x10) >> 4) > 0; //Palette is OBJ0PAL if 0, else OBJ1PAL

				tileOffset = tileNumber * 16;
				tileAddress = baseAddress + tileOffset;

				if (yFlip)
				{
					lineToDraw = 8 - lineToDraw;
				}

				rowHalf1 = beakMemory.readMemory(tileAddress + (lineToDraw * 2));
				rowHalf2 = beakMemory.readMemory(tileAddress + (lineToDraw * 2) + 1);

				if (xFlip)
				{
					rowHalf1 = reverseBits(rowHalf1);
					rowHalf2 = reverseBits(rowHalf2);
				}

				for (int j = 0; j < 8; j++)
				{
					byte colorNumber = ((rowHalf1 & 0x80) >> 7) | ((rowHalf2 & 0x80) >> 6);
					Color color;

					if (colorNumber > 0)
					{
						color = returnColor(colorNumber, palette + 1);
						beakWindow.setSpritePixel(x + j, lineY, color);
					}

					rowHalf1 <<= 1;
					rowHalf2 <<= 1;
				}

			}
		}
	}
}


/*
void gpu::drawLineFromSpriteMap(int lineY)
{
	//Todo: Reimplement this function. It currently does NOT support priority OR Y flip. Will need to add logic to go from bottom - up or right - left if these flips are there. Can't do after.

	int mapAddress = 0xFE00;
	int baseAddress = 0x8000;

	//False: 8x8 | True: 8x16
	bool spriteSize = getSpriteSize();

	for (int i = 0; i < 40; i++)
	{
		byte y = beakMemory.readMemory(mapAddress + (i * 4));
		byte x = beakMemory.readMemory(mapAddress + (i * 4) + 1);
		y -= 16;//17;
		x -= 9;

		bool isSpriteOnLine = (y > 8) && (y <= lineY) && ((y + ((spriteSize == 0) ? 8 : 16)) > lineY); //Has to be at least 9 to appear on screen

		if (isSpriteOnLine)
		{

			//TODO: Implement Y-Flip

			int lineToDraw = lineY - y;

			byte tileNumber = beakMemory.readMemory(mapAddress + (i * 4) + 2);
			byte tileFlags = beakMemory.readMemory(mapAddress + (i * 4) + 3);
			bool priority = ((tileFlags & 0x80) >> 7) > 0; //If 1, displays in front of window. Otherwise is below window and above BG
			bool yFlip = ((tileFlags & 0x40) >> 6) > 0; //Vertically flipped if 1, else 0.
			bool xFlip = ((tileFlags & 0x20) >> 5) > 0; //Horizontally flipped if 1, else 0;
			bool palette = ((tileFlags & 0x10) >> 4) > 0; //Palette is OBJ0PAL if 0, else OBJ1PAL

			int tileOffset = tileNumber * 16;
			int tileAddress = baseAddress + tileOffset;
		
			byte rowHalf1 = beakMemory.readMemory(tileAddress + (lineToDraw * 2));
			byte rowHalf2 = beakMemory.readMemory(tileAddress + (lineToDraw * 2) + 1);

			vector<Color> line;

			// // // // //
			for (int j = 0; j < 8; j++)
			{
				//byte colorNumber = (rowHalf1 & 0x01) + (rowHalf2 & 0x01);
				byte colorNumber = ((rowHalf1 & 0x80)>> 7) + ((rowHalf2 & 0x80) >> 7);
				Color color;

				if (colorNumber == 0)
				{
					color = Color(0, 0, 0, 0);
				}
				else
				{
					color = returnColor(colorNumber, palette + 1);
				}

				line.push_back(color);

				//rowHalf1 >>= 1;
				//rowHalf2 >>= 1;
				rowHalf1 <<= 1;
				rowHalf2 <<= 1;
			}

			if (xFlip) //Seems counter-intuitive, but I am already reading it backwards
			{
				reverse(line.begin(), line.end());
			}

			for (int j = 0; j < (int)line.size(); j++)
			{
				if (line[j].a != 0) //Forces transparency for color 0
				{
					beakWindow.setSpritePixel(x + j, lineY, line[j]);
				}
			}

			
			//if (yFlip)
			//{
				//reverse(tile.begin(), tile.end());
			//}
			//
			//drawSprite(x, y, tile);
		}
	}
}
*/

//DrawTile: Draws tile data as given to location of tile number given
void gpu::drawBGTile(int tileNumber, vector<vector<Color>> tile)
{
	int y = tileNumber / 32;
	int x = tileNumber - (32 * y);

	//int y = tileNumber / 20;
	//int x = tileNumber - (20 * y);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//beakWindow.setPixel(x + i, y + i, tile[x][y]);
			//beakWindow.setPixel((x * 8) + i, (y * 8) + j, tile.at(y + i).at(j));//tile[y + i][x + j]);
			beakWindow.setBGPixel((x * 8) + j, (y * 8) + i, tile[0][j]);
			//setFullMapPixel((x * 8) + j, (y * 8) + i, tile[0][j]);
			//beakWindow.drawScreen(); //temp
		}
		//tile.pop_back();
		tile.erase(tile.begin());
	}

	//beakWindow.drawScreen(); //temp
}

//DrawSpriteFromMap: Reads sprite map to draw each sprite to it's proper location
void gpu::drawSpriteFromMap(int spriteNumber)
{
	int mapAddress = 0xFE00;
	int baseAddress = 0x8000;

	//False: 8x8 | True: 8x16
	bool spriteSize = getSpriteSize();

	vector<vector<Color>> tile;

	byte y = beakMemory.readMemory(mapAddress + (spriteNumber * 4));
	byte x = beakMemory.readMemory(mapAddress + (spriteNumber * 4) + 1);
	byte tileNumber = beakMemory.readMemory(mapAddress + (spriteNumber * 4) + 2);
	byte tileFlags = beakMemory.readMemory(mapAddress + (spriteNumber * 4) + 3);

	bool priority = ((tileFlags & 0x80) >> 7) > 0; //If 1, displays in front of window. Otherwise is below window and above BG
	bool yFlip = ((tileFlags & 0x40) >> 6) > 0; //Vertically flipped if 1, else 0.
	bool xFlip = ((tileFlags & 0x20) >> 5) > 0; //Horizontally flipped if 1, else 0;
	bool palette = ((tileFlags & 0x10) >> 4) > 0; //Palette is OBJ0PAL if 0, else OBJ1PAL

	int tileOffset = tileNumber * 16;
	int tileAddress = baseAddress + tileOffset;

	for (int j = 0; j < 16; j += 2)
	{
		byte rowHalf1 = beakMemory.readMemory(tileAddress + j);
		byte rowHalf2 = beakMemory.readMemory(tileAddress + j + 1);

		vector<Color> row;

		for (int k = 0; k < 8; k++)
		{
			byte colorNumber = (rowHalf1 & 0x01) + (rowHalf2 & 0x01);

			if (colorNumber == 0)
			{
				row.push_back(Color(0,0,0,0));
			}
			else
			{
				row.push_back(returnColor(colorNumber));
			}

			rowHalf1 >>= 1;
			rowHalf2 >>= 1;
		}
		//Experimental, I have already fixed the sprites being vertically flipped. It seems they are also X flipped, so lets just reverse the row:
		reverse(row.begin(), row.end());
		tile.push_back(row);
	}

	if (xFlip)
	{
		for (int i = 0; i < (int)tile.size(); i++)
		{
			reverse(tile[i].begin(), tile[i].end());
		}
	}

	if (yFlip)
	{
		reverse(tile.begin(), tile.end());
	}

	drawSprite(x, y, tile);

}

//DrawSprite: Draws sprite data as given to location to an exact x/y coordinate
void gpu::drawSprite(int x, int y, vector<vector<Color>> tile)
{

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (tile[0][j].a != 0)
			{
				beakWindow.setBGPixel((x) + j, (y) + i, tile[0][j]);
				//beakWindow.setPixel((x * 8) + j, (y * 8) + i, tile[0][j]);
			}

		}
		tile.erase(tile.begin());
	}
}

byte gpu::getScrollX()
{
	return beakMemory.readMemory(0xFF43);
}

byte gpu::getScrollY()
{
	return beakMemory.readMemory(0xFF42);
}

byte gpu::getWindowX()
{
	return beakMemory.readMemory(0xFF4B);
}

byte gpu::getWindowY()
{
	return beakMemory.readMemory(0xFF4A);
}

Color gpu::returnColor(int colorNumber)
{
	if (pinkMode)
	{
		switch (colorNumber)
		{
			case 0:
			{
				return Color(255, 241, 254, 255); //Pink WHITE
				break;
			}
			case 1:
			{
				return Color(255, 214, 245, 255); //Light Pink
				break;
			}
			case 2:
			{
				return Color(255, 131, 217, 255); //Dark Pink
				break;
			}
			case 3:
			{
				return Color(72, 24, 59, 255); //Pink Black
				break;
			}
		}

		return Color(255, 241, 254, 255);
	}
	else
	{
		switch (colorNumber)
		{
			case 0:
			{
				//SDL_Color color = { 255, 50, 255, 0 };

				//return Color(255, 50, 255,0);
				//return Color(0, 0, 0, 255);
				return Color(255, 255, 255, 255); //WHITE
				//return Color(255, 0, 0, 255); //RED
				break;
			}
			case 1:
			{
				//SDL_Color color = { 255, 50, 255, 255/30 };
				//return Color(255, 50, 255, 255);
				return Color(105, 105, 105, 255); //GREY
				//return Color(0, 0, 0, 255);
				//return Color(0, 255, 0, 255); //GREEN
				break;
			}
			case 2:
			{
				//SDL_Color color = { 255, 50, 255, 255/60 };
				//return Color(255, 50, 255, 255);
				return Color(185, 185, 185, 255); //BLACK
				//return Color(0, 0, 255, 255); //BLUE
				break;
			}
			case 3:
			{
				//SDL_Color color = { 255, 50, 255, 255 };
				//return Color(255, 50, 255, 255); // MAGENTA
				return Color(0, 0, 0, 255); //GREY
				//return Color(255, 255, 0, 255);
				break;
			}
		}
		return Color(255, 255, 255, 255); //WHITE
	}
}

Color gpu::returnColor(int colorNumber, int palette)
{
	//Palette: 0 = BGP
	//Palette: 1 = 0BP0
	//Palette: 2 = 0BP1

	//Palette decides between BGP (0xFF47), 0BP0 (0xFF48), and 0BP1 (0xFF49)
	//Color number decides which color slot is selected from the palette data.
	//The value returned from the palette data is then used to index from the emulator's palette array.

	//byte paletteData = beakMemory.readMemory(0xFF47 + palette);
	//colorNumber = (paletteData & (3 << (colorNumber * 2))) >> (colorNumber * 2);//(colorNumber + 1);
	//return gameBeakPalette[colorNumber + (pinkMode << 2)];

	return gameBeakPalette[((beakMemory.readMemory(0xFF47 + palette) & (3 << (colorNumber * 2))) >> (colorNumber * 2)) + (pinkMode << 2)];


	//The palette variable is being used to select the memory location of the palette
	//The palette data that is retrieved is made up of 8 bits. 4 colors represented by 2 bits each.
	//The 2 bit groups can represent numbers 0-3 and represent how light or dark the color we want is supposed to be.
	//Once we retrieve the correct grouping it will be used to index the exact color to be used from the emulator's palette array.
	//To retrieve the appropriate grouping we have to mask the 2 bits we want. The number 3 will
	//retrieve the first 2 bits, and we can shift the number three to select the next three groupings if needed.
	//We use the color number to decide how much 3 needs to be shifted (if at all) to get the set of bits we want.
	//We then use it again to decide how much they need to be shifted right (if at all) to reduce the number to 0-3
	//Finally, we have the index we will use to index the palette, and we can add the value of pinkMode * 4 (or << 2) (will result in either 0 or 4)
	//To index the grey or pink set of colors depending on the mode.


	//Below is identical functionality, but simply much slower.
	//return gameBeakPalette[ returnHalfNibble( returnPalette(palette), colorNumber) ];
}

byte gpu::returnPalette(byte palette)
{
	//Palette: 0 = BGP
	//Palette: 1 = 0BP0
	//Palette: 2 = 0BP1
	return beakMemory.readMemory(0xFF47 + palette);
}