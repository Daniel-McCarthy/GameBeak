#include "Gpu.h"
#include "Core.h"
#include <vector>

#include <QTextStream>
#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>

Gpu::Gpu(Memory& memory, Screen& screen, bool& gbcMode)
    : memory(memory), screen(screen), GBCMode(gbcMode)
{
}

Gpu::~Gpu()
{
}

unsigned char Gpu::getLCDStatus()
{
    return memory.readMemory(0xFF41);
}

void Gpu::setLCDStatus(unsigned char newStatus)
{
    memory.directMemoryWrite(0xFF41, newStatus);
}

void Gpu::setLCDMode(unsigned char status)
{
    memory.directMemoryWrite(0xFF41, (unsigned char)((getLCDStatus() & 0xFC) | status));
}

unsigned char Gpu::getLCDMode()
{
    return (getLCDStatus() & 0x03);
}

unsigned char Gpu::getLCDLYCCheckEnabled()
{
    return (getLCDStatus() & 0x40) >> 6;
}

unsigned char Gpu::getLCDLYCompare()
{
    return memory.readMemory(0xFF45);
}

unsigned char Gpu::getLCDLY()
{
    return memory.readMemory(0xFF44);
}

unsigned char Gpu::getLCDControl()
{
    return memory.readMemory(0xFF40);
}

bool Gpu::getLCDOn()
{
    return ((getLCDControl() & 0x80) >> 7) > 0;
}

bool Gpu::getWindowTileMapLocation()
{
    return ((getLCDControl() & 0x40) >> 6) > 0;
}

bool Gpu::getWindowEnabled()
{
    return ((getLCDControl() & 0x20) >> 5) > 0;
}

bool Gpu::getBackGroundWindowTileSetLocation()
{
    return ((getLCDControl() & 0x10) >> 4) > 0;
}

bool Gpu::getBackGroundTileMapLocation()
{
    return ((getLCDControl() & 0x08) >> 3) > 0;
}

bool Gpu::getSpriteSize()
{
    return ((getLCDControl() & 0x04) >> 2) > 0;
}

bool Gpu::getSpriteEnabled()
{
    return ((getLCDControl() & 0x02) >> 1) > 0;
}

bool Gpu::getBackGroundEnabled()
{
    return (getLCDControl() & 0x01);
}

//DrawLineFromMap: Draws a single specific line of the background map
void Gpu::drawLineFromBGMap(unsigned char  lineY)
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

        tileID = memory.readVRAMBankRam(tileIDAddress, 0);

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
        unsigned char vramBankSelection = 0; //DMG only has bank 0.
        unsigned char gbcBGPalette = 0;

        if (GBCMode == true)
        {
            unsigned char tileFlags = memory.readVRAMBankRam((unsigned short)(tileIndex + 0x1800), 1);
            gbcBGPalette = (unsigned char)(tileFlags & 0b0111);
            vramBankSelection = (unsigned char)((tileFlags & 0b1000) >> 3);
            bool horizontalFlip = (tileFlags & 0b0010 - 0000) > 0;
            bool verticalFlip = (tileFlags & 0b0100 - 0000) > 0;
            bool hasPriority = (tileFlags & 0b1000 - 0000) > 0;

        }

        rowHalf1 = memory.readVRAMBankRam(tileAddress + (lineToDraw * 2), 0);
        rowHalf2 = memory.readVRAMBankRam(tileAddress + (lineToDraw * 2) + 1, 0);

        for (int j = 0; j < 8; j++)
        {
            QColor pixelColor;

            if (GBCMode == false)
            {
                pixelColor = returnColor(((rowHalf1 & 0x80) >> 7) | ((rowHalf2 & 0x80) >> 6), 0);
            }
            else
            {
                pixelColor = returnGBCBackgroundColor((unsigned char)(((rowHalf1 & 0x80) >> 7) | ((rowHalf2 & 0x80) >> 6)), gbcBGPalette);
            }

            screen.setBGPixel((unsigned char)((i * 8) + j), (unsigned char)lineY, pixelColor);
            rowHalf1 <<= 1;
            rowHalf2 <<= 1;


        }

    }

}

