#include "src/Mappers/MBC2.h"
#include "src/Memory.h"
#include "src/Rom.h"

MBC2::MBC2(Memory& memory, Rom& rom)
    : Mapper(memory), memory(memory), rom(rom)
{
}

void MBC2::changeMBC2RomBanks(int bankNumber)
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
            memory.directMemoryWrite(fixedBankAddress + i, rom.readByte(bankAddress + i));
        }

        this->romBankNumber = bankNumber;
    }
}

void MBC2::writeMBC2Value(short address, unsigned char value)
{
    if (address >= 0x0000 && address <= 0x1FFF)
    {
        //Ram Enable/Disable
        if ((value & 0x0F) == 0x0A)
        {
            //Enable Ram
            this->ramEnabled = true;
        }
        else
        {
            //Disable Ram
            this->ramEnabled = false;
        }
    }
    else if (address >= 0x2000 && address <= 0x3FFF)
    {
        //Set Rom Bank Number 5 bits
        unsigned char newBankNumber = (value & 0x0F);

        if (this->romBankNumber != newBankNumber)
        {
            this->changeMBC2RomBanks(newBankNumber);
        }

    }
    /*
    Should never get called, as MBC writes only occur if it is less than 0x7FFF
    else if (address >= 0xA000 && address <= 0xA1FF)
    {
    //External Ram 512x4bits
    beakRam[(unsigned short)address] = value;
    }
    */
}

MBC2::~MBC2()
{
}

void MBC2::resetMBC2() {
    memset(beakExternalRam, 0, sizeof(beakExternalRam));
    ramEnabled = false;
    romBankNumber = false;
    romBankNumber = 0;
    bankingMode = false;
}
