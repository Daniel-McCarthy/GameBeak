#include "Rom.h"
#include "Memory.h"
#include "Main.h"


Memory::Memory()
{
}


Memory::~Memory()
{
}

void Memory::writeRom0ToRam()
{
	for (int i = 0; i <= 0x3FFF; i++)
	{
		beakRam[i] = rom.readByte(i);
	}
}

void Memory::writeFullRomToRam()
{
	for (int i = 0; i <= 0x7FFF; i++)
	{
		beakRam[i] = rom.readByte(i);
	}
}

byte Memory::readSpritePaletteRam(byte address)
{
	return spritePaletteRam[address];
}

byte Memory::readBackgroundPaletteRam(byte address)
{
	return backgroundPaletteRam[address];
}

byte Memory::readVRAMBankRam(unsigned short address, byte bank)
{
	//In GBC mode there are two swappable banks. The current vramBank is loaded in the ramMap. The other bank is loaded in an external bank.
	//Therefore if the selected bank isn't the current vram bank, the bank must me in the external bank.

	//If not in GBC mode, then then only bank available is bank 0, which will always be loaded in the ram map in this mode.

	if (GBCMode && vramBank != bank)
	{
		if (address >= 0x8000)
		{
			address -= 0x8000;
		}

		return externalVRAMBank[address];
	}
	else
	{
		if (address < 0x8000)
		{
			address += 0x8000;
		}

		return beakRam[address];
	}
}

vector<uint8_t> Memory::readMemory(int address, int bytes)
{
	vector<uint8_t> returnMemory;

	for (int i = 0; i < bytes; i++)
	{
		returnMemory.push_back(beakRam[address + i]);
	}

	return returnMemory;
}

//DMA Transfer
void Memory::transferDMA(byte address)
{
	//TODO:This should occur over time, not all at once


	if (address <= 0xF1)
	{
		int baseAddress = address << 8;//*= 100;

		for (int i = 0; i < 160; i++)
		{
			writeMemory(0xFE00 + i, readMemory(baseAddress + i));
		}
	}
}

void Memory::directMemoryWrite(unsigned short address, uint8_t value)
{
	/*
	Write to Ram without ordinary restrictions. Only to be used by hardware emulating functions and not game instructions.
	*/

	beakRam[address] = value;

}


void Memory::writeMemory(unsigned short address, uint8_t value)
{

	if (rom.mapperSetting > 0 && address <= 0x7FFF)
	{
		if (rom.mapperSetting <= 3)
		{
			mbc1.writeMBC1Value(address, value);
		}
		else if (rom.mapperSetting <= 6)
		{
			mbc2.writeMBC2Value(address, value);
		}
		else if (rom.mapperSetting <= 9)
		{
			//8: Rom+Ram
			//9: Rom+Ram+Battery
		}
		else if (rom.mapperSetting <= 0x0D)
		{
			//0B: MMM01
			//0C: MMM01+Ram
			//0D: MMM01+Ram+Battery
		}
		else if (rom.mapperSetting <= 0x10)
		{
			//0F: MBC3+Timer+Battery
			//10: MBC3+Timer+Ram+Battery
			//11: MBC3
			//12: MBC3+Ram
			//13: MBC3+Ram+Battery

			//Add this later: MBC3 is not currently ready (RTC)
			mbc3.writeMBC3Value(address, value);
		}
		else if (rom.mapperSetting <= 0x1E)
		{
			mbc5.writeMBC5Value(address, value);
		}
		//TODO: Add more MBC controllers

	}
	else
	{
		if (address >= 0x8000 && address <= 0xFFFF)
		{
			if (address == (unsigned short)0xFF46)
			{
				//Initiate DMA Transfer Register
				transferDMA(value);
			}
			else if (address == (unsigned short)0xFF41)
			{
				//Set LCDC Status
				beakRam[address] = ((beakRam[address] & 0x87) | (value & 0x78) | 0x80); //Bit 7 is always 1, Bit 0, 1, and 2 are read Only
																						//&0x87 clears bits 3, 4, 5, 6 from Stat. &0xF8 clears all but bit bit 0, 1, 2, and 7 from value being written.
			}
			else if (address == (unsigned short)0xFF68)
			{
				//Set GBC Background Palette Index
				beakRam[address] = (0x40 | (value));
				//Bit 7: Increment on Write //Bit 6: Unused //Bit 5-0 Index (0-35)
			}
			else if (address == (unsigned short)0xFF69)
			{
				//Write GBC Background Palette Index

				byte bgPaletteIndexRegister = readMemory(0xFF68);
				byte index = bgPaletteIndexRegister & 0x3F;

				beakGPU.gameboyColorBackGroundPalette[index] = value;

				//If Auto-Increment enabled, increment index by 1
				if ((bgPaletteIndexRegister & 0x80) > 0)
				{

					if (index >= 0x3F)
					{
						index = 0;
					}
					else
					{
						index++;
					}

					writeMemory((unsigned short)0xFF68, (byte)(index | (bgPaletteIndexRegister & 0x80)));
				}
			}
			else if (address == (unsigned short)0xFF6A)
			{
				//Set GBC Sprite Palette Index
				beakRam[address] = (0x40 | (value));
				//Bit 7: Increment on Write //Bit 6: Unused //Bit 5-0 Index (0-35)
			}
			else if (address == (unsigned short)0xFF6B)
			{
				//Write GBC Sprite Palette Index

				byte spritePaletteIndexRegister = readMemory(0xFF6A);
				byte index = spritePaletteIndexRegister & 0x3F;

				beakGPU.gameboyColorSpritePalette[index] = value;

				//If Auto-Increment enabled, increment index by 1
				if ((spritePaletteIndexRegister & 0x80) > 0)
				{

					if (index >= 0x3F)
					{
						index = 0;
					}
					else
					{
						index++;
					}

					writeMemory((unsigned short)0xFF6A, (byte)(index | (spritePaletteIndexRegister & 0x80)));
				}
			}
			else
			{
				if (address >= 0xC000 && address <= 0xDDFF)
				{
					//ECHO. Anything written to here also gets written to CXXXX
					beakRam[address + 0x2000] = value;
				}
				else if (address >= 0xE000 && address <= 0xFDFF)
				{
					beakRam[address - 0x2000] = value;
				}

				unsigned int test = (unsigned int)address;

				beakRam[address] = value;
			}
		}
	}
}

