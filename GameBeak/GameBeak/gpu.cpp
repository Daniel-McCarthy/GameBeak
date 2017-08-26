#include "gpu.h"
#include "Main.h"
#include <vector>

gpu::gpu()
{
}


gpu::~gpu()
{
}


unsigned char gpu::getLCDStatus()
{
	return beakMemory.readMemory(0xFF41);
}

void gpu::setLCDStatus(unsigned char newStatus)
{
	beakMemory.directMemoryWrite(0xFF41, newStatus);
}

void gpu::setLCDMode(unsigned char status)
{
	beakMemory.directMemoryWrite(0xFF41, (unsigned char)((getLCDStatus() & 0xFC) | status));
}

byte gpu::getLCDMode()
{
	return (getLCDStatus() & 0x03);
}

unsigned char gpu::getLCDLYCCheckEnabled()
{
	return (getLCDStatus() & 0x40) >> 6;
}

unsigned char gpu::getLCDLYCompare()
{
	return beakMemory.readMemory(0xFF45);
}

unsigned char gpu::getLCDLY()
{
	return beakMemory.readMemory(0xFF44);
}

unsigned char gpu::getLCDControl()
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
	int baseAddress = 0x8000;

	vector<vector<Color>> tile;

	for (int i = 0; i < 360; i++)
	{
		tile.clear();

		int tileOffset = i * 16;

		int tileAddress = baseAddress + tileOffset;

		for (int j = 0; j < 16; j += 2)
		{
			unsigned char rowHalf1 = beakMemory.readMemory(tileAddress + j);
			unsigned char rowHalf2 = beakMemory.readMemory(tileAddress + j + 1);

			vector<Color> row;

			for (int k = 0; k < 8; k++)
			{
				int test = rowHalf1 & 0x01;
				int test2 = rowHalf2 & 0x01;
				int test3 = ((rowHalf1 & 0x01) << 1) | (rowHalf2 & 0x01);
				Color test4 = returnColor(((rowHalf1 & 0x01) << 1) | (rowHalf2 & 0x01));

				row.push_back(returnColor((((rowHalf1 & 0x80) >> 7)) | ((rowHalf2 & 0x80) >> 6)));
				rowHalf1 <<= 1;
				rowHalf2 <<= 1;
			}

			tile.push_back(row);
		}

		drawDebugTile(i, tile);

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
			//unsigned char rowHalf1 = beakMemory.readMemory(finalLocation + j);
			//unsigned char rowHalf2 = beakMemory.readMemory(finalLocation + j + 1);
			unsigned char rowHalf1 = beakMemory.readMemory(tileAddress + j);
			unsigned char rowHalf2 = beakMemory.readMemory(tileAddress + j + 1);

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
	unsigned char rowHalf1 = 0;
	unsigned char rowHalf2 = 0;

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
	}

	int lineToDraw = lineY % 8;

	int tileY = 0;
	int tileX = 0;
	int tileIndex = 0;
	int tileIDAddress = 0;
	int tileID = 0;
	int tileOffset = 0;
	int tileAddress = 0;
	unsigned char rowHalf1 = 0;
	unsigned char rowHalf2 = 0;

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
			beakWindow.setWindowPixel((i * 8) + j, lineY, returnColor(((rowHalf1 & 0x80) >> 7) | ((rowHalf2 & 0x80) >> 6), 0));
			rowHalf1 &= 0x7F;
			rowHalf1 <<= 1;
			rowHalf2 &= 0x7F;
			rowHalf2 <<= 1;

		}

	}


}

#include "Binary.h"

