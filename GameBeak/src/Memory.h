#pragma once

#include <QString>
#include <QList>
#include <QWidget>

#ifndef MEMORYH
#define MEMORYH

class Cpu;
class Core;
class Rom;
class Memory : public QWidget
{
    Q_OBJECT

	private:
        Rom* rom;
        Cpu* cpu;
        bool* GBCMode;
        unsigned char beakRam[0xFFFF+1];
        unsigned char externalVRAMBank[0x2000]; //CGB Only
        unsigned char internalRam[0x8000]; //CGB Only
        QString title;

        //Registers
        short regAF;
        short regBC;
        short regDE;
        short regHL;

        short memoryPointer;
        short stackPointer;

        //GBC Only Registers
        unsigned char backgroundPaletteRam[0x40];
        unsigned char spritePaletteRam[0x40];
        unsigned char internalRamBank = 1; //CGB Only
        unsigned char vramBank = 0; //CGB Only

	public:
        explicit Memory(QWidget *parent = nullptr);
        explicit Memory(Core* core);
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

        QList<unsigned char> returnSaveDataFromMemory();

        void saveState();
        void loadSaveState();

        public slots:
            void writeFullRomToRam();
            void writeRom0ToRam();

       signals:
            void cpu_SetDoubleSpeedMode(bool speedSetting);
            void writeMBC1Value(unsigned short address, unsigned char value);
            void writeMBC2Value(unsigned short address, unsigned char value);
            void writeMBC3Value(unsigned short address, unsigned char value);
            void writeMBC5Value(unsigned short address, unsigned char value);
};


#endif
