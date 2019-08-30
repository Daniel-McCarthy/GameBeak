#include <QString>
#include <QObject>

#ifndef ROMH
#define ROMH


#pragma once
class Memory;
class Rom : public QObject
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
    Rom(QObject *parent = nullptr);
    Rom(unsigned char* romData, unsigned int length);
	~Rom();
	void readRomHeader();
	unsigned char readByte(unsigned int address);
	bool isGBCRom();
    bool isSGBRom();
    void resetRom();

	void operator=(const Rom & newRom);

    signals:
        void fullRomWrite();
        void rom0Write();

        void setMBC1RomBank(unsigned int bankNumber);
        void setMBC2RomBank(unsigned int bankNumber);
        void setMBC3RomBank(unsigned int bankNumber);
        void setMBC5RomBank(unsigned int bankNumber);

};
#endif