void Memory::writeMemory(unsigned short address, short shortVal)
{

	writeMemory((address + 1), (byte)((shortVal & 0xFF00) >> 8));
	writeMemory((address), (byte)(shortVal & 0x00FF));
}

void Memory::toggleZFlag()
{
	byte flag = getF();
	flag ^= 0x80; //Toggles left most bit
	setF(flag);
}

void Memory::setZFlag(bool setting)
{
	if (setting)
	{
		byte flag = getF();
		flag |= 0x80; //Sets left most bit to 1
		setF(flag);
	}
	else
	{
		byte flag = getF();
		flag &= 0x7F; //Sets left most bit to 0
		setF(flag);
	}
}

bool Memory::getZFlag()
{
	byte flag = getF();
	if (((flag & 0x80) >> 7) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Memory::toggleNFlag()
{
	byte flag = getF();
	flag ^= 0x40; //Toggles second to left most bit
	setF(flag);
}

void Memory::setNFlag(bool setting)
{
	if (setting)
	{
		byte flag = getF();
		flag |= 0x40; //Sets second to left most bit to 1
		setF(flag);
	}
	else
	{
		byte flag = getF();
		flag &= 0xBF; //Sets second to left most bit to 0
		setF(flag);
	}
}

bool Memory::getNFlag()
{
	byte flag = getF();
	if (((flag & 0x40) >> 6) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Memory::toggleHFlag()
{
	byte flag = getF();
	flag ^= 0x20; //Toggles third to left most bit
	setF(flag);
}

void Memory::setHFlag(bool setting)
{
	if (setting)
	{
		byte flag = getF();
		flag |= 0x20; //Sets third to left most bit to 1
		setF(flag);
	}
	else
	{
		byte flag = getF();
		flag &= 0xDF; //Sets third to left most bit to 0
		setF(flag);
	}
}

bool Memory::getHFlag()
{
	byte flag = getF();
	if (((flag & 0x20) >> 5) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Memory::toggleCFlag()
{
	byte flag = getF();
	flag ^= 0x10; //Toggles fourth to left most bit
	setF(flag);
}

void Memory::setCFlag(bool setting)
{
	if (setting)
	{
		byte flag = getF();
		flag |= 0x10; //Sets fourth to left most bit to 1
		setF(flag);
	}
	else
	{
		byte flag = getF();
		flag &= 0xEF; //Sets fourth to left most bit to 0
		setF(flag);
	}
}

bool Memory::getCFlag()
{
	byte flag = getF();
	if (((flag & 0x10) >> 4) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

byte Memory::getA()
{
	return (regAF & 0xFF00) >> 8;
}

byte Memory::getF()
{
	return (regAF & 0x00FF);
}

short Memory::getAF()
{
	return regAF;
}

byte Memory::getB()
{
	return (regBC & 0xFF00) >> 8;
}

byte Memory::getC()
{
	return (regBC & 0x00FF);
}

short Memory::getBC()
{
	return regBC;
}

byte Memory::getD()
{
	return (regDE & 0xFF00) >> 8;
}

byte Memory::getE()
{
	return (regDE & 0x00FF);
}

short Memory::getDE()
{
	return regDE;
}

byte Memory::getH()
{
	return (regHL & 0xFF00) >> 8;
}

byte Memory::getL()
{
	return (regHL & 0x00FF);
}

short Memory::getHL()
{
	return regHL;
}

void Memory::setA(byte newA)
{
	regAF = regAF & 0x00FF;
	regAF |= newA << 8;
}

void Memory::setF(byte newF)
{
	regAF = regAF & 0xFF00;
	regAF |= newF;
}

void Memory::setAF(short newAF)
{
	regAF = newAF & 0xFFF0;
}

void Memory::setB(byte newB)
{
	regBC = regBC & 0x00FF;
	regBC |= newB << 8;
}

void Memory::setC(byte newC)
{
	regBC = regBC & 0xFF00;
	regBC |= newC;
}

void Memory::setBC(short newBC)
{
	regBC = newBC;
}

void Memory::setD(byte newD)
{
	regDE = regDE & 0x00FF;
	regDE |= newD << 8;
}

void Memory::setE(byte newE)
{
	regDE = regDE & 0xFF00;
	regDE |= newE;
}

void Memory::setDE(short newDE)
{
	regDE = newDE;
}

void Memory::setH(byte newH)
{
	regHL = regHL & 0x00FF;
	regHL |= newH << 8;
}

void Memory::setL(byte newL)
{
	regHL = regHL & 0xFF00;
	regHL |= newL;
}

void Memory::setHL(short newHL)
{
	regHL = newHL;
}

byte Memory::getLCDControl()
{
	return readMemory(0xFF40);
}

bool Memory::getLCDEnabled()
{
	return (((getLCDControl() & 0x80) >> 7) > 0); //Bit 7
}

byte Memory::getLCDLY()
{
	return readMemory((short)0xFF44);
}

void Memory::setLCDLY(byte newLY)
{
	writeMemory((short)0xFF44, newLY);
}

void Memory::setStackPointer(short nn)
{
	stackPointer = nn;
}

void Memory::clearRegistersFlagsAndMemory()
{
	setAF(0x0000);
	setBC(0x0000);
	setDE(0x0000);
	setHL(0x0000);
	setStackPointer((short)0x0000);
	memset(beakRam, 0, 0xFFFF);
}

void Memory::clearRegistersAndFlags()
{
	setAF(0x0000);
	setBC(0x0000);
	setDE(0x0000);
	setHL(0x0000);
	setStackPointer((short)0x0000);
}

void Memory::initializeGameBoyValues()
{

	setAF(0x01B0);
	setBC(0x013);
	setDE(0x0D8);
	setHL(0x14D);
	setStackPointer((short)0xFFFE);

	srand(time(NULL));
	for (int i = 0xC000; i < 0xDFFF; i += 2)
	{
		int randNum = rand();

		for (int j = 0; j < 2; j++)
		{
			if (i < 0xDFFF)
			{
				writeMemory((short)(i + j), (byte)(randNum & 0x000000FF)); //So it ECHO will be emulated
				randNum >>= 8;
			}
		}
	}

	for (int i = 0xFF80; i < 0xFFFE; i += 2)
	{
		int randNum = rand();

		for (int j = 0; j < 2; j++)
		{
			if (i < 0xFFFE)
			{
				writeMemory((short)(i + j), (byte)(randNum & 0x000000FF)); //So it ECHO will be emulated
				randNum >>= 8;
			}
		}
	}

	beakRam[(unsigned short)0xFF00] = ((byte)0xCF); //Joypad
	beakRam[(unsigned short)0xFF04] = ((byte)0xAB);
	beakRam[(unsigned short)0xFF05] = ((byte)0x00); //TIMA
	beakRam[(unsigned short)0xFF06] = ((byte)0x00); //TMA
	beakRam[(unsigned short)0xFF07] = ((byte)0x00); //TAC
	beakRam[(unsigned short)0xFF0F] = ((byte)0xE1); //IF
	beakRam[(unsigned short)0xFF10] = ((byte)0x80); //NR10
	beakRam[(unsigned short)0xFF11] = ((byte)0xBF); //NR11
	beakRam[(unsigned short)0xFF12] = ((byte)0xF3); //NR12
	beakRam[(unsigned short)0xFF14] = ((byte)0xBF); //NR14
	beakRam[(unsigned short)0xFF16] = ((byte)0x3F); //NR21
	beakRam[(unsigned short)0xFF17] = ((byte)0x00); //NR22
	beakRam[(unsigned short)0xFF19] = ((byte)0xBF); //NR24
	beakRam[(unsigned short)0xFF1A] = ((byte)0x7F); //NR30
	beakRam[(unsigned short)0xFF1B] = ((byte)0xFF); //NR31
	beakRam[(unsigned short)0xFF1C] = ((byte)0x9F); //NR32
	beakRam[(unsigned short)0xFF1E] = ((byte)0xBF); //NR33
	beakRam[(unsigned short)0xFF20] = ((byte)0xFF); //NR41
	beakRam[(unsigned short)0xFF21] = ((byte)0x00); //NR42
	beakRam[(unsigned short)0xFF22] = ((byte)0x00); //NR43
	beakRam[(unsigned short)0xFF23] = ((byte)0xBF); //NR30
	beakRam[(unsigned short)0xFF24] = ((byte)0x77); //NR50
	beakRam[(unsigned short)0xFF25] = ((byte)0xF3); //NR51
	beakRam[(unsigned short)0xFF26] = ((byte)0xF1); //NR52 //F1 for GB //F0 for SGB
	beakRam[(unsigned short)0xFF40] = ((byte)0x91); //LCD Ctrl
	beakRam[(unsigned short)0xFF41] = ((byte)0x85); //LCD Status
	beakRam[(unsigned short)0xFF42] = ((byte)0x00); //SCY
	beakRam[(unsigned short)0xFF43] = ((byte)0x00); //SCX
	beakRam[(unsigned short)0xFF44] = ((byte)0x00); //LY
	beakRam[(unsigned short)0xFF45] = ((byte)0x00); //LYC
	beakRam[(unsigned short)0xFF47] = ((byte)0xFC); //BGP
	beakRam[(unsigned short)0xFF48] = ((byte)0xFF); //OBP0
	beakRam[(unsigned short)0xFF49] = ((byte)0xFF); //0BP1
	beakRam[(unsigned short)0xFF4A] = ((byte)0x00); //WY
	beakRam[(unsigned short)0xFF4B] = ((byte)0x00); //WX
	beakRam[(unsigned short)0xFFFF] = ((byte)0x00); //IE


}

void Memory::initializeGameBoyColorValues()
{

	setA(0x11); //AF: 0x1180
	setF(0x80);
	setB(0x00); //BC: 0x0000
	setC(0x00);
	setD(0xFF); //DE: 0xFF56
	setE(0x56);
	setH(0x00); //HL: 0x000D
	setL(0x0D);
	setStackPointer((short)0xFFFE);

	srand(time(NULL));
	for (int i = 0xC000; i < 0xDFFF; i += 2)
	{
		int randNum = rand();

		for (int j = 0; j < 2; j++)
		{
			if (i < 0xDFFF)
			{
				writeMemory((short)(i + j), (byte)(randNum & 0x000000FF)); //So it ECHO will be emulated
				randNum >>= 8;
			}
		}
	}

	for (int i = 0xFF80; i < 0xFFFE; i += 2)
	{
		int randNum = rand();

		for (int j = 0; j < 2; j++)
		{
			if (i < 0xFFFE)
			{
				writeMemory((short)(i + j), (byte)(randNum & 0x000000FF)); //So it ECHO will be emulated
				randNum >>= 8;
			}
		}
	}

	beakRam[(unsigned short)0xFF00] = ((byte)0xCF); //Joypad
	beakRam[(unsigned short)0xFF04] = ((byte)0xAB);
	beakRam[(unsigned short)0xFF05] = ((byte)0x00); //TIMA
	beakRam[(unsigned short)0xFF06] = ((byte)0x00); //TMA
	beakRam[(unsigned short)0xFF07] = ((byte)0x00); //TAC
	beakRam[(unsigned short)0xFF0F] = ((byte)0xE1); //IF
	beakRam[(unsigned short)0xFF10] = ((byte)0x80); //NR10
	beakRam[(unsigned short)0xFF11] = ((byte)0xBF); //NR11
	beakRam[(unsigned short)0xFF12] = ((byte)0xF3); //NR12
	beakRam[(unsigned short)0xFF14] = ((byte)0xBF); //NR14
	beakRam[(unsigned short)0xFF16] = ((byte)0x3F); //NR21
	beakRam[(unsigned short)0xFF17] = ((byte)0x00); //NR22
	beakRam[(unsigned short)0xFF19] = ((byte)0xBF); //NR24
	beakRam[(unsigned short)0xFF1A] = ((byte)0x7F); //NR30
	beakRam[(unsigned short)0xFF1B] = ((byte)0xFF); //NR31
	beakRam[(unsigned short)0xFF1C] = ((byte)0x9F); //NR32
	beakRam[(unsigned short)0xFF1E] = ((byte)0xBF); //NR33
	beakRam[(unsigned short)0xFF20] = ((byte)0xFF); //NR41
	beakRam[(unsigned short)0xFF21] = ((byte)0x00); //NR42
	beakRam[(unsigned short)0xFF22] = ((byte)0x00); //NR43
	beakRam[(unsigned short)0xFF23] = ((byte)0xBF); //NR30
	beakRam[(unsigned short)0xFF24] = ((byte)0x77); //NR50
	beakRam[(unsigned short)0xFF25] = ((byte)0xF3); //NR51
	beakRam[(unsigned short)0xFF26] = ((byte)0xF1); //NR52 //F1 for GB //F0 for SGB
	beakRam[(unsigned short)0xFF40] = ((byte)0x91); //LCD Ctrl
	beakRam[(unsigned short)0xFF41] = ((byte)0x85); //LCD Status
	beakRam[(unsigned short)0xFF42] = ((byte)0x00); //SCY
	beakRam[(unsigned short)0xFF43] = ((byte)0x00); //SCX
	beakRam[(unsigned short)0xFF44] = ((byte)0x00); //LY
	beakRam[(unsigned short)0xFF45] = ((byte)0x00); //LYC
	beakRam[(unsigned short)0xFF47] = ((byte)0xFC); //BGP
	beakRam[(unsigned short)0xFF48] = ((byte)0xFF); //OBP0
	beakRam[(unsigned short)0xFF49] = ((byte)0xFF); //0BP1
	beakRam[(unsigned short)0xFF4A] = ((byte)0x00); //WY
	beakRam[(unsigned short)0xFF4B] = ((byte)0x00); //WX
	beakRam[(unsigned short)0xFFFF] = ((byte)0x00); //IE


}

bool Memory::loadRom(string path)
{
	ifstream inputFile(path, ios::binary | ios::ate);

	if (inputFile.is_open())
	{
		int fileLength = (int)inputFile.tellg();
		inputFile.seekg(0, ios::beg);
		vector<char> romData(fileLength);
		inputFile.read(romData.data(), fileLength);

		if (romData.size() <= 0x500000)
		{
			
			int address = 0;// 0x100;//? //0x200;
			for (int i = 0x0; i < (int)romData.size(); i++)
			{
				//writeMemory(address + i, (uint8_t)rom.at(i));
				rom.beakRom[address + i] = (uint8_t)romData.at(i);
			}
			//rom = (Rom(romData.data, fileLength));
		}
		else
		{
			cout << "Error: Rom too large. It does not fit in GameBoy's memory." << endl;
			return false;
		}
	}
	else
	{
		cout << "Error: Rom does not exist." << endl;
		return false;
	}

	inputFile.close();

	return true;
}

/*
Load Rom and Attempt to Load Save if selected
*/
bool Memory::loadRom(string path, bool findAndLoadSaveFile)
{
	ifstream inputFile(path, ios::binary | ios::ate);

	if (inputFile.is_open())
	{
		int fileLength = (int)inputFile.tellg();
		inputFile.seekg(0, ios::beg);
		vector<char> romData(fileLength);
		inputFile.read(romData.data(), fileLength);

		if (romData.size() <= 0x500000)
		{
			int address = 0;// 0x100;//? //0x200;
			for (int i = 0x0; i < (int)romData.size(); i++)
			{
				//writeMemory(address + i, (uint8_t)rom.at(i));
				rom.beakRom[address + i] = (uint8_t)romData.at(i);
			}
		}
		else
		{
			cout << "Error: Rom too large. It does not fit in GameBoy's memory." << endl;
			return false;
		}
	}
	else
	{
		cout << "Error: Rom does not exist." << endl;
		return false;
	}

	inputFile.close();

	if (findAndLoadSaveFile)
	{
		//Attempt to open file, if it was successful close it and call the full loadSave function
		string savePath = path.substr(0, path.find_first_of('.')) + ".sav";

		ifstream saveFile(savePath, ios::binary | ios::ate);

		bool fileExists = saveFile.is_open();
		saveFile.close();

		if (fileExists)
		{
			beakMemory.loadSaveFile(savePath);
		}
	}

	return true;
}


/*
Load Rom From Array
*/
bool Memory::loadRom(byte* romData, int romSize)
{

	if (romSize > 0)
	{

		if (romSize <= 0x500000)
		{
			for (int i = 0x0; i < romSize; i++)
			{
				rom.beakRom[i] = (uint8_t)romData[i];
			}
		}
		else
		{
			cout << "Error: Rom too large. It does not fit in GameBoy's memory." << endl;
			return false;
		}
	}
	else
	{
		cout << "Error: Rom is empty." << endl;
		return false;
	}

	return true;
}

/*
Load Rom And Save File From Array
*/
bool Memory::loadRom(byte* romData, int romSize, byte* save, int saveSize)
{

	if (romSize > 0)
	{

		if (romSize <= 0x500000)
		{
			for (int i = 0x0; i < romSize; i++)
			{
				rom.beakRom[i] = (uint8_t)romData[i];
			}
		}
		else
		{
			cout << "Error: Rom too large. It does not fit in GameBoy's memory." << endl;
			return false;
		}
	}
	else
	{
		cout << "Error: Rom is empty." << endl;
		return false;
	}


	beakMemory.loadSaveFile(save, saveSize);


	return true;
}



bool Memory::loadSaveFile(string filepath)
{

	ifstream inputFile(filepath, ios::binary | ios::ate);

	if (inputFile.is_open())
	{
		int fileLength = (int)inputFile.tellg();
		inputFile.seekg(0, ios::beg);
		vector<char> savefile(fileLength);
		inputFile.read(savefile.data(), fileLength);

		if (fileLength >= 0x2000)
		{
			unsigned short address = 0xA000;
			for (unsigned short i = 0x0; i <= 0x1FFF; i++)
			{
				beakRam[address + i] = (uint8_t)savefile.at(i);
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "Error: Save file does not exist." << endl;
		return false;
	}

	inputFile.close();

	return true;
}

/*
Load Save File From Array
*/
bool Memory::loadSaveFile(byte* saveFile, int saveSize)
{

	if (saveSize > 0)
	{

		if (saveSize >= 0x2000)
		{
			unsigned short address = 0xA000;
			for (unsigned short i = 0x0; i <= 0x1FFF; i++)
			{
				beakRam[address + i] = (uint8_t)saveFile[i];
			}
		}
		else
		{
			cout << "Error: Save file is too large." << endl;
			return false;
		}
	}
	else
	{
		cout << "Error: Save file has no data." << endl;
		return false;
	}

	return true;
}

vector<uint8_t> Memory::returnSaveDataFromMemory()
{
	vector<uint8_t> memory;

	uint16_t address = 0xA000;
	for (int i = 0; i <= 0x1FFF; i++)
	{
		memory.push_back(beakRam[address + i]);
	}

	return memory;
}


void Memory::saveState()
{
	char path1[MAX_PATH];
	string path;
	GetModuleFileNameA(NULL, path1, MAX_PATH);
	path = string(path1);
	path = path.substr(0, path.find_last_of('\\') + 1);

	ofstream file(path + "save1.egg");
	if (file.is_open())
	{
		file << "[Title:]" << title << endl;
		file << "[MBC:]" << hexToASCII(rom.mapperSetting) << endl;
		file << "[Rom Bank:]" << hexToASCIIU(mapper.romBankNumber) << endl;
		file << "[Ram Bank:]" << hexToASCII(mapper.ramBankNumber) << endl;
		file << "[AF:]" << hexToASCIIU(regAF) << endl;
		file << "[BC:]" << hexToASCIIU(regBC) << endl;
		file << "[DE:]" << hexToASCIIU(regDE) << endl;
		file << "[HL:]" << hexToASCIIU(regHL) << endl;
		file << "[PC:]" << hexToASCIIU(memoryPointer) << endl;
		file << "[SP:]" << hexToASCIIU(stackPointer) << endl;
		file << "[Halt:]" << hexToASCII(cpu.returnHalt()) << endl;
		file << "[Interrupt:]" << hexToASCII(cpu.returnInterrupt()) << endl;
		file << "[PendingIMESet:]" << hexToASCII(enableInterruptsNextCycle) << endl;
		file << "[IME:]" << hexToASCII(cpu.returnIME()) << endl;
		file << "[Repeat:]" << hexToASCII(cpu.returnRepeat()) << endl;
		file << "[Clocks:]" << hexToASCII(clocks) << endl;
		file << "[GPUMode:]" << hexToASCII(beakWindow.gpuMode) << endl;
		file << "[Memory:]";

		for (int i = 0x8000; i <= 0xFFFF; i++)
		{
			byte ram = beakRam[i];

			file << hexToASCII(beakRam[i]) << ';';
		}

	}

	file.close();

	//paused = true;
}


void Memory::loadSaveState()
{
	char path1[MAX_PATH];
	string path;
	GetModuleFileNameA(NULL, path1, MAX_PATH);
	path = string(path1);
	path = path.substr(0, path.find_last_of('\\') + 1);

	ifstream savestateFile(path + "save1.egg");
	if (!savestateFile.fail())
	{
		string line;
		list<byte> colorValues;

		bool quit = false;
		bool setRomBank = false;
		bool setRamBank = false;

		while (getline(savestateFile, line) && !quit)
		{
			if (line.find("[Title:]") != string::npos)
			{
				int last = line.find_last_of(']') + 1;

				line = line.substr(last, line.length() - last);

				if (title != line)
				{
					quit = true;
				}
			}
			else if (line.find("[MBC:]") != string::npos)
			{
				int last = line.find_last_of(']') + 1;
				line = line.substr(last, line.length() - last - 2);


				unsigned int mbc = stoi(line, 0, 16);

				switch (mbc)
				{
				case 1:
				case 2:
				case 3:
				{
					//MBC1
					setRomBank = true;
					setRamBank = true;
					break;
				}
				case 5:
				case 6:
				{
					//MBC2
					setRomBank = true;
					break;
				}
				//case 0x0B:
				//case 0x0C:
				//case 0x0D:
				case 0x11:
				case 0x12:
				case 0x13:
				{
					//MBC3
					setRomBank = true;
					setRamBank = true;
					break;
				}
				case 0x19:
				case 0x1A:
				case 0x1B:
				case 0x1C:
				case 0x1D:
				case 0x1E:
				{
					//MBC5
					setRomBank = true;
					setRamBank = true;
					break;
				}
				//case 0x20:
				//case 0x22:
				//case 0xFD:
				//case 0xFE:
				//case 0xFF:


				}


			}
			else if (line.find("[Rom Bank:]") != string::npos)
			{
				if (setRomBank == true)
				{
					int last = line.find_last_of(']') + 1;
					line = line.substr(last, line.length() - last - 2);

					unsigned int romBank = stoi(line, 0, 16);

					//Change Rom Bank based on which memory controller it is
					switch (rom.mapperSetting)
					{
					case 1:
					case 2:
					case 3:
					{
						//MBC1
						mbc1.changeMBC1RomBanks(romBank);
						break;
					}
					case 5:
					case 6:
					{
						//MBC2
						mbc2.changeMBC2RomBanks(romBank);
						break;
					}
					//case 0x0B:
					//case 0x0C:
					//case 0x0D:
					case 0x11:
					case 0x12:
					case 0x13:
					{
						//MBC3
						mbc3.changeMBC3RomBanks(romBank);
						break;
					}
					case 0x19:
					case 0x1A:
					case 0x1B:
					case 0x1C:
					case 0x1D:
					case 0x1E:
					{
						//MBC5
						mbc5.changeMBC5RomBanks(romBank);
						break;
					}
					}
				}
			}
			else if (line.find("[Ram Bank:]") != string::npos)
			{
				if (setRamBank == true)
				{
					int last = line.find_last_of(']') + 1;
					line = line.substr(last, line.length() - last);

					unsigned int ramBank = stoi(line, 0, 16);


					mapper.changeRamBanks(ramBank);
				}
			}
			else if (line.find("[AF:]") != string::npos)
			{
				int last = line.find_last_of(']') + 1;
				line = line.substr(last, line.length() - last);

				unsigned int af = stoi(line, 0, 16);

				setAF(af);
			}
			else if (line.find("[BC:]") != string::npos)
			{
				int last = line.find_last_of(']') + 1;
				line = line.substr(last, line.length() - last);

				unsigned int bc = stoi(line, 0, 16);

				setBC(bc);
			}
			else if (line.find("[DE:]") != string::npos)
			{
				int last = line.find_last_of(']') + 1;
				line = line.substr(last, line.length() - last);

				unsigned int de = stoi(line, 0, 16);

				setDE(de);
			}
			else if (line.find("[HL:]") != string::npos)
			{
				int last = line.find_last_of(']') + 1;
				line = line.substr(last, line.length() - last);

				unsigned int hl = stoi(line, 0, 16);

				setHL(hl);
			}
			else if (line.find("[PC:]") != string::npos)
			{
				int last = line.find_last_of(']') + 1;
				line = line.substr(last, line.length() - last);

				unsigned int pc = stoi(line, 0, 16);

				memoryPointer = pc;
			}
			else if (line.find("[SP:]") != string::npos)
			{
				int last = line.find_last_of(']') + 1;
				line = line.substr(last, line.length() - last);

				unsigned int sp = stoi(line, 0, 16);

				stackPointer = sp;
			}
			else if (line.find("[HALT:]") != string::npos)
			{
				int last = line.find_last_of(']') + 1;
				line = line.substr(last, line.length() - last);

				unsigned int halt = stoi(line, 0, 16);

				cpu.setHalt(halt > 0);
			}
			else if (line.find("[Interrupt:]") != string::npos)
			{
				int last = line.find_last_of(']') + 1;
				line = line.substr(last, line.length() - last);

				unsigned int interruptVal = stoi(line, 0, 16);

				cpu.setInterrupt(interruptVal > 0);
			}
			else if (line.find("[PendingIMESet:]") != string::npos)
			{
				int last = line.find_last_of(']') + 1;
				line = line.substr(last, line.length() - last);

				unsigned int imeSet = stoi(line, 0, 16);

				enableInterruptsNextCycle = (imeSet > 0);
			}
			else if (line.find("[IME:]") != string::npos)
			{
				int last = line.find_last_of(']') + 1;
				line = line.substr(last, line.length() - last);

				unsigned int ime = stoi(line, 0, 16);

				cpu.setIME(ime > 0);
			}
			else if (line.find("[Repeat:]") != string::npos)
			{
				int last = line.find_last_of(']') + 1;
				line = line.substr(last, line.length() - last);

				unsigned int repeat = stoi(line, 0, 16);

				cpu.setRepeat(repeat > 0);
			}
			else if (line.find("[Clocks:]") != string::npos)
			{
				int last = line.find_last_of(']') + 1;
				line = line.substr(last, line.length() - last);

				unsigned int clocksVal = stoi(line, 0, 16);

				clocks = clocksVal;
			}
			else if (line.find("[GPUMode:]") != string::npos)
			{
				int last = line.find_last_of(']') + 1;
				line = line.substr(last, line.length() - last);

				unsigned int gpuMode = stoi(line, 0, 16);

				beakWindow.gpuMode = gpuMode;
			}
			else if (line.find("[Memory:]") != string::npos)
			{
				int last = line.find_last_of(']') + 1;
				line = line.substr(last, line.length() - last);

				for (int i = 0x8000; i <= 0xFFFF; i++)
				{
					int nextDelimiter = line.find_first_of(';');
					beakRam[i] = stoi(line.substr(0, nextDelimiter), 0, 16);
					line = line.substr(nextDelimiter + 1, line.length() - (nextDelimiter + 1));
				}
			}
		}
	}
	//paused = true;
}