void gpu::drawLineFromSpriteMap(int lineY)
{
	//Todo: Support priority.

	int mapAddress = 0xFE00;
	int baseAddress = 0x8000;

	//False: 8x8 | True: 8x16
	bool spriteSize = getSpriteSize();

	int y = 0;
	unsigned char x = 0;
	int tileY = 0;
	int tileX = 0;
	int tileIndex = 0;
	int tileIDAddress = 0;
	int tileID = 0;
	int tileOffset = 0;
	int tileAddress = 0;
	unsigned char rowHalf1 = 0;
	unsigned char rowHalf2 = 0;
	int lineToDraw = 0;

	unsigned char tileNumber = 0;
	unsigned char tileFlags = 0;
	bool priority = false;
	bool yFlip = false;
	bool xFlip = false;
	bool palette = false;

	unsigned char scrollX = getScrollX();
	unsigned char scrollY = getScrollY();

	Color bgColor = returnColor(0, 0);

	for (int i = 0; i < 40; i++)
	{
		y = beakMemory.readMemory(mapAddress + (i * 4)) - 16;

		if (y > -8)
		{

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
					unsigned char colorNumber = ((rowHalf1 & 0x80) >> 7) | ((rowHalf2 & 0x80) >> 6);

					if (colorNumber > 0)
					{
						if (!priority || (priority && (beakWindow.getBGPixel(scrollX + x + j, lineY + scrollY) == bgColor)))
						{
							beakWindow.setSpritePixel(x + j, lineY, returnColor(colorNumber, palette + 1)); //Plus 1 because 0 is BG palette, so value must be 1 or 2 to access OBJ1 or OBj2.
						}
					}

					rowHalf1 <<= 1;
					rowHalf2 <<= 1;
				}

			}
		}
	}
}

//DrawTile: Draws tile data as given to location of tile number given
void gpu::drawDebugTile(int tileNumber, vector<vector<Color>> tile)
{
	//int y = tileNumber / 32;
	//int x = tileNumber - (32 * y);

	int y = tileNumber / 20;
	int x = tileNumber - (20 * y);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			beakWindow.setDebugPixel((x * 8) + j, (y * 8) + i, tile[0][j]);
		}

		tile.erase(tile.begin());
	}

}

unsigned char gpu::getScrollX()
{
	return beakMemory.readMemory(0xFF43);
}

unsigned char gpu::getScrollY()
{
	return beakMemory.readMemory(0xFF42);
}

unsigned char gpu::getWindowX()
{
	return beakMemory.readMemory(0xFF4B);
}

unsigned char gpu::getWindowY()
{
	return beakMemory.readMemory(0xFF4A);
}

Color gpu::returnColor(int colorNumber)
{
	return gameBeakPalette[colorNumber + (paletteSetting * 12)];
}

Color gpu::returnColor(int colorNumber, int palette)
{
	//Palette: 0 = BGP
	//Palette: 1 = 0BP0
	//Palette: 2 = 0BP1

	//Palette decides between BGP (0xFF47), 0BP0 (0xFF48), and 0BP1 (0xFF49)
	//Color number decides which color slot is selected from the palette data.
	//The value returned from the palette data is then used to index from the emulator's palette array.

	//unsigned char paletteData = beakMemory.readMemory(0xFF47 + palette);
	//colorNumber = (paletteData & (3 << (colorNumber * 2))) >> (colorNumber * 2);//(colorNumber + 1);
	//return gameBeakPalette[colorNumber + paletteSetting << 2)];

	return gameBeakPalette[((beakMemory.readMemory(0xFF47 + palette) & (3 << (colorNumber * 2))) >> (colorNumber * 2)) + (paletteSetting * 12) + (palette << 2)];


	//The palette variable is being used to select the memory location of the palette
	//The palette data that is retrieved is made up of 8 bits. 4 colors represented by 2 bits each.
	//The 2 bit groups can represent numbers 0-3 and represent how light or dark the color we want is supposed to be.
	//Once we retrieve the correct grouping it will be used to index the exact color to be used from the emulator's palette array.
	//To retrieve the appropriate grouping we have to mask the 2 bits we want. The number 3 will
	//retrieve the first 2 bits, and we can shift the number three to select the next three groupings if needed.
	//We use the color number to decide how much 3 needs to be shifted (if at all) to get the set of bits we want.
	//We then use it again to decide how much they need to be shifted right (if at all) to reduce the number to 0-3
	//Finally, we have the index we will use to index the palette, and we can add the value of paletteSettng * 4 (or << 2) (multiples of 4 to select correct group)
	//To index the grey or pink set of colors depending on the mode.


	//Below is identical functionality, but simply much slower.
	//return gameBeakPalette[ returnHalfNibble( returnPalette(palette), colorNumber) ];
}

