#include "src/Mappers/MBC1.h"
#include "src/Mappers/Mapper.h"
#include "src/Memory.h"
#include "src/Rom.h"

MBC1::MBC1(Memory& memory, Rom& rom)
    : Mapper(memory), memory(memory), rom(rom)
{
}

MBC1::~MBC1()
{
}

void MBC1::changeMBC1RomBanks(int bankNumber)
{
    if (bankNumber == 0)
    {
        bankNumber++;
    }

    if ((bankNumber >= 0) && (bankNumber <= 0x1F))
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

void MBC1::writeMBC1Value(short address, unsigned char value)
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
        unsigned char newBankNumber = ((this->romBankNumber & 0xE0) | (value & 0x1F));

        if (this->romBankNumber != newBankNumber)
        {
            changeMBC1RomBanks(newBankNumber);
        }

    }
    else if (address >= 0x4000 && address <= 0x5FFF)
    {
        //Set Ram Bank Number /OR/ Set Rom Bank Number 2 bits
        if (!this->bankingMode)
        {
            //Change Rom Bank
            unsigned char newBankNumber = ((this->romBankNumber & 0x1F) | ((value & 0x03) << 5));
            if (this->romBankNumber != newBankNumber)
            {
                changeMBC1RomBanks(newBankNumber);
            }
        }
        else
        {
            //Change Ram Bank
            unsigned char newBankNumber = value & 0x03;

            if (this->ramBankNumber != newBankNumber)
            {
                this->changeRamBanks(newBankNumber);
            }
        }

    }
    else if (address >= 0x6000 && address <= 0x7FFF)
    {
        //Rom Banking / Ram Banking Mode
        if (value & 0x01)
        {
            this->bankingMode = true;
        }
        else
        {
            this->bankingMode = false;
        }
    }

}

void MBC1::resetMBC1() {
    memset(beakExternalRam, 0, sizeof(beakExternalRam));
    ramEnabled = false;
    romBankNumber = false;
    romBankNumber = 0;
    bankingMode = false;
}
