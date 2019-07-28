#pragma once

#include <QString>
#include <QList>
#include <QVector>
#include <QWidget>

#ifndef MEMORYH
#define MEMORYH

class Cpu;
class Core;
class Rom;
class MBC1;
class MBC2;
class MBC3;
class MBC5;
class Memory : public QObject
{
    Q_OBJECT

	private:
        Rom& rom;
        Cpu& cpu;
        bool& GBCMode;
        bool& forceDMGMode;

        MBC1& mbc1;
        MBC2& mbc2;
        MBC3& mbc3;
        MBC5& mbc5;

    public:
        QVector<unsigned char> beakRam = QVector<unsigned char>(0xFFFF + 1);
        unsigned char externalVRAMBank[0x2000] = {0}; //CGB Only
        unsigned char internalRam[0x8000] = {0}; //CGB Only
        QString title;

        //Registers
        short regAF;
        short regBC;
        short regDE;
        short regHL;

        //GBC Only Registers
        unsigned char backgroundPaletteRam[0x40] = {0};
        unsigned char spritePaletteRam[0x40] = {0};
        unsigned char internalRamBank = 1; //CGB Only
        unsigned char vramBank = 0; //CGB Only

        short memoryPointer = 0x100;
        short stackPointer = 0;

        explicit Memory(QObject* parent, Rom& rom, Cpu& cpu, bool& gbcMode, bool& forceDMGMode, MBC1& mbc1, MBC2& mbc2, MBC3& mbc3, MBC5& mbc5);
        ~Memory();

        unsigned char readSpritePaletteRam(unsigned char address);
        unsigned char readBackgroundPaletteRam(unsigned char address);
        unsigned char readVRAMBankRam(unsigned short address, unsigned char bank);

        unsigned char readMemory(unsigned short address);
        QList<unsigned char> readMemory(int address, int bytes);

        //DMA Transfer
        void transferDMA(unsigned char address);
        void directMemoryWrite(unsigned short address, unsigned char value);

        void writeMemory(unsigned short address, unsigned char value);
        void writeMemory(unsigned short address, short shortVal);

        void swapVRAMBank(unsigned char newBank);
        void swapInternalRamBank(unsigned char newBank);

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

        unsigned char getA();
        unsigned char getF();
        short getAF();

        unsigned char getB();
        unsigned char getC();
        short getBC();

        unsigned char getD();
        unsigned char getE();
        short getDE();

        unsigned char getH();
        unsigned char getL();
        short getHL();

        void setA(unsigned char newA);
        void setF(unsigned char newF);
        void setAF(short newAF);
        void setB(unsigned char newB);
        void setC(unsigned char newC);
        void setBC(short newBC);
        void setD(unsigned char newD);
        void setE(unsigned char newE);
        void setDE(short newDE);
        void setH(unsigned char newH);
        void setL(unsigned char newL);
        void setHL(short newHL);

        unsigned char getLCDControl();
        bool getLCDEnabled();

        unsigned char getLCDLY();
        void setLCDLY(unsigned char newLY);

        void setStackPointer(short nn);

        void clearRegistersFlagsAndMemory();
        void clearRegistersAndFlags();

        void initializeGameBoyValues();
        void initializeGameBoyColorValues();

        bool loadRom(QString path);
        bool loadRom(QString path, bool findAndLoadSaveFile);
        bool loadRom(QByteArray rom);
        bool loadRom(QByteArray rom, QByteArray save);

        bool loadSaveFile(QString filepath);

        /*
        Load Save File From Array
        */
        bool loadSaveFile(QByteArray saveFile);

        QByteArray returnSaveDataFromMemory();

        bool createSaveFile(bool overwrite);
        void saveState();
        void loadSaveState();

        public slots:
            void romLoaded(QString gameFilePath);
            void writeFullRomToRam();
            void writeRom0ToRam();

       signals:
            void cpu_SetDoubleSpeedMode(bool speedSetting);
            void setEmulationRun(bool setting);
};


#endif
