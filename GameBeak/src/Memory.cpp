#include "Core.h"
#include "Rom.h"
#include "Memory.h"
#include "MainWindow/mainwindow.h"
#include "QtDebug"

Memory::Memory(QObject* parent, Rom& rom, Cpu& cpu, bool& gbcMode, bool& forceDMGMode, MBC1& mbc1, MBC2& mbc2, MBC3& mbc3, MBC5& mbc5)
    : QObject(parent), rom(rom), cpu(cpu), GBCMode(gbcMode), forceDMGMode(forceDMGMode), mbc1(mbc1), mbc2(mbc2), mbc3(mbc3), mbc5(mbc5)
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

unsigned char Memory::readSpritePaletteRam(unsigned char address)
{
	return spritePaletteRam[address];
}

unsigned char Memory::readBackgroundPaletteRam(unsigned char address)
{
	return backgroundPaletteRam[address];
}

unsigned char Memory::readVRAMBankRam(unsigned short address, unsigned char bank)
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

unsigned char Memory::readMemory(unsigned short address)
{
    /*
	if (accessBreakpoint && memoryPointer == accessBreakpointAddress)
	{
	paused = true;
	}
    */
	if (address == 0xFF41)
	{
		return (beakRam[address] | 0x80);
	}
	else if (address == 0xFF4D && GBCMode)
	{
		// Get Speed Mode

        unsigned char returnValue = 0;
        returnValue |= (unsigned char)(cpu.preparingSpeedChange ? 1 : 0);
        returnValue |= (unsigned char)(cpu.doubleSpeedMode ? 0x80 : 0);

		return returnValue;

	}
	else if (address == 0xFF4F && GBCMode)
	{
		// Read VRAM Bank Number
        return (unsigned char)(0b11111110 | (vramBank & 0b00000001));
	}
	else if (address == 0xFF69 && GBCMode)
	{
		// Read Background Palette Ram Data.

		// BG Index: Bits 0,1,2,3,4,5: Index value. Bit 6: Unused. Bit 7: Auto-increment index on write. 0: Disabed, 1: Enabled.
        unsigned char bgIndexData = beakRam[0xFF68];
		// Retrieve index data for palette ram read.
        unsigned char index = (unsigned char)(bgIndexData & 0b00111111);

		return backgroundPaletteRam[index];
	}
	else if (address == 0xFF6B && GBCMode)
	{
		// Read Sprite Palette Ram Data.

		// Sprite Index: Bits 0,1,2,3,4,5: Index value. Bit 6: Unused. Bit 7: Auto-increment index on write. 0: Disabed, 1: Enabled.
        unsigned char spriteIndexData = beakRam[0xFF6A];
		// Retrieve index data for palette ram read.
        unsigned char index = (unsigned char)(spriteIndexData & 0b00111111);

		return spritePaletteRam[index];
	}
	else
	{
        return beakRam[address];
	}
}

QList<unsigned char> Memory::readMemory(int address, int bytes)
{
    QList<unsigned char> returnMemory;

	for (int i = 0; i < bytes; i++)
	{
		returnMemory.push_back(beakRam[address + i]);
	}

	return returnMemory;
}

//DMA Transfer
void Memory::transferDMA(unsigned char address)
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

void Memory::directMemoryWrite(unsigned short address, unsigned char value)
{
    /*
	Write to Ram without ordinary restrictions. Only to be used by hardware emulating functions and not game instructions.
    */

	beakRam[address] = value;

}