void Gpu::drawLineFromWindowMap(unsigned char lineY)
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
    unsigned char vramBankSelection = 0; //DMG only has bank 0.
    unsigned char gbcBGPalette = 0;

    for (int i = 0; i < 32; i++)
    {

        tileY = (lineY) / 8;
        tileX = (i);
        tileIndex = tileX + (32 * tileY);
        tileIDAddress = mapAddress + tileIndex;

        tileID = memory.readVRAMBankRam(tileIDAddress, 0);

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

        if (GBCMode == true)
        {
            unsigned char tileFlags = memory.readVRAMBankRam((unsigned short)(tileIndex + 0x1C00), 1);
            gbcBGPalette = (unsigned char)(tileFlags & 0b0111);
            vramBankSelection = (unsigned char)((tileFlags & 0b1000) >> 3);
            bool horizontalFlip = (tileFlags & 0b0010 - 0000) > 0;
            bool verticalFlip = (tileFlags & 0b0100 - 0000) > 0;
            bool hasPriority = (tileFlags & 0b1000 - 0000) > 0;

        }

        rowHalf1 = memory.readVRAMBankRam(tileAddress + (lineToDraw * 2), 0);
        rowHalf2 = memory.readVRAMBankRam(tileAddress + (lineToDraw * 2) + 1, 0);

        for (int j = 0; j < 8; j++)
        {
            QColor pixelColor;

            if (GBCMode == false)
            {
                pixelColor = returnColor(((rowHalf1 & 0x80) >> 7) | ((rowHalf2 & 0x80) >> 6), 0);
            }
            else
            {
                pixelColor = returnGBCBackgroundColor((unsigned char)(((rowHalf1 & 0x80) >> 7) | ((rowHalf2 & 0x80) >> 6)), gbcBGPalette);
            }

            screen.setWindowPixel((unsigned char)((i * 8) + j), (unsigned char)lineY, pixelColor);
            rowHalf1 &= 0x7F;
            rowHalf1 <<= 1;
            rowHalf2 &= 0x7F;
            rowHalf2 <<= 1;
        }
    }
}

#include "Binary.h"

void Gpu::drawLineFromSpriteMap(unsigned char lineY)
{
    //Todo: Support priority.

    int mapAddress = 0xFE00;
    int baseAddress = 0x8000;

    //False: 8x8 | True: 8x16
    bool spriteSize = getSpriteSize();

    int y = 0;
    unsigned char x = 0;
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
    bool dmgPaletteSetting = false;
    unsigned char gbcPaletteSetting = 0;

    unsigned char scrollX = getScrollX();
    unsigned char scrollY = getScrollY();

    QColor bgColor = returnColor(0, 0);

    for (int i = 0; i < 40; i++)
    {
        y = memory.readMemory(mapAddress + (i * 4)) - 16;

        if (y > -8)
        {
            x = memory.readMemory(mapAddress + (i * 4) + 1) - 8;
            bool isSpriteOnLine = (y <= lineY) && ((y + ((spriteSize == 0) ? 8 : 16)) > lineY);

            if (isSpriteOnLine)
            {


                lineToDraw = lineY - y;

                tileNumber = memory.readMemory(mapAddress + (i * 4) + 2);
                tileFlags = memory.readMemory(mapAddress + (i * 4) + 3);
                priority = ((tileFlags & 0x80) >> 7) > 0; //If 1, displays in front of window. Otherwise is below window and above BG
                yFlip = ((tileFlags & 0x40) >> 6) > 0; //Vertically flipped if 1, else 0.
                xFlip = ((tileFlags & 0x20) >> 5) > 0; //Horizontally flipped if 1, else 0;
                dmgPaletteSetting = ((tileFlags & 0x10) >> 4) > 0; //Palette is OBJ0PAL if 0, else OBJ1PAL
                gbcPaletteSetting = (unsigned char)(tileFlags & 0b111);

                tileOffset = tileNumber * 16;
                tileAddress = baseAddress + tileOffset;

                if (yFlip)
                {
                    lineToDraw = ((spriteSize) ? 15 : 7) - lineToDraw;
                }

                rowHalf1 = memory.readVRAMBankRam(tileAddress + (lineToDraw * 2), 0);
                rowHalf2 = memory.readVRAMBankRam(tileAddress + (lineToDraw * 2) + 1, 0);

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
                        if (!priority || (priority && (screen.getBGPixel(scrollX + x + j, lineY + scrollY) == bgColor)))
                        {
                            QColor pixelColor;

                            if (GBCMode == false)
                            {
                                pixelColor = returnColor(colorNumber, dmgPaletteSetting + 1); //Plus 1 because 0 is BG palette, so value must be 1 or 2 to access OBJ1 or OBj2.
                            }
                            else
                            {
                                pixelColor = returnGBCSpriteColor(colorNumber, gbcPaletteSetting);
                            }

                            screen.setSpritePixel((unsigned char)(x + j), (unsigned char)lineY, pixelColor);
                        }
                    }

                    rowHalf1 <<= 1;
                    rowHalf2 <<= 1;
                }

            }
        }
    }
}

