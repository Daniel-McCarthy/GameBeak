#pragma once
#include <Windows.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

#include "Main.h"
//#include "Input.h"

using namespace std;

#ifndef MEMORYH
#define MEMORYH

class Memory
{
	private:
	byte beakRam[0xFFFF+1];
	byte beakExternalRam[0x1E000];
	byte beakRom[0x500000]; //64kb for rom
	string title;
	bool ramEnabled = false;
	byte romBankNumber = 0;
	byte ramBankNumber = 0;
	bool bankingMode = false; //0: Rom 1: Ram

	public:

	Memory() {}
	~Memory() {}

	int memoryControllerMode = 0;

	void readRomHeader()
	{
		//if(checkNintendoLogoInRom()) {

		for (int i = 0; i < 16; i++)
		{
			title += (char)beakRom[0x134 + i];
		}

		//beakWindow.window->setTitle("GameBeak -" + title);

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

		byte cartridgeType = beakRom[0x147];
		byte romSize = beakRom[0x148];
		memoryControllerMode = cartridgeType;//romSize;
		if (memoryControllerMode == 0)
		{
			//None
			writeFullRomToRam();
		}
		else if (memoryControllerMode <= 3) //else if (memoryControllerMode == 1)
		{
			//MBC1
			writeRom0ToRam();
			changeMBC1RomBanks(1);
		}
		else if (memoryControllerMode <= 6)
		{
			//MBC2
			writeRom0ToRam();
			changeMBC2RomBanks(1);
		}
		else
		{
			writeFullRomToRam(); //TODO: Change this back when you have MBC Rom banking properly implemented. This will load more of the file until it can be loaded properly
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

	bool loadRom(string path)
	{
		ifstream inputFile(path, ios::binary | ios::ate);

		if (inputFile.is_open())
		{
			int fileLength = (int)inputFile.tellg();
			inputFile.seekg(0, ios::beg);
			vector<char> rom(fileLength);
			inputFile.read(rom.data(), fileLength);

			if (rom.size() <= 0x100000)
			{
				int address = 0;// 0x100;//? //0x200;
				for (int i = 0x0; i < (int)rom.size(); i++)
				{
					//writeMemory(address + i, (uint8_t)rom.at(i));
					beakRom[address + i] = (uint8_t)rom.at(i);
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

		return true;
	}

	void writeRom0ToRam()
	{
		for (int i = 0; i < 0x3FFF; i++)
		{
			beakRam[i] = beakRom[i];
		}
	}

	void writeFullRomToRam()
	{
		for (int i = 0; i < 0x7FFF; i++)
		{
			beakRam[i] = beakRom[i];
		}
	}

	void changeMBC1RomBanks(int bankNumber)
	{
		if (bankNumber == 0 || bankNumber == 20 || bankNumber == 40 || bankNumber == 60)
		{
			bankNumber++;
		}

		if ((bankNumber >= 0) && (bankNumber <= 0x7F))
		{

			int bankAddress = 0x4000 * bankNumber;

			int fixedBankAddress = 0x4000;
			for (int i = 0; i < 0x4000; i++)
			{
				beakRam[fixedBankAddress + i] = beakRom[bankAddress + i];
			}

			romBankNumber = bankNumber;
		}
	}

	void changeMBC2RomBanks(int bankNumber)
	{
		if (bankNumber == 0)
		{
			bankNumber++;
		}

		if ((bankNumber >= 0) && (bankNumber <= 0x0F))
		{

			int bankAddress = 0x4000 * bankNumber;

			int fixedBankAddress = 0x4000;
			for (int i = 0; i < 0x4000; i++)
			{
				beakRam[fixedBankAddress + i] = beakRom[bankAddress + i];
			}

			romBankNumber = bankNumber;
		}
	}

	void changeRamBanks(int bankNumber)
	{
		short externalAddress = ramBankNumber * 0x2000;

		//Save Old Beak Ram Data to External Ram Array
		for (int i = 0; i < 0x2000; i++)
		{
			beakExternalRam[externalAddress + i] = beakRam[0xA000 + i];
		}

		ramBankNumber = bankNumber;
		externalAddress = ramBankNumber * 0x2000;

		//Load New External Ram data to Beak Ram
		for (int i = 0; i < 0x2000; i++)
		{
			beakRam[0xA000 + i] = beakExternalRam[externalAddress + i];
		}
		
	}

	void writeMBC1Value(short address, byte value)
	{
		if (address >= 0x0000 && address <= 0x1FFF)
		{
			//Ram Enable/Disable
			if ((value & 0x0F) == 0x0A)
			{
				//Enable Ram
				ramEnabled = true;
			}
			else
			{
				//Disable Ram
				ramEnabled = false;
			}
		}
		else if (address >= 0x2000 && address <= 0x3FFF)
		{
			//Set Rom Bank Number 5 bits
			byte newBankNumber = ((romBankNumber & 0xE0) | (value & 0x1F));

			if (romBankNumber != newBankNumber)
			{
				changeMBC1RomBanks(newBankNumber);
			}

		}
		else if (address >= 0x4000 && address <= 0x5FFF)
		{
			//Set Ram Bank Number /OR/ Set Rom Bank Number 2 bits
			if (!bankingMode)
			{
				//Change Rom Bank
				byte newBankNumber = ((romBankNumber & 0x1F) | ((value & 0x03) << 5));
				if (romBankNumber != newBankNumber)
				{
					changeMBC1RomBanks(newBankNumber);
				}
			}
			else
			{
				//Change Ram Bank
				byte newBankNumber = value & 0x03;

				if (ramBankNumber != newBankNumber)
				{
					changeRamBanks(newBankNumber);
				}
			}

		}
		else if (address >= 0x6000 && address <= 0x7FFF)
		{
			//Rom Banking / Ram Banking Mode
			if (value & 0x01)
			{
				bankingMode = true;
			}
			else
			{
				bankingMode = false;
			}
		}

	}

	void writeMBC2Value(short address, byte value)
	{
		if (address >= 0x0000 && address <= 0x1FFF)
		{
			//Ram Enable/Disable
			if ((value & 0x0F) == 0x0A)
			{
				//Enable Ram
				ramEnabled = true;
			}
			else
			{
				//Disable Ram
				ramEnabled = false;
			}
		}
		else if (address >= 0x2000 && address <= 0x3FFF)
		{
			//Set Rom Bank Number 5 bits
			byte newBankNumber = (value & 0x0F);

			if (romBankNumber != newBankNumber)
			{
				changeMBC1RomBanks(newBankNumber);
			}

		}
		else if (address >= 0xA000 && address <= 0xA1FF)
		{
			//External Ram 512x4bits
		}

	}

	void loadDecompressedNintendoLogoToMemory()
	{
		vector<byte> logo = {
			//0xC3, 0x53, 0x65, 0xC3, 0xD6, 0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0xF0, 0x00, 0xF0, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0xF3, 0x00, 0xF3, 0x00,
			0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00,
			0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF3, 0x00, 0xF3, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCF, 0x00, 0xCF, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x3F, 0x00, 0x3F, 0x00, 0x0F, 0x00, 0x0F, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0x0F, 0x00, 0x0F, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0xF0, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF3, 0x00, 0xF3, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0xC0, 0x00,
			0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0xFF, 0x00, 0xFF, 0x00,
			0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC3, 0x00, 0xC3, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0xFC, 0x00,
			0xF3, 0x00, 0xF3, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00,
			0x3C, 0x00, 0x3C, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0x3C, 0x00, 0x3C, 0x00,
			0xF3, 0x00, 0xF3, 0x00, 0xF3, 0x00, 0xF3, 0x00, 0xF3, 0x00, 0xF3, 0x00, 0xF3, 0x00, 0xF3, 0x00,
			0xF3, 0x00, 0xF3, 0x00, 0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00,
			0xCF, 0x0C, 0xCF, 0x00, 0xCF, 0x00, 0xCF, 0x00, 0xCF, 0x00, 0xCF, 0x00, 0xCF, 0x00, 0xCF, 0x00,
			0x3C, 0x00, 0x3C, 0x00, 0x3F, 0x00, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x0F, 0x00, 0x0F, 0x00,
			0x3C, 0x00, 0x3C, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0xFC, 0x00,
			0xFC, 0x00, 0xFC, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00,
			0xF3, 0x00, 0xF3, 0x00, 0xF3, 0x00, 0xF3, 0x00, 0xF3, 0x00, 0xF3, 0x00, 0xF0, 0x00, 0xF0, 0x00,
			0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00, 0xFF, 0x00, 0xFF, 0x00,
			0xCF, 0x00, 0xCF, 0x00, 0xCF, 0x00, 0xCF, 0x00, 0xCF, 0x00, 0xCF, 0x00, 0xC3, 0x00, 0xC3, 0x00,
			0x0F, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0xFC, 0x00, 0xFC, 0x00,
			0x3C, 0x00, 0x42, 0x00, 0xB9, 0x00, 0xA5, 0x00, 0xB9, 0x00, 0xA5, 0x00, 0x42, 0x00, 0x3C, 0x00
		};
		
		for (int i = 0; i < (int)logo.size(); i++)
		{
			//writeMemory(0x7FF0 + i, logo[i]);
			writeMemory(0x8000 + i, logo[i]);
		}

		vector<byte> logoTileMap =
		{
			0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
			0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		};

		for (int i = 0; i < (int)logoTileMap.size(); i++)
		{
			writeMemory(0x9800 + i, logoTileMap[i]);
		}

	}

	bool checkNintendoLogoInRom()
	{
		vector<byte> logo = { 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C,
			0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9,
			0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E };

		for (int i = 0; i < (int)logo.size(); i++)
		{
			if (logo[i] != readMemory(0x105 + i))
			{
				return false;
			}
		}

		return true;
	}

	void loadGBBootStrapIntoMemory()
	{
		vector<byte> boot = { 
			0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E, 0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
			0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B, 0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
			0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20, 0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
			0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2, 0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
			0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xE2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20, 0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
			0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
			0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C,
			0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20, 0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50
		};

		for (int i = 0; i < (int)boot.size(); i++)
		{
			beakRam[i] = boot[i];
		}
	}

	uint8_t readMemory(unsigned short address)
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
		else
		{
			return beakRam[address];
		}
	}

	vector<uint8_t> readMemory(int address, int bytes)
	{
		vector<uint8_t> returnMemory;

		for (int i = 0; i < bytes; i++)
		{
			returnMemory.push_back(beakRam[address + i]);
		}

		return returnMemory;
	}

	//DMA Transfer
	void transferDMA(byte address)
	{
		int baseAddress = address << 8;//*= 100;

		for (int i = 0; i < 160; i++)
		{
			writeMemory(0xFE00 + i, readMemory(baseAddress + i));
		}
	}

	void directMemoryWrite(unsigned short address, uint8_t byte)
	{
		/*
			Write to Ram without ordinary restrictions. Only to be used by hardware emulating functions and not game instructions.
		*/

		beakRam[address] = byte;

	}

	bool writeMemory(unsigned short address, uint8_t byte)
	{
		//TODO: Rethink error checking for addresses, 4096 is silly restriction, can't access whole ram map
		/*
		if (writeBreakpoint && memoryPointer == writeBreakpointAddress)
		{
			paused = true;
		}
		*/

		if (memoryControllerMode > 0 && address <= 0x7FFF)
		{
			if (memoryControllerMode <= 3)//if (memoryControllerMode == 1)
			{
				writeMBC1Value(address, byte);
			}
			else if(memoryControllerMode <= 6)
			{
				writeMBC2Value(address, byte);
			}
			//TODO: Add more MBC controllers

		}
		else
		{
			//if (address >= 0 && address <= 0xFFFF)
			if (address >= 0x8000 && address <= 0xFFFF)
			{
				if (address == (unsigned short)0xFF46)
				{
					transferDMA(byte);
				}
				if (address == (unsigned short)0xFF41)
				{
					beakRam[address] = ((beakRam[address] & 0x87) | (byte & 0x78) | 0x80); //Bit 7 is always 1, Bit 0, 1, and 2 are read Only
					//&0x87 clears bits 3, 4, 5, 6 from Stat. &0xF8 clears all but bit bit 0, 1, 2, and 7 from value being written.
				}
				else
				{

					if (address >= 0xC000 && address <= 0xDDFF)
					{
						//ECHO. Anything written to here also gets written to CXXXX
						//writeMemory(address + 0x2000, shortVal);
						beakRam[address + 0x2000] = byte;
					}
					else if (address >= 0xE000 && address <= 0xFDFF)
					{
						beakRam[address - 0x2000] = byte;
					}

					unsigned int test = (unsigned int)address;

					beakRam[address] = byte;

					if (beakRam[address] == byte)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				return false;
			}
		}
	}
	
	bool writeMemory(unsigned short address, short shortVal)
	{

		if (address >= 0x0 && address <= 0xFFFF)
		{

			if (address >= 0xC000 && address <= 0xDDFF)
			{
				//ECHO. Anything written to here also gets written to EXXXX
				//writeMemory(address + 0x2000, shortVal);
				beakRam[address + 0x2000 + 1] = (shortVal & 0xFF00) >> 8;
				beakRam[address + 0x2000] = (shortVal & 0x00FF);
			}
			else if (address >= 0xE000 && address <= 0xFDFF)
			{
				beakRam[address - 0x2000 + 1] = (shortVal & 0xFF00) >> 8;
				beakRam[address - 0x2000] = (shortVal & 0x00FF);
			}

			beakRam[address + 1] = (shortVal & 0xFF00) >> 8;
			beakRam[address] = (shortVal & 0x00FF);

			if (((beakRam[address+1] << 8) | beakRam[address]) == shortVal)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	void toggleZFlag()
	{
		byte flag = getF();
		flag ^= 0x80; //Toggles left most bit
		setF(flag);
	}

	void setZFlag(bool setting)
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

	bool getZFlag()
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

	void toggleNFlag()
	{
		byte flag = getF();
		flag ^= 0x40; //Toggles second to left most bit
		setF(flag);
	}

	void setNFlag(bool setting)
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

	bool getNFlag()
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

	void toggleHFlag()
	{
		byte flag = getF();
		flag ^= 0x20; //Toggles third to left most bit
		setF(flag);
	}

	void setHFlag(bool setting)
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

	bool getHFlag()
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

	void toggleCFlag()
	{
		byte flag = getF();
		flag ^= 0x10; //Toggles fourth to left most bit
		setF(flag);
	}

	void setCFlag(bool setting)
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

	bool getCFlag()
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

	byte getA()
	{
		return (regAF & 0xFF00) >> 8;
	}

	byte getF()
	{
		return (regAF & 0x00FF);
	}

	short getAF()
	{
		return regAF;
	}

	byte getB()
	{
		return (regBC & 0xFF00) >> 8;
	}

	byte getC()
	{
		return (regBC & 0x00FF);
	}

	short getBC()
	{
		return regBC;
	}

	byte getD()
	{
		return (regDE & 0xFF00) >> 8;
	}

	byte getE()
	{
		return (regDE & 0x00FF);
	}

	short getDE()
	{
		return regDE;
	}

	byte getH()
	{
		return (regHL & 0xFF00) >> 8;
	}

	byte getL()
	{
		return (regHL & 0x00FF);
	}

	short getHL()
	{
		return regHL;
	}

	void setA(byte newA)
	{
		regAF = regAF & 0x00FF;
		regAF |= newA << 8;
	}

	void setF(byte newF)
	{
		regAF = regAF & 0xFF00;
		regAF |= newF;
	}

	void setAF(short newAF)
	{
		regAF = newAF & 0xFFF0;
	}

	void setB(byte newB)
	{
		regBC = regBC & 0x00FF;
		regBC |= newB << 8;
	}

	void setC(byte newC)
	{
		regBC = regBC & 0xFF00;
		regBC |= newC;
	}

	void setBC(short newBC)
	{
		regBC = newBC;
	}

	void setD(byte newD)
	{
		regDE = regDE & 0x00FF;
		regDE |= newD << 8;
	}

	void setE(byte newE)
	{
		regDE = regDE & 0xFF00;
		regDE |= newE;
	}

	void setDE(short newDE)
	{
		regDE = newDE;
	}

	void setH(byte newH)
	{
		regHL = regHL & 0x00FF;
		regHL |= newH << 8;
	}

	void setL(byte newL)
	{
		regHL = regHL & 0xFF00;
		regHL |= newL;
	}

	void setHL(short newHL)
	{
		regHL = newHL;
	}

	byte getLCDControl()
	{
		return readMemory(0xFF40);
	}

	bool getLCDEnabled()
	{
		return (((getLCDControl() & 0x80) >> 7) > 0); //Bit 7
	}

	byte getLCDLY()
	{
		return readMemory((short)0xFF44);
	}

	void setLCDLY(byte newLY)
	{
		writeMemory((short)0xFF44, newLY);
	}

	void setStackPointer(short nn)
	{
		stackPointer = nn;
	}

	void clearRegistersFlagsAndMemory()
	{
		setAF(0x0000);
		setBC(0x0000);
		setDE(0x0000);
		setHL(0x0000);
		setStackPointer((short)0x0000);
		memset(beakRam, 0, 0xFFFF);
	}

	void clearRegistersAndFlags()
	{
		setAF(0x0000);
		setBC(0x0000);
		setDE(0x0000);
		setHL(0x0000);
		setStackPointer((short)0x0000);
	}

	void initializeGameBoyValues()
	{

		setAF(0x01B0);
		setBC(0x013);
		setDE(0x0D8);
		setHL(0x14D);
		setStackPointer((short)0xFFFE);

		srand(time(NULL));
		for (int i = 0xC000; i < 0xDFFF; i+= 2)
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

		for (int i = 0xFF80; i < 0xFFFE; i+= 2)
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

};

#endif