void Memory::writeMemory(unsigned short address, unsigned char value)
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
				beakRam[address] = ((beakRam[address] & 0x87) | (value & 0x78) | 0x80); //Bit 7 is always 1, Bit 0, 1, and 2 are read Only //&0x87clears bits 3, 4, 5, 6 from Stat. &0xF8 clears all but bit bit 0, 1, 2, and 7 from value being written.
			}
            else if (address == 0xFF4D && GBCMode == true)
			{
				// Set Speed Mode

                bool newSpeedSetting = (value & 0b0000 - 0001) == 1;
                emit cpu_SetDoubleSpeedMode(newSpeedSetting);
			}
            else if (address == 0xFF4F && GBCMode == true)
			{
				// Swap VRAM Bank
				swapVRAMBank(value);
			}
            else if (address == 0xFF55 && GBCMode == true)
			{
				// Initiate GBC HDMA Transfer.
				unsigned short sourceAddress = (unsigned short)((beakRam[0xFF51] << 8) | beakRam[0xFF52]);
				unsigned short targetAddress = (unsigned short)((beakRam[0xFF53] << 8) | beakRam[0xFF54]);

				// Mask off low 4 bits from addresses.
				sourceAddress &= 0xFFF0;
				targetAddress &= 0x1FF0;

				int byteTransferAmount = value * 16;

				for (int i = 0; i < byteTransferAmount; i++)
				{
					beakRam[0x8000 + targetAddress + i] = beakRam[sourceAddress + i];
				}
			}
            else if (address == 0xFF68 && GBCMode == true)
			{
				// Set GBC Background Palette Index
                beakRam[address] = (unsigned char)(0x40 | (value));
				// Bit 7: Increment on Write setting //Bit 6: Unused //Bit 0,1,2,3,4,5 Index (0-3F)
			}
            else if (address == 0xFF69 && GBCMode == true)
			{
				// Write to Background Palette Ram.

				// BG Index: Bits 0,1,2,3,4,5: Index value. Bit 6: Unused. Bit 7: Auto-increment index on write. 0: Disabed, 1: Enabled.
                unsigned char bgIndexData = beakRam[0xFF68];
				bool bgIndexAutoIncrement = (bgIndexData & 0x80) != 0;

				// Retrieve index data for palette ram write.
                unsigned char index = (unsigned char)(bgIndexData & 0b00111111);

				// Write data to palette ram at index.
				backgroundPaletteRam[index] = value;

				// Increment index data if auto-increment is enabled.
				if (bgIndexAutoIncrement)
				{
                    unsigned char newIndexData = (unsigned char)(index + 1);
					newIndexData |= 0b11000000; // Set unused and auto-increment bits to enabled.
					beakRam[0xFF68] = newIndexData;
				}
			}
            else if (address == 0xFF6A && GBCMode == true)
			{
				// Set GBC Sprite Palette Index
                beakRam[address] = (unsigned char)(0x40 | (value));
				// Bit 7: Increment on Write setting //Bit 6: Unused //Bit 0,1,2,3,4,5 Index (0-3F)
			}
            else if (address == 0xFF6B && GBCMode == true)
			{
				// Write to Sprite Palette Ram.

				// Sprite Index: Bits 0,1,2,3,4,5: Index value. Bit 6: Unused. Bit 7: Auto-increment index on write. 0: Disabed, 1: Enabled.
                unsigned char spriteIndexData = beakRam[0xFF6A];
				bool spriteIndexAutoIncrement = (spriteIndexData & 0x80) != 0;

				// Retrieve index data for palette ram write.
                unsigned char index = (unsigned char)(spriteIndexData & 0b00111111);

				// Write data to palette ram at index.
				spritePaletteRam[index] = value;

				// Increment index data if auto-increment is enabled.
				if (spriteIndexAutoIncrement)
				{
                    unsigned char newIndexData = (unsigned char)(index + 1);
					newIndexData |= 0b11000000; // Set unused and auto-increment bits to enabled.
					beakRam[0xFF6A] = newIndexData;
				}
			}
            else if (address == 0xFF70 && GBCMode == true)
			{
				// Swap WRAM Bank at 0xD000
                unsigned char bankValue = (unsigned char)(value & 0b111);

				if (bankValue == 0)
					bankValue = 1;

				swapInternalRamBank(bankValue);
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

				beakRam[address] = value;
			}
		}
	}
}

void Memory::writeMemory(unsigned short address, short shortVal)
{

    writeMemory((address + 1), (unsigned char)((shortVal & 0xFF00) >> 8));
    writeMemory((address), (unsigned char)(shortVal & 0x00FF));
}

