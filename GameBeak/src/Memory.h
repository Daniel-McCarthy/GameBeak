#pragma once
#include <Windows.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

#include "Binary.h"

using namespace std;

#ifndef MEMORYH
#define MEMORYH

class Rom;
class Memory
class Memory : public QWidget
{
    Q_OBJECT

	private:
	byte beakRam[0xFFFF+1];
	byte externalVRAMBank[0x2000]; //CGB Only
	byte internalRam[0x8000]; //CGB Only
	string title;

	//GBC Only Registers
	byte backgroundPaletteRam[0x40];
	byte spritePaletteRam[0x40];
	byte internalRamBank = 1; //CGB Only
	byte vramBank = 0; //CGB Only

	public:
	void writeRom0ToRam();
	void writeFullRomToRam();


	byte readSpritePaletteRam(byte address);
	byte readBackgroundPaletteRam(byte address);
	byte readVRAMBankRam(unsigned short address, byte bank);

	uint8_t readMemory(unsigned short address);
	vector<uint8_t> readMemory(int address, int bytes);

	//DMA Transfer
	void transferDMA(byte address);
	void directMemoryWrite(unsigned short address, uint8_t value);

	void writeMemory(unsigned short address, uint8_t value);
	void writeMemory(unsigned short address, short shortVal);

	void swapVRAMBank(byte newBank);
	void swapInternalRamBank(byte newBank);

	void toggleZFlag();

	void setZFlag(bool setting);

	bool getZFlag();

	void toggleNFlag();

	void setNFlag(bool setting);

	bool getNFlag();

	void toggleHFlag();

	void setHFlag(bool setting);

	bool getHFlag();

	void toggleCFlag();

	void setCFlag(bool setting);

	bool getCFlag();

	byte getA();

	byte getF();

	short getAF();

	byte getB();

	byte getC();

	short getBC();

	byte getD();

	byte getE();

	short getDE();

	byte getH();

	byte getL();

	short getHL();

	void setA(byte newA);

	void setF(byte newF);
         explicit Memory(QWidget *parent = nullptr);
        ~Memory();

	void setAF(short newAF);

	void setB(byte newB);

	void setC(byte newC);

	void setBC(short newBC);

	void setD(byte newD);

	void setE(byte newE);

	void setDE(short newDE);

	void setH(byte newH);

	void setL(byte newL);

	void setHL(short newHL);

	byte getLCDControl();

	bool getLCDEnabled();

	byte getLCDLY();

	void setLCDLY(byte newLY);

	void setStackPointer(short nn);

	void clearRegistersFlagsAndMemory();

	void clearRegistersAndFlags();

	void initializeGameBoyValues();
	void initializeGameBoyColorValues();

	bool loadRom(string path);
	bool loadRom(string path, bool findAndLoadSaveFile);
	bool loadRom(byte* rom, int romSize);
	bool loadRom(byte* rom, int romSize, byte* save, int saveSize);

	bool loadSaveFile(string filepath);

	/*
	Load Save File From Array
	*/
	bool loadSaveFile(byte* saveFile, int saveSize);

	vector<uint8_t> returnSaveDataFromMemory();

	
	void saveState();
	
	
	void loadSaveState();
	


};


#endif