unsigned char gpu::returnPalette(unsigned char palette)
{
	//Palette: 0 = BGP
	//Palette: 1 = 0BP0
	//Palette: 2 = 0BP1
	return beakMemory.readMemory(0xFF47 + palette);
}

void gpu::loadPalettesFromXML(ifstream file)
{
	string line;
	list<unsigned char> colorValues;

	while (getline(file, line))
	{
		bool test1 = (line.find("<bgp>") != string::npos) && (line.find("</bgp>") != string::npos);
		bool test2 = (line.find("<0bp0>") != string::npos) && (line.find("</0bp0>") != string::npos);
		bool test3 = (line.find("<0bp1>") != string::npos) && (line.find("</0bp1>") != string::npos);

		if (test1 || test2 || test3)
		{
			int first = line.find_first_of('>') + 1;
			int last = line.find_last_of('<');

			line = line.substr(first, last - first);

			for (int i = 0; i < 4; i++)
			{
				unsigned int r = stoi(line.substr(0, 2), 0, 16);
				unsigned int g = stoi(line.substr(2, 2), 0, 16);
				unsigned int b = stoi(line.substr(4, 2), 0, 16);

				colorValues.push_back(r);
				colorValues.push_back(g);
				colorValues.push_back(b);

				if (line.length() > 8)
				{
					line = line.substr(9, line.length() - 9);
				}
			}

		}
	}
	if ((colorValues.size() / 36) > 0)
	{
		int paletteOffset = 0;
		int colorOffset = 0;

		while (colorValues.size() >= (4*3))
		{
			for (int i = 0; i < 4; i++)
			{
				int r = colorValues.front();
				colorValues.pop_front();
				int g = colorValues.front();
				colorValues.pop_front();
				int b = colorValues.front();
				colorValues.pop_front();

				Color color = Color(r, g, b, 255);


				beakGPU.gameBeakPalette[(paletteOffset * 4) + colorOffset] = color;

				if (colorOffset >= 3)
				{
					colorOffset = 0;
				}
				else
				{
					colorOffset++;
				}
			}

			paletteOffset++;
		}
	}

	file.close();
}