void Memory::swapVRAMBank(unsigned char newBank)
{
	// Mask away unused data.
	newBank &= 0b00000001;

	if (vramBank != newBank)
	{
		// Swap bank in GB vram with bank in external VRAM.
		for (int i = 0; i < 0x2000; i++)
		{
            unsigned char temporarySwapByte = externalVRAMBank[i];   // Hold new data from external bank.
			externalVRAMBank[i] = beakRam[0x8000 + i];       // Write previous bank data to external bank.
			beakRam[0x8000 + i] = temporarySwapByte;         // Write new bank data to GB VRAM region.
		}

		// Set new bank number to the vram bank value.
		vramBank = newBank;
	}
}

void Memory::swapInternalRamBank(unsigned char newBank)
{
	if (internalRamBank != newBank)
	{
		if (newBank < 8)
		{
			unsigned short oldBankAddress = (unsigned short)(internalRamBank * 0x1000);
			unsigned short bankAddress = (unsigned short)(newBank * 0x1000);
			unsigned short ramAddress = 0xD000; //0xC000-CFFF is bank 0; //0xD000-DFFF is swappable

			//Write current GB ram data to internal ram bank
			for (int i = 0; i < 0x1000; i++)
			{
				internalRam[oldBankAddress + i] = beakRam[ramAddress + i];
			}

			//Write new internal ram bank data to GB ram
			for (int i = 0; i < 0x1000; i++)
			{
				beakRam[ramAddress + i] = internalRam[bankAddress + i];
			}

			// Set new bank number to the internal ram bank value.
			internalRamBank = newBank;
		}
	}
}

void Memory::toggleZFlag()
{
    unsigned char flag = getF();
	flag ^= 0x80; //Toggles left most bit
	setF(flag);
}

void Memory::setZFlag(bool setting)
{
	if (setting)
	{
        unsigned char flag = getF();
		flag |= 0x80; //Sets left most bit to 1
		setF(flag);
	}
	else
	{
        unsigned char flag = getF();
		flag &= 0x7F; //Sets left most bit to 0
		setF(flag);
	}
}

bool Memory::getZFlag()
{
    unsigned char flag = getF();
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
    unsigned char flag = getF();
	flag ^= 0x40; //Toggles second to left most bit
	setF(flag);
}

void Memory::setNFlag(bool setting)
{
	if (setting)
	{
        unsigned char flag = getF();
		flag |= 0x40; //Sets second to left most bit to 1
		setF(flag);
	}
	else
	{
        unsigned char flag = getF();
		flag &= 0xBF; //Sets second to left most bit to 0
		setF(flag);
	}
}

bool Memory::getNFlag()
{
    unsigned char flag = getF();
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
    unsigned char flag = getF();
	flag ^= 0x20; //Toggles third to left most bit
	setF(flag);
}

void Memory::setHFlag(bool setting)
{
	if (setting)
	{
        unsigned char flag = getF();
		flag |= 0x20; //Sets third to left most bit to 1
		setF(flag);
	}
	else
	{
        unsigned char flag = getF();
		flag &= 0xDF; //Sets third to left most bit to 0
		setF(flag);
	}
}

bool Memory::getHFlag()
{
    unsigned char flag = getF();
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
    unsigned char flag = getF();
	flag ^= 0x10; //Toggles fourth to left most bit
	setF(flag);
}

void Memory::setCFlag(bool setting)
{
	if (setting)
	{
        unsigned char flag = getF();
		flag |= 0x10; //Sets fourth to left most bit to 1
		setF(flag);
	}
	else
	{
        unsigned char flag = getF();
		flag &= 0xEF; //Sets fourth to left most bit to 0
		setF(flag);
	}
}