unsigned char Gpu::getScrollX()
{
    return memory.readMemory(0xFF43);
}

unsigned char Gpu::getScrollY()
{
    return memory.readMemory(0xFF42);
}

unsigned char Gpu::getWindowX()
{
    return memory.readMemory(0xFF4B);
}

unsigned char Gpu::getWindowY()
{
    return memory.readMemory(0xFF4A);
}

QColor Gpu::returnColor(int colorNumber)
{
    return gameBeakPalette[paletteSetting].paletteColors[colorNumber];
}

QColor Gpu::returnColor(int colorNumber, int palette)
{
    //Palette: 0 = BGP
    //Palette: 1 = 0BP0
    //Palette: 2 = 0BP1

    //Palette decides between BGP (0xFF47), 0BP0 (0xFF48), and 0BP1 (0xFF49)
    //Color number decides which color slot is selected from the palette data.
    //The value returned from the palette data is then used to index from the emulator's palette array.

    //unsigned char paletteData = memory->readMemory(0xFF47 + palette);
    //colorNumber = (paletteData & (3 << (colorNumber * 2))) >> (colorNumber * 2);//(colorNumber + 1);
    //return gameBeakPalette[paletteSetting].paletteColors[colorNumber];

    return gameBeakPalette[paletteSetting].paletteColors[((memory.readMemory(0xFF47 + palette) & (3 << (colorNumber * 2))) >> (colorNumber * 2)) + (palette << 2)];


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

QColor Gpu::returnGBCSpriteColor(unsigned char colorNumber, unsigned char palette)
{
    // There are 4 colors per palette and 8 Sprite palettes.
    // Each color is defined by 2 unsigned chars. Therefore 8 unsigned chars per palette.
    unsigned char paletteAddress = (unsigned char)(palette * 8);
    unsigned char colorIndex = (unsigned char)(colorNumber * 2);

    unsigned char paletteData1 = memory.readSpritePaletteRam((unsigned char)(paletteAddress + colorIndex + 1));
    unsigned char paletteData2 = memory.readSpritePaletteRam((unsigned char)(paletteAddress + colorIndex + 0));

    // GBC Colors are 5 bit. 0-31 data range. Shifting them left by 3 allows them to be used as 8 bit colors.
    unsigned short rgbData = (unsigned short)(paletteData1 << 8 | paletteData2);
    unsigned char r = (unsigned char)(rgbData & (0x1F));
    unsigned char g = (unsigned char)((rgbData & (0x1F << 5)) >> 5);
    unsigned char b = (unsigned char)((rgbData & (0x1F << 10)) >> 10);

    r <<= 3;
    g <<= 3;
    b <<= 3;

    return QColor(r, g, b);
}

QColor Gpu::returnGBCBackgroundColor(unsigned char colorNumber, unsigned char palette)
{
    // There are 4 colors per palette and 8 BG palettes.
    // Each color is defined by 2 unsigned chars. Therefore 8 unsigned chars per palette.
    unsigned char paletteAddress = (unsigned char)(palette * 8);
    unsigned char colorIndex = (unsigned char)(colorNumber * 2);

    unsigned char paletteData1 = memory.readBackgroundPaletteRam((unsigned char)(paletteAddress + colorIndex + 1));
    unsigned char paletteData2 = memory.readBackgroundPaletteRam((unsigned char)(paletteAddress + colorIndex + 0));

    // GBC Colors are 5 bit. 0-31 data range. Shifting them left by 3 allows them to be used as 8 bit colors.
    unsigned short rgbData = (unsigned short)(paletteData1 << 8 | paletteData2);
    unsigned char r = (unsigned char)(rgbData & (0x1F));
    unsigned char g = (unsigned char)((rgbData & (0x1F << 5)) >> 5);
    unsigned char b = (unsigned char)((rgbData & (0x1F << 10)) >> 10);

    r <<= 3;
    g <<= 3;
    b <<= 3;

    return QColor(r, g, b);
}

unsigned char Gpu::returnPalette(unsigned char palette)
{
    //Palette: 0 = BGP
    //Palette: 1 = 0BP0
    //Palette: 2 = 0BP1
    return memory.readMemory(0xFF47 + palette);
}

void Gpu::loadPalettesFromXML(QFile* file)
{
    QString line;
    QList<unsigned char> colorValues;
    QList<QColor> paletteColors;
    QList<QString> paletteNames;

    if (file->open(QIODevice::ReadOnly)) {
        QTextStream text(file);

        QRegExp bgp("<bgp>.*</bgp>"); //Contains both <bgp> and </bgp>
        QRegExp bp0("<0bp0>.*</0bp0>"); //Contains both <0bp0> and </0bp0>
        QRegExp bp1("<0bp1>.*</0bp1>"); //Contains both <0bp1> and </0bp1>
        QRegExp name("<name>.*</name>");

        gameBeakPalette.clear();
        while (!text.atEnd()) {
            line = text.readLine();

            // Add name to list of palettes.
            if (line.contains(name)) {
                int first = line.indexOf('>') + 1;
                int last = line.lastIndexOf('<');
                paletteNames.push_back(line.mid(first, last - first));
            }

            bool test1 = (line.contains(bgp));
            bool test2 = (line.contains(bp0));
            bool test3 = (line.contains(bp1));

            if (test1 || test2 || test3) {
                int first = line.indexOf('>') + 1;
                int last = line.lastIndexOf('<');

                line = line.mid(first, last - first);

                for (int i = 0; i < 4; i++) {
                    unsigned char r = line.mid(0, 2).toUInt(NULL, 16) & 0xFF;
                    unsigned char g = line.mid(2, 2).toUInt(NULL, 16) & 0xFF;
                    unsigned char b = line.mid(4, 2).toUInt(NULL, 16) & 0xFF;

                    colorValues.push_back(r);
                    colorValues.push_back(g);
                    colorValues.push_back(b);

                    if (line.length() > 8) {
                        line = line.mid(9, line.length() - 9);
                    }
                }

            }
        }
        if (colorValues.count() >= 36) {
            while (colorValues.count() >= 4)
            {
                for (int i = 0; i < 4; i++)
                {
                    int r = colorValues.front();
                    colorValues.pop_front();
                    int g = colorValues.front();
                    colorValues.pop_front();
                    int b = colorValues.front();
                    colorValues.pop_front();

                    QColor color = QColor(r, g, b, 255);
                    paletteColors.push_back(color);
                }
            }
        }
    }

    // Assemble names and colors into Palette structs for storage.
    int palettesTotal = paletteNames.count();
    for (int i =  0; i < palettesTotal; i++) {
        if (paletteColors.count() >= 12) {
            gameBeakPalette.push_back({
                paletteNames[0],
                {
                  paletteColors[0], paletteColors[1], paletteColors[2], paletteColors[3],
                  paletteColors[4], paletteColors[5], paletteColors[6], paletteColors[7],
                  paletteColors[8], paletteColors[9], paletteColors[10], paletteColors[11],
                },
            });
        }

        paletteNames.pop_front();
        for (int j = 0; j < 12; j++) {
            paletteColors.pop_front();
        }
    }

    file->close();
}

QString Gpu::openCreatePalettesXML()
{
    //open XML palette file
    QString path = QDir(QFileInfo(QCoreApplication::applicationFilePath()).absolutePath()).filePath("palettes.xml");

    QFileInfo fileStatus(path);

    if (fileStatus.exists() && fileStatus.isFile()) {
        return path;
    }

    QFile file(path);

    if (file.open(QIODevice::WriteOnly)) {
        QTextStream textStream(&file);

        textStream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
        textStream << "<colorschemes>\n" << endl;

        textStream << "\t<scheme>" << endl;
        textStream << "\t\t<name>BlackWhite</name>" << endl;
        textStream << "\t\t<bgp>FFFFFFFF|B9B9B9FF|696969FF|000000FF</bgp>" << endl;
        textStream << "\t\t<0bp0>FFFFFFFF|B9B9B9FF|696969FF|000000FF</0bp0>" << endl;
        textStream << "\t\t<0bp1>FFFFFFFF|B9B9B9FF|696969FF|000000FF</0bp1>" << endl;
        textStream << "\t</scheme>\n" << endl;

        textStream << "\t<scheme>" << endl;
        textStream << "\t\t<name>Green</name>" << endl;
        textStream << "\t\t<bgp>E0FFEBFF|88D058FF|34B73CFF|084703FF</bgp>" << endl;
        textStream << "\t\t<0bp0>E0FFEBFF|88D058FF|34B73CFF|084703FF</0bp0>" << endl;
        textStream << "\t\t<0bp1>E0FFEBFF|88D058FF|34B73CFF|084703FF</0bp1>" << endl;
        textStream << "\t</scheme>\n" << endl;

        textStream << "\t<scheme>" << endl;
        textStream << "\t\t<name>Pink</name>" << endl;
        textStream << "\t\t<bgp>FFF1FEFF|FFD6F5FF|FF83D9FF|48183BFF</bgp>" << endl;
        textStream << "\t\t<0bp0>FFF1FEFF|FFD6F5FF|FF83D9FF|48183BFF</0bp0>" << endl;
        textStream << "\t\t<0bp1>FFF1FEFF|FFD6F5FF|FF83D9FF|48183BFF</0bp1>" << endl;
        textStream << "\t</scheme>\n" << endl;

        textStream << "\t<scheme>" << endl;
        textStream << "\t\t<name>PinkAlt</name>" << endl;
        textStream << "\t\t<bgp>FFF0F5FF|FFBADEFF|FF74D9FF|520528FF</bgp>" << endl;
        textStream << "\t\t<0bp0>FFF0F5FF|FFBADEFF|FF74D9FF|520528FF</0bp0>" << endl;
        textStream << "\t\t<0bp1>FFF0F5FF|FFBADEFF|FF74D9FF|520528FF</0bp1>" << endl;
        textStream << "\t</scheme>\n" << endl;

        textStream << "\t<scheme>" << endl;
        textStream << "\t\t<name>Ultra-Pink</name>" << endl;
        textStream << "\t\t<bgp>52263EFF|FE04E8FF|CCE20AFF|AA7C94FF</bgp>" << endl;
        textStream << "\t\t<0bp0>FE9EB6FF|52263EFF|E69EB6FF|AA7C94FF</0bp0>" << endl;
        textStream << "\t\t<0bp1>FE9EB6FF|52263EFF|E69EB6FF|AA7C94FF</0bp1>" << endl;
        textStream << "\t</scheme>\n" << endl;

        textStream << "\t<scheme>" << endl;
        textStream << "\t\t<name>GrapeCherry</name>" << endl;
        textStream << "\t\t<bgp>FFE3FEFF|CBA0BAFF|975076FF|5A0033FF</bgp>" << endl;
        textStream << "\t\t<0bp0>FFE3FEFF|CBA0BAFF|975076FF|5A0033FF</0bp0>" << endl;
        textStream << "\t\t<0bp1>FFE3FEFF|CBA0BAFF|975076FF|5A0033FF</0bp1>" << endl;
        textStream << "\t</scheme>\n" << endl;

        textStream << "\t<scheme>" << endl;
        textStream << "\t\t<name>MintPink</name>" << endl;
        textStream << "\t\t<bgp>FFA5CEFF|19C7F0FF|33EF12FF|511733FF</bgp>" << endl;
        textStream << "\t\t<0bp0>FFA5CEFF|19C7F0FF|33EF12FF|511733FF</0bp0>" << endl;
        textStream << "\t\t<0bp1>FFA5CEFF|19C7F0FF|33EF12FF|511733FF</0bp1>" << endl;
        textStream << "\t</scheme>\n" << endl;

        textStream << "\t<scheme>" << endl;
        textStream << "\t\t<name>KiGB</name>" << endl;
        textStream << "\t\t<bgp>9CB916FF|8CAA14FF|306430FF|103F10FF</bgp>" << endl;
        textStream << "\t\t<0bp0>9CB916FF|8CAA14FF|306430FF|103F10FF</0bp0>" << endl;
        textStream << "\t\t<0bp1>9CB916FF|8CAA14FF|306430FF|103F10FF</0bp1>" << endl;
        textStream << "\t</scheme>\n" << endl;

        textStream << "\t<scheme>" << endl;
        textStream << "\t\t<name>BGB</name>" << endl;
        textStream << "\t\t<bgp>E0F8D0FF|88C070FF|346856FF|081820FF</bgp>" << endl;
        textStream << "\t\t<0bp0>E0F8D0FF|88C070FF|346856FF|081820FF</0bp0>" << endl;
        textStream << "\t\t<0bp1>E0F8D0FF|88C070FF|346856FF|081820FF</0bp1>" << endl;
        textStream << "\t</scheme>\n" << endl;

        textStream << "\t<scheme>" << endl;
        textStream << "\t\t<name>NO$GMB</name>" << endl;
        textStream << "\t\t<bgp>FCE88CFF|DCB45CFF|987C3CFF|4C3C1CFF</bgp>" << endl;
        textStream << "\t\t<0bp0>FCE88CFF|DCB45CFF|987C3CFF|4C3C1CFF</0bp0>" << endl;
        textStream << "\t\t<0bp1>FCE88CFF|DCB45CFF|987C3CFF|4C3C1CFF</0bp1>" << endl;
        textStream << "\t</scheme>\n" << endl;

        textStream << "\t<scheme>" << endl;
        textStream << "\t\t<name>PLAYGUY</name>" << endl;
        textStream << "\t\t<bgp>FFEEACFF|ACA473FF|5A5239FF|000000FF</bgp>" << endl;
        textStream << "\t\t<0bp0>FFEEACFF|ACA473FF|5A5239FF|000000FF</0bp0>" << endl;
        textStream << "\t\t<0bp1>FFEEACFF|ACA473FF|5A5239FF|000000FF</0bp1>" << endl;
        textStream << "\t</scheme>\n" << endl;

        textStream << "\t<scheme>" << endl;
        textStream << "\t\t<name>DREAMGBC</name>" << endl;
        textStream << "\t\t<bgp>FFFFFFFF|00B2B5FF|00868CFF|000000FF</bgp>" << endl;
        textStream << "\t\t<0bp0>FFFFFFFF|00B2B5FF|00868CFF|000000FF</0bp0>" << endl;
        textStream << "\t\t<0bp1>FFFFFFFF|00B2B5FF|00868CFF|000000FF</0bp1>" << endl;
        textStream << "\t</scheme>\n" << endl;

        textStream << "\t<scheme>" << endl;
        textStream << "\t\t<name>HEBOWIN</name>" << endl;
        textStream << "\t\t<bgp>FFFFFFFF|7FCC7FFF|3399B2FF|000000FF</bgp>" << endl;
        textStream << "\t\t<0bp0>FFFFFFFF|FFCCCCFF|7F3333FF|000000FF</0bp0>" << endl;
        textStream << "\t\t<0bp1>FFFFFFFF|7FCC7FFF|3399B2FF|000000FF</0bp1>" << endl;
        textStream << "\t</scheme>\n" << endl;

        textStream << "\t<scheme>" << endl;
        textStream << "\t\t<name>FPGABOY</name>" << endl;
        textStream << "\t\t<bgp>BFB9FDFF|6E58D7FF|28196BFF|000000FF</bgp>" << endl;
        textStream << "\t\t<0bp0>BFB9FDFF|6E58D7FF|28196BFF|000000FF</0bp0>" << endl;
        textStream << "\t\t<0bp1>BFB9FDFF|6E58D7FF|28196BFF|000000FF</0bp1>" << endl;
        textStream << "\t</scheme>\n" << endl;

        textStream << "\t<scheme>" << endl;
        textStream << "\t\t<name>GBC UP A</name>" << endl;
        textStream << "\t\t<bgp>FFFFFFFF|FFCCCCFF|7F3333FF|000000FF</bgp>" << endl;
        textStream << "\t\t<0bp0>FFFFFFFF|CCFFCCFF|337F33FF|000000FF</0bp0>" << endl;
        textStream << "\t\t<0bp1>FFFFFFFF|FFCCCCFF|7F3333FF|000000FF</0bp1>" << endl;
        textStream << "\t</scheme>\n" << endl;

        textStream << "\t</colorschemes>" << endl;
    }

    file.close();

    return path;
}

void Gpu::savePalettesToFile()
{
    auto ucharToHexString = [](unsigned char byte) {
      QString hexByte = QString::number(byte, 16);
      while (hexByte.length() < 2) {
          hexByte = '0' + hexByte;
      }
      return hexByte;
    };

    auto qcolorToHexString = [ucharToHexString](QColor &color) {
        unsigned char r = color.red(), g = color.green(), b = color.blue(), a = color.alpha();
        return (ucharToHexString(r) + ucharToHexString(g) + ucharToHexString(b) + ucharToHexString(a)).toUpper();
    };

    auto writeSchemeLine = [qcolorToHexString](Palette& palette, QTextStream& textStream, int offset, QString paletteType) {
        QString color1 = qcolorToHexString(palette.paletteColors[offset + 0]);
        QString color2 = qcolorToHexString(palette.paletteColors[offset + 1]);
        QString color3 = qcolorToHexString(palette.paletteColors[offset + 2]);
        QString color4 = qcolorToHexString(palette.paletteColors[offset + 3]);

        textStream << "\t\t<" + paletteType  + ">" + color1 + '|' + color2 + '|' + color3 + '|' + color4 + "</" + paletteType  + ">" << endl;
    };

    //open XML palette file
    QDir directory = QDir(QFileInfo(QCoreApplication::applicationFilePath()).absolutePath());
    QString filePath = directory.filePath("palettes.xml");

    QFile file(filePath);

    // Make a back up of the palettes file if none exists.
    file.copy(filePath, directory.filePath("palettes.copy.xml"));

    // Delete original palettes.xml file to write from scratch.
    file.remove();

    if (file.open(QIODevice::WriteOnly)) {
        QTextStream textStream(&file);

        // Write start of xml file.
        textStream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
        textStream << "<colorschemes>\n" << endl;

        // Write each of the palettes to the file.
        for (int i = 0; i < gameBeakPalette.count(); i++) {
            // Write name of the palette.
            textStream << "\t<scheme>" << endl;
            textStream << "\t\t<name>" + gameBeakPalette[i].paletteName + "</name>" << endl;

            writeSchemeLine(gameBeakPalette[i], textStream, 0, "bgp");
            writeSchemeLine(gameBeakPalette[i], textStream, 4, "0bp0");
            writeSchemeLine(gameBeakPalette[i], textStream, 8, "0bp1");

            // Write end of current palette.
            textStream << "\t</scheme>\n" << endl;
        }

        // Write end of palettes file.
        textStream << "\t</colorschemes>" << endl;
    }

    file.close();
}

void Gpu::resetGPU() {
    // User palette settings should remain the same on new rom load for consistency and convenience.

    memset(gameboyColorBackGroundPalette, 0, sizeof(gameboyColorBackGroundPalette));
    memset(gameboyColorSpritePalette, 0, sizeof(gameboyColorSpritePalette));
}
