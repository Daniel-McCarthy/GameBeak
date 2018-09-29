#include <Windows.h>
#include <string>
using namespace std;
#include <QString>
#include <QWidget>

#ifndef ROMH
#define ROMH


#pragma once
class Memory;
class Rom : public QWidget
{
    Q_OBJECT

private:
    unsigned char romSize = 0;
    unsigned char romByteSize = 0;
	bool programRamBattery = false;
	bool usesProgramRam = false;
	bool hasGBCFunctionality = false;
	bool hasSGBFunctionality = false;

public:
    unsigned char beakRom[0x500000];
	bool loadSuccessful = false;
	bool bankingMode = false; //0: Rom 1: Ram
    unsigned char mapperSetting = 0;
    unsigned char cartridgeType = 0;
	unsigned short romBankNumber = 0;
	unsigned short ramBankNumber = 0;

    QString romFilePath = "";
    QString title = "";
    Rom(QWidget *parent = nullptr);
    Rom(unsigned char* romData, unsigned int length);
	~Rom();
	void readRomHeader();
	unsigned char readByte(unsigned int address);
	bool isGBCRom();
	bool isSGBRom();

	void operator=(const Rom & newRom);

};
#endif