bool Memory::getCFlag()
{
    unsigned char flag = getF();
	if (((flag & 0x10) >> 4) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

unsigned char Memory::getA()
{
	return (regAF & 0xFF00) >> 8;
}

unsigned char Memory::getF()
{
	return (regAF & 0x00FF);
}

short Memory::getAF()
{
	return regAF;
}

unsigned char Memory::getB()
{
	return (regBC & 0xFF00) >> 8;
}

unsigned char Memory::getC()
{
	return (regBC & 0x00FF);
}

short Memory::getBC()
{
	return regBC;
}

unsigned char Memory::getD()
{
	return (regDE & 0xFF00) >> 8;
}

unsigned char Memory::getE()
{
	return (regDE & 0x00FF);
}

short Memory::getDE()
{
	return regDE;
}

unsigned char Memory::getH()
{
	return (regHL & 0xFF00) >> 8;
}

unsigned char Memory::getL()
{
	return (regHL & 0x00FF);
}

short Memory::getHL()
{
	return regHL;
}

void Memory::setA(unsigned char newA)
{
	regAF = regAF & 0x00FF;
	regAF |= newA << 8;
}

void Memory::setF(unsigned char newF)
{
	regAF = regAF & 0xFF00;
	regAF |= newF;
}

void Memory::setAF(short newAF)
{
	regAF = newAF & 0xFFF0;
}

void Memory::setB(unsigned char newB)
{
	regBC = regBC & 0x00FF;
	regBC |= newB << 8;
}

void Memory::setC(unsigned char newC)
{
	regBC = regBC & 0xFF00;
	regBC |= newC;
}

void Memory::setBC(short newBC)
{
	regBC = newBC;
}

void Memory::setD(unsigned char newD)
{
	regDE = regDE & 0x00FF;
	regDE |= newD << 8;
}

void Memory::setE(unsigned char newE)
{
	regDE = regDE & 0xFF00;
	regDE |= newE;
}

void Memory::setDE(short newDE)
{
	regDE = newDE;
}

void Memory::setH(unsigned char newH)
{
	regHL = regHL & 0x00FF;
	regHL |= newH << 8;
}

void Memory::setL(unsigned char newL)
{
	regHL = regHL & 0xFF00;
	regHL |= newL;
}

void Memory::setHL(short newHL)
{
	regHL = newHL;
}

unsigned char Memory::getLCDControl()
{
	return readMemory(0xFF40);
}

bool Memory::getLCDEnabled()
{
	return (((getLCDControl() & 0x80) >> 7) > 0); //Bit 7
}

unsigned char Memory::getLCDLY()
{
	return readMemory((short)0xFF44);
}

void Memory::setLCDLY(unsigned char newLY)
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
    beakRam.fill(0);
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
                writeMemory((short)(i + j), (unsigned char)(randNum & 0x000000FF)); //So it ECHO will be emulated
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
                writeMemory((short)(i + j), (unsigned char)(randNum & 0x000000FF)); //So it ECHO will be emulated
				randNum >>= 8;
			}
		}
	}

    beakRam[(unsigned short)0xFF00] = ((unsigned char)0xCF); //Joypad
    beakRam[(unsigned short)0xFF04] = ((unsigned char)0xAB);
    beakRam[(unsigned short)0xFF05] = ((unsigned char)0x00); //TIMA
    beakRam[(unsigned short)0xFF06] = ((unsigned char)0x00); //TMA
    beakRam[(unsigned short)0xFF07] = ((unsigned char)0x00); //TAC
    beakRam[(unsigned short)0xFF0F] = ((unsigned char)0xE1); //IF
    beakRam[(unsigned short)0xFF10] = ((unsigned char)0x80); //NR10
    beakRam[(unsigned short)0xFF11] = ((unsigned char)0xBF); //NR11
    beakRam[(unsigned short)0xFF12] = ((unsigned char)0xF3); //NR12
    beakRam[(unsigned short)0xFF14] = ((unsigned char)0xBF); //NR14
    beakRam[(unsigned short)0xFF16] = ((unsigned char)0x3F); //NR21
    beakRam[(unsigned short)0xFF17] = ((unsigned char)0x00); //NR22
    beakRam[(unsigned short)0xFF19] = ((unsigned char)0xBF); //NR24
    beakRam[(unsigned short)0xFF1A] = ((unsigned char)0x7F); //NR30
    beakRam[(unsigned short)0xFF1B] = ((unsigned char)0xFF); //NR31
    beakRam[(unsigned short)0xFF1C] = ((unsigned char)0x9F); //NR32
    beakRam[(unsigned short)0xFF1E] = ((unsigned char)0xBF); //NR33
    beakRam[(unsigned short)0xFF20] = ((unsigned char)0xFF); //NR41
    beakRam[(unsigned short)0xFF21] = ((unsigned char)0x00); //NR42
    beakRam[(unsigned short)0xFF22] = ((unsigned char)0x00); //NR43
    beakRam[(unsigned short)0xFF23] = ((unsigned char)0xBF); //NR30
    beakRam[(unsigned short)0xFF24] = ((unsigned char)0x77); //NR50
    beakRam[(unsigned short)0xFF25] = ((unsigned char)0xF3); //NR51
    beakRam[(unsigned short)0xFF26] = ((unsigned char)0xF1); //NR52 //F1 for GB //F0 for SGB
    beakRam[(unsigned short)0xFF40] = ((unsigned char)0x91); //LCD Ctrl
    beakRam[(unsigned short)0xFF41] = ((unsigned char)0x85); //LCD Status
    beakRam[(unsigned short)0xFF42] = ((unsigned char)0x00); //SCY
    beakRam[(unsigned short)0xFF43] = ((unsigned char)0x00); //SCX
    beakRam[(unsigned short)0xFF44] = ((unsigned char)0x00); //LY
    beakRam[(unsigned short)0xFF45] = ((unsigned char)0x00); //LYC
    beakRam[(unsigned short)0xFF47] = ((unsigned char)0xFC); //BGP
    beakRam[(unsigned short)0xFF48] = ((unsigned char)0xFF); //OBP0
    beakRam[(unsigned short)0xFF49] = ((unsigned char)0xFF); //0BP1
    beakRam[(unsigned short)0xFF4A] = ((unsigned char)0x00); //WY
    beakRam[(unsigned short)0xFF4B] = ((unsigned char)0x00); //WX
    beakRam[(unsigned short)0xFFFF] = ((unsigned char)0x00); //IE


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
                writeMemory((short)(i + j), (unsigned char)(randNum & 0x000000FF)); //So it ECHO will be emulated
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
                writeMemory((short)(i + j), (unsigned char)(randNum & 0x000000FF)); //So it ECHO will be emulated
				randNum >>= 8;
			}
		}
	}

    beakRam[(unsigned short)0xFF00] = ((unsigned char)0xCF); //Joypad
    beakRam[(unsigned short)0xFF04] = ((unsigned char)0xAB);
    beakRam[(unsigned short)0xFF05] = ((unsigned char)0x00); //TIMA
    beakRam[(unsigned short)0xFF06] = ((unsigned char)0x00); //TMA
    beakRam[(unsigned short)0xFF07] = ((unsigned char)0x00); //TAC
    beakRam[(unsigned short)0xFF0F] = ((unsigned char)0xE1); //IF
    beakRam[(unsigned short)0xFF10] = ((unsigned char)0x80); //NR10
    beakRam[(unsigned short)0xFF11] = ((unsigned char)0xBF); //NR11
    beakRam[(unsigned short)0xFF12] = ((unsigned char)0xF3); //NR12
    beakRam[(unsigned short)0xFF14] = ((unsigned char)0xBF); //NR14
    beakRam[(unsigned short)0xFF16] = ((unsigned char)0x3F); //NR21
    beakRam[(unsigned short)0xFF17] = ((unsigned char)0x00); //NR22
    beakRam[(unsigned short)0xFF19] = ((unsigned char)0xBF); //NR24
    beakRam[(unsigned short)0xFF1A] = ((unsigned char)0x7F); //NR30
    beakRam[(unsigned short)0xFF1B] = ((unsigned char)0xFF); //NR31
    beakRam[(unsigned short)0xFF1C] = ((unsigned char)0x9F); //NR32
    beakRam[(unsigned short)0xFF1E] = ((unsigned char)0xBF); //NR33
    beakRam[(unsigned short)0xFF20] = ((unsigned char)0xFF); //NR41
    beakRam[(unsigned short)0xFF21] = ((unsigned char)0x00); //NR42
    beakRam[(unsigned short)0xFF22] = ((unsigned char)0x00); //NR43
    beakRam[(unsigned short)0xFF23] = ((unsigned char)0xBF); //NR30
    beakRam[(unsigned short)0xFF24] = ((unsigned char)0x77); //NR50
    beakRam[(unsigned short)0xFF25] = ((unsigned char)0xF3); //NR51
    beakRam[(unsigned short)0xFF26] = ((unsigned char)0xF1); //NR52 //F1 for GB //F0 for SGB
    beakRam[(unsigned short)0xFF40] = ((unsigned char)0x91); //LCD Ctrl
    beakRam[(unsigned short)0xFF41] = ((unsigned char)0x85); //LCD Status
    beakRam[(unsigned short)0xFF42] = ((unsigned char)0x00); //SCY
    beakRam[(unsigned short)0xFF43] = ((unsigned char)0x00); //SCX
    beakRam[(unsigned short)0xFF44] = ((unsigned char)0x00); //LY
    beakRam[(unsigned short)0xFF45] = ((unsigned char)0x00); //LYC
    beakRam[(unsigned short)0xFF47] = ((unsigned char)0xFC); //BGP
    beakRam[(unsigned short)0xFF48] = ((unsigned char)0xFF); //OBP0
    beakRam[(unsigned short)0xFF49] = ((unsigned char)0xFF); //0BP1
    beakRam[(unsigned short)0xFF4A] = ((unsigned char)0x00); //WY
    beakRam[(unsigned short)0xFF4B] = ((unsigned char)0x00); //WX
    beakRam[(unsigned short)0xFFFF] = ((unsigned char)0x00); //IE


}

