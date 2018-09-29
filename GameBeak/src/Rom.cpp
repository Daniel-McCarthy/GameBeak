#include "src/Rom.h"
#include "src/Memory.h"

Rom::Rom(QWidget *parent) : QWidget(parent) {}
Rom::~Rom() {}

Rom::Rom(unsigned char* romData, unsigned int length)
{
	for (unsigned int i = 0; i < length; i++)
	{
		beakRom[i] = romData[i];
	}
}

void Rom::readRomHeader()
{

	for (int i = 0; i < 16; i++)
	{
		title += (char)beakRom[0x134 + i];
	}

	//ASCII title should be upper case and 16 bytes for GB roms.
	//Very early GBC roms should be 15, but all GBC roms after should be 11, with the extra bytes being
	//repurposed for manufacture code (0x13F-0x142) and GBC flag (0x143) (GBC flag can be 80 for GBC functionality but
	//has GB backwards compatibility and C0 for GBC only)

	//0x144-0x145 Licensee Code (newer roms after SGB only?)

	//0x145 SGB flag (00 No SGB functionality, either GB or GBC only game. 03 Game supports SGB functionality)

	//0x147 Catridge type
	/*
	00 Rom only | 01 MBC1 | 02 MBC1 + Ram | 03 MBC1 + Ram + Battery | 05 MBC2 | 06 MBC2 + Battery | 08 Rom + Ram |
	09 Rom + Ram + Battery | 0B MMM01 | 0C MMM01 + Ram | 0D MMM01 + Ram + Battery | 11 MBC3 | 12 MBC3 + Ram |
	13 MBC3 + Ram + Battery | 19 MBC5 | 1A MBC5 + Ram | 1B MBC5 + Ram + Battery | 1C MBC5 + Rumble | 1D MBC5 + Rumble + Ram |
	1E MBC5 + Rumble + Ram + Battery | 20 MBC6 | 22 MBC7 + Sensor + Rumble + Ram + Battery | FC Pocket Camera |
	FD Bandai Tama5 | FE HuC3 | FF HuC1 + Ram + Battery |
	*/

	//0x148 Rom Size
	/*
	00 32kb (no rom bank) | 01 64kb (4 rom banks) | 02 128kb (16 rom banks) | 03 256kb (32 rom banks) |
	04 512kb (64 rom banks) | 05 1mb (64 rom banks) | 06  2mb (128 rom banks) | 07 4mb (256 rom banks) |
	08 8mb (512 rom banks) | 52 1.1mb (72 rom banks) | 53 1.2mb (80 rom banks) | 54 1.5mb
	*/

    unsigned char cartridgeType = beakRom[0x147];
    unsigned char romSize = beakRom[0x148];
	hasGBCFunctionality = beakRom[0x143] != 0;
	hasSGBFunctionality = beakRom[0x146] == 3;
	mapperSetting = cartridgeType;
	if (mapperSetting == 0)
	{
		//None
        emit fullRomWrite();
	}
	else if (mapperSetting <= 3)
	{
		//MBC1
        emit rom0Write();
        emit setMBC1RomBank(1);
	}
	else if (mapperSetting <= 6)
	{
		//MBC2
        emit rom0Write();
        emit setMBC2RomBank(1);
	}
	else if (mapperSetting <= 9)
	{
		//8: Rom+Ram
		//9: Rom+Ram+Battery

        emit fullRomWrite();
	}
	else if (mapperSetting <= 0x0D)
	{
		//0B: MMM01
		//0C: MMM01+Ram
		//0D: MMM01+Ram+Battery

        emit rom0Write();
	}
	else if (mapperSetting <= 0x10)
	{
		//0F: MBC3+Timer+Battery
		//10: MBC3+Timer+Ram+Battery
		//11: MBC3
		//12: MBC3+Ram
		//13: MBC3+Ram+Battery

        emit rom0Write();
        emit setMBC3RomBank(1);
	}
	else if (mapperSetting <= 0x1E)
	{
        emit rom0Write();
        emit setMBC5RomBank(1);
	}
	else
	{
        emit fullRomWrite();
		//writeRom0ToRam();
	}



	//0x149 Ram Size
	/*
	00 No Ram In Cart | 01 2kb | 02 8kb | 03 32kb (4 banks of 8 kb) | 04 128kb (16 banks 0f 8kb) | 05 64kb (8 banks 0f 8 kb)
	*/

	//0x14A Location Value (00 Japanese, 01 Non-Japanese)

	//0x14B Old Licensee Code (If 33, uses New Licensee Code)

	//0x14C Rom Version Number (often 00)

	//0x14D Header Checksum (checksum for bytes from 0x134-0x14C) (IS CHECKED)
	//Calculated As:
	//int x = 0;
	//for(int i = 0x134; i < 0x14C; i++)
	//{
	//	x = x - readMemory(i) - 1;
	//}

	//0x14E-14F - Rom Checksum (whole rom except checksum bytes, not checked by GB)
}

unsigned char Rom::readByte(unsigned int address)
{
	return beakRom[address];
}

void Rom::operator=(const Rom & newRom)
{
	for (int i = 0; i < 0x500000; i++)
	{
		beakRom[i] = newRom.beakRom[i];
	}
	romSize = newRom.romSize;
	romByteSize = newRom.romSize;
	programRamBattery = newRom.romSize;
	usesProgramRam = newRom.usesProgramRam;
	loadSuccessful = newRom.loadSuccessful;
	bankingMode = newRom.bankingMode; //0: Rom 1: Ram
	mapperSetting = newRom.mapperSetting;
	cartridgeType = newRom.cartridgeType;
	romBankNumber = newRom.romBankNumber;
	ramBankNumber = newRom.ramBankNumber;
	romFilePath = newRom.romFilePath;
	title = newRom.title;
}

bool Rom::isGBCRom()
{
	return hasGBCFunctionality;
}

bool Rom::isSGBRom()
{
	return hasSGBFunctionality;
}

