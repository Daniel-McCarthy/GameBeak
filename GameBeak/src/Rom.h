#include <Windows.h>
#include <string>
using namespace std;
#include <QWidget>

#ifndef ROMH
#define ROMH


#pragma once
class Memory;
class Rom : public QWidget
{
    Q_OBJECT

private:
	byte romSize = 0;
	byte romByteSize = 0;
	bool programRamBattery = false;
	bool usesProgramRam = false;
	bool hasGBCFunctionality = false;
	bool hasSGBFunctionality = false;

public:
	byte beakRom[0x500000];
	bool loadSuccessful = false;
	bool bankingMode = false; //0: Rom 1: Ram
	byte mapperSetting = 0;
	byte cartridgeType = 0;
	unsigned short romBankNumber = 0;
	unsigned short ramBankNumber = 0;

	string romFilePath = "";
	string title = "";
	Rom(byte* romData, unsigned int length);
    Rom(QWidget *parent = nullptr);
	~Rom();
	void readRomHeader();
	unsigned char readByte(unsigned int address);
	bool isGBCRom();
	bool isSGBRom();

	void operator=(const Rom & newRom);

};
#endif