void Memory::romLoaded(QString gameFilePath) {
    loadRom(gameFilePath, true);
    rom.readRomHeader();
    rom.romFilePath = gameFilePath;
    GBCMode = rom.isGBCRom() == true && forceDMGMode == false;

    if (GBCMode == true) {
        initializeGameBoyColorValues();
    } else {
        initializeGameBoyValues();
    }

    emit setEmulationRun(true);
}

bool Memory::loadRom(QString path)
{
    QFile selectedFile(path);

    if (selectedFile.open(QIODevice::ReadOnly)) {

        QByteArray binaryFileData = selectedFile.readAll();
        int fileLength = binaryFileData.length();

        if (fileLength <= 0x500000)
		{
			int address = 0;
            for (int i = 0x0; i < fileLength; i++)
			{
                rom.beakRom[address + i] = static_cast<unsigned char>(binaryFileData.at(i));
			}
		}
		else
		{
            //cout << "Error: Rom too large. It does not fit in GameBoy's memory." << endl;
			return false;
		}
	}
	else
	{
        //cout << "Error: Rom does not exist." << endl;
		return false;
	}

    selectedFile.close();
	return true;
}

/*
Load Rom and Attempt to Load Save if selected
*/
bool Memory::loadRom(QString path, bool findAndLoadSaveFile)
{
    bool fileLoaded = loadRom(path);

    if (fileLoaded && findAndLoadSaveFile)
	{
		//Attempt to open file, if it was successful close it and call the full loadSave function
        QString savePath = path.left(path.lastIndexOf('.')) + ".sav";
        QFile saveFile(savePath);

        bool fileExists = saveFile.open(QIODevice::ReadOnly);

        if (fileExists)
        {
            QByteArray binaryFileData = saveFile.readAll();
            loadSaveFile(savePath);
		}
        saveFile.close();
        return true;
    } else {
        return false;
    }
}