ifstream gpu::openCreatePalettesXML()
{
	//open XML palette file
	char path1[MAX_PATH];
	string path;
	GetModuleFileNameA(NULL, path1, MAX_PATH);
	path = string(path1);
	path = path.substr(0, path.find_last_of('\\') + 1);

	ifstream colorFile(path + "palettes.xml");
	if (colorFile.fail())
	{
		ofstream file(path + "palettes.xml");
		if (file.is_open())
		{
			file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
			file << "<colorschemes>\n" << endl;

			file << "\t<scheme>" << endl;
			file << "\t\t<name>BlackWhite</name>" << endl;
			file << "\t\t<bgp>FFFFFFFF|B9B9B9FF|696969FF|000000FF</bgp>" << endl;
			file << "\t\t<0bp0>FFFFFFFF|B9B9B9FF|696969FF|000000FF</0bp0>" << endl;
			file << "\t\t<0bp1>FFFFFFFF|B9B9B9FF|696969FF|000000FF</0bp1>" << endl;
			file << "\t</scheme>\n" << endl;

			file << "\t<scheme>" << endl;
			file << "\t\t<name>Green</name>" << endl;
			file << "\t\t<bgp>E0FFEBFF|88D058FF|34B73CFF|084703FF</bgp>" << endl;
			file << "\t\t<0bp0>E0FFEBFF|88D058FF|34B73CFF|084703FF</0bp0>" << endl;
			file << "\t\t<0bp1>E0FFEBFF|88D058FF|34B73CFF|084703FF</0bp1>" << endl;
			file << "\t</scheme>\n" << endl;

			file << "\t<scheme>" << endl;
			file << "\t\t<name>Pink</name>" << endl;
			file << "\t\t<bgp>FFF1FEFF|FFD6F5FF|FF83D9FF|48183BFF</bgp>" << endl;
			file << "\t\t<0bp0>FFF1FEFF|FFD6F5FF|FF83D9FF|48183BFF</0bp0>" << endl;
			file << "\t\t<0bp1>FFF1FEFF|FFD6F5FF|FF83D9FF|48183BFF</0bp1>" << endl;
			file << "\t</scheme>\n" << endl;

			file << "\t<scheme>" << endl;
			file << "\t\t<name>PinkAlt</name>" << endl;
			file << "\t\t<bgp>FFF0F5FF|FFBADEFF|FF74D9FF|520528FF</bgp>" << endl;
			file << "\t\t<0bp0>FFF0F5FF|FFBADEFF|FF74D9FF|520528FF</0bp0>" << endl;
			file << "\t\t<0bp1>FFF0F5FF|FFBADEFF|FF74D9FF|520528FF</0bp1>" << endl;
			file << "\t</scheme>\n" << endl;

			file << "\t<scheme>" << endl;
			file << "\t\t<name>Ultra-Pink</name>" << endl;
			file << "\t\t<bgp>52263EFF|FE04E8FF|CCE20AFF|AA7C94FF</bgp>" << endl;
			file << "\t\t<0bp0>FE9EB6FF|52263EFF|E69EB6FF|AA7C94FF</0bp0>" << endl;
			file << "\t\t<0bp1>FE9EB6FF|52263EFF|E69EB6FF|AA7C94FF</0bp1>" << endl;
			file << "\t</scheme>\n" << endl;

			file << "\t<scheme>" << endl;
			file << "\t\t<name>GrapeCherry</name>" << endl;
			file << "\t\t<bgp>FFE3FEFF|CBA0BAFF|975076FF|5A0033FF</bgp>" << endl;
			file << "\t\t<0bp0>FFE3FEFF|CBA0BAFF|975076FF|5A0033FF</0bp0>" << endl;
			file << "\t\t<0bp1>FFE3FEFF|CBA0BAFF|975076FF|5A0033FF</0bp1>" << endl;
			file << "\t</scheme>\n" << endl;

			file << "\t<scheme>" << endl;
			file << "\t\t<name>MintPink</name>" << endl;
			file << "\t\t<bgp>FFA5CEFF|19C7F0FF|33EF12FF|511733FF</bgp>" << endl;
			file << "\t\t<0bp0>FFA5CEFF|19C7F0FF|33EF12FF|511733FF</0bp0>" << endl;
			file << "\t\t<0bp1>FFA5CEFF|19C7F0FF|33EF12FF|511733FF</0bp1>" << endl;
			file << "\t</scheme>\n" << endl;

			file << "\t<scheme>" << endl;
			file << "\t\t<name>KiGB</name>" << endl;
			file << "\t\t<bgp>9CB916FF|8CAA14FF|306430FF|103F10FF</bgp>" << endl;
			file << "\t\t<0bp0>9CB916FF|8CAA14FF|306430FF|103F10FF</0bp0>" << endl;
			file << "\t\t<0bp1>9CB916FF|8CAA14FF|306430FF|103F10FF</0bp1>" << endl;
			file << "\t</scheme>\n" << endl;

			file << "\t<scheme>" << endl;
			file << "\t\t<name>BGB</name>" << endl;
			file << "\t\t<bgp>E0F8D0FF|88C070FF|346856FF|081820FF</bgp>" << endl;
			file << "\t\t<0bp0>E0F8D0FF|88C070FF|346856FF|081820FF</0bp0>" << endl;
			file << "\t\t<0bp1>E0F8D0FF|88C070FF|346856FF|081820FF</0bp1>" << endl;
			file << "\t</scheme>\n" << endl;

			file << "\t<scheme>" << endl;
			file << "\t\t<name>NO$GMB</name>" << endl;
			file << "\t\t<bgp>FCE88CFF|DCB45CFF|987C3CFF|4C3C1CFF</bgp>" << endl;
			file << "\t\t<0bp0>FCE88CFF|DCB45CFF|987C3CFF|4C3C1CFF</0bp0>" << endl;
			file << "\t\t<0bp1>FCE88CFF|DCB45CFF|987C3CFF|4C3C1CFF</0bp1>" << endl;
			file << "\t</scheme>\n" << endl;

			file << "\t<scheme>" << endl;
			file << "\t\t<name>PLAYGUY</name>" << endl;
			file << "\t\t<bgp>FFEEACFF|ACA473FF|5A5239FF|000000FF</bgp>" << endl;
			file << "\t\t<0bp0>FFEEACFF|ACA473FF|5A5239FF|000000FF</0bp0>" << endl;
			file << "\t\t<0bp1>FFEEACFF|ACA473FF|5A5239FF|000000FF</0bp1>" << endl;
			file << "\t</scheme>\n" << endl;

			file << "\t<scheme>" << endl;
			file << "\t\t<name>DREAMGBC</name>" << endl;
			file << "\t\t<bgp>FFFFFFFF|00B2B5FF|00868CFF|000000FF</bgp>" << endl;
			file << "\t\t<0bp0>FFFFFFFF|00B2B5FF|00868CFF|000000FF</0bp0>" << endl;
			file << "\t\t<0bp1>FFFFFFFF|00B2B5FF|00868CFF|000000FF</0bp1>" << endl;
			file << "\t</scheme>\n" << endl;

			file << "\t<scheme>" << endl;
			file << "\t\t<name>HEBOWIN</name>" << endl;
			file << "\t\t<bgp>FFFFFFFF|7FCC7FFF|3399B2FF|000000FF</bgp>" << endl;
			file << "\t\t<0bp0>FFFFFFFF|FFCCCCFF|7F3333FF|000000FF</0bp0>" << endl;
			file << "\t\t<0bp1>FFFFFFFF|7FCC7FFF|3399B2FF|000000FF</0bp1>" << endl;
			file << "\t</scheme>\n" << endl;

			file << "\t<scheme>" << endl;
			file << "\t\t<name>FPGABOY</name>" << endl;
			file << "\t\t<bgp>BFB9FDFF|6E58D7FF|28196BFF|000000FF</bgp>" << endl;
			file << "\t\t<0bp0>BFB9FDFF|6E58D7FF|28196BFF|000000FF</0bp0>" << endl;
			file << "\t\t<0bp1>BFB9FDFF|6E58D7FF|28196BFF|000000FF</0bp1>" << endl;
			file << "\t</scheme>\n" << endl;

			file << "\t<scheme>" << endl;
			file << "\t\t<name>GBC UP A</name>" << endl;
			file << "\t\t<bgp>FFFFFFFF|FFCCCCFF|7F3333FF|000000FF</bgp>" << endl;
			file << "\t\t<0bp0>FFFFFFFF|CCFFCCFF|337F33FF|000000FF</0bp0>" << endl;
			file << "\t\t<0bp1>FFFFFFFF|FFCCCCFF|7F3333FF|000000FF</0bp1>" << endl;
			file << "\t</scheme>\n" << endl;

			file << "\t</colorschemes>" << endl;
		}

		file.close();
		colorFile.open(path + "palettes.xml");


	}

	return colorFile;
}