/*
Load Rom From Array
*/
bool Memory::loadRom(QByteArray romData)
{
    int romSize = romData.length();
    if (romSize > 0) {
        if (romSize <= 0x500000) {
            for (int i = 0x0; i < romSize; i++) {
                rom.beakRom[i] = (unsigned char)romData[i];
			}
        } else {
            //cout << "Error: Rom too large. It does not fit in GameBoy's memory." << endl;
			return false;
		}
    } else {
        //cout << "Error: Rom is empty." << endl;
		return false;
	}

	return true;
}

/*
Load Rom And Save File From Array
*/
bool Memory::loadRom(QByteArray romData, QByteArray save)
{
    bool romLoaded = loadRom(romData);
    bool saveLoaded = loadSaveFile(save);


    return romLoaded && saveLoaded;
}



bool Memory::loadSaveFile(QString path)
{
    //Attempt to open file, if it was successful close it and call the full loadSave function
    QString savePath = path.left(path.indexOf('.')) + ".sav";
    QFile saveFile(savePath);

    bool fileOpen = saveFile.open(QIODevice::ReadOnly);

    bool saveFileLoaded = false;

    if (fileOpen)
    {
        QByteArray binaryFileData = saveFile.readAll();
        saveFileLoaded = loadSaveFile(binaryFileData);
    }
    saveFile.close();
    return saveFileLoaded;
}

/*
Load Save File From Array
*/
bool Memory::loadSaveFile(QByteArray saveFile)
{
    int fileLength = saveFile.length();
    bool fileNotEmpty = fileLength > 0;
    bool fileNotTooLarge = fileLength <= 0x2000;

    if (fileNotEmpty && fileNotTooLarge) {
        unsigned short address = 0xA000;
        for (unsigned short i = 0x0; i <= 0x1FFF; i++) {
            beakRam[address + i] = (unsigned char)saveFile[i];
        }
        return true;
    } else if(fileNotEmpty == false) {
        //cout << "Error: Save file has no data." << endl;
        return false;
    } else {
        //cout << "Error: Save file is too large." << endl;
        return false;
    }
}

QByteArray Memory::returnSaveDataFromMemory()
{
    QByteArray memory;
    unsigned short address = 0xA000;
    for (int i = 0; i <= 0x1FFF; i++) {
        memory.push_back(beakRam[address + i]);
	}

	return memory;
}

bool Memory::createSaveFile(bool overwrite) {
    /*
    00 Rom only | 01 MBC1 | 02 MBC1 + Ram | 03 MBC1 + Ram + Battery | 05 MBC2 | 06 MBC2 + Battery | 08 Rom + Ram |
    09 Rom + Ram + Battery | 0B MMM01 | 0C MMM01 + Ram | 0D MMM01 + Ram + Battery | 11 MBC3 | 12 MBC3 + Ram |
    13 MBC3 + Ram + Battery | 19 MBC5 | 1A MBC5 + Ram | 1B MBC5 + Ram + Battery | 1C MBC5 + Rumble | 1D MBC5 + Rumble + Ram |
    1E MBC5 + Rumble + Ram + Battery | 20 MBC6 | 22 MBC7 + Sensor + Rumble + Ram + Battery | FC Pocket Camera |
    FD Bandai Tama5 | FE HuC3 | FF HuC1 + Ram + Battery |
    */

    bool romUsesRam = rom.mapperSetting == 0x02 || rom.mapperSetting == 0x03 || rom.mapperSetting == 0x06 || rom.mapperSetting == 0x08 || rom.mapperSetting == 0x09 || rom.mapperSetting == 0x0C || rom.mapperSetting == 0x0D
        || rom.mapperSetting == 0x12 || rom.mapperSetting == 0x13 || rom.mapperSetting == 0x1A || rom.mapperSetting == 0x1B || rom.mapperSetting == 0x1D || rom.mapperSetting == 0x1E || rom.mapperSetting == 0x22 || rom.mapperSetting == 0xFF;

    if (romUsesRam)
    {
        QByteArray saveData = returnSaveDataFromMemory();

        //Attempt to open file, to check if it exists and potentially overwrite it.
        QString savePath = rom.romFilePath.left(rom.romFilePath.lastIndexOf('.')) + ".sav";
        QFile saveFile(savePath);

        bool fileExists = saveFile.open(QIODevice::ReadWrite);

        if (!fileExists || overwrite)
        {
            saveFile.write(saveData);
            return true;
        }
    }

    return false;
}

/*
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
            unsigned char ram = beakRam[i];

			file << hexToASCII(beakRam[i]) << ';';
		}

	}

	file.close();
}*/

/*
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
        list<unsigned char> colorValues;

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
*/
