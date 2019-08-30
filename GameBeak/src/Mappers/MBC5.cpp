#include "src/Mappers/MBC5.h"
#include "src/Mappers/Mapper.h"
#include "src/Memory.h"
#include "src/Rom.h"

MBC5::MBC5(Memory& memory, Rom& rom)
    : Mapper(memory), memory(memory), rom(rom)
{
}

void MBC5::changeMBC5RomBanks(int bankNumber)
{
	if ((bankNumber >= 0) && (bankNumber <= 0x1FF))
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

void MBC5::writeMBC5Value(short address, unsigned char value)
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
	else if (address >= 0x2000 && address <= 0x2FFF)
	{
		//Set Low 8 bits of Rom Bank Number
        unsigned char newBankNumber = ((this->romBankNumber & 0x100) | (value)); //Keeps the 9th bit of current rom bank number, joins entire value.

        if (this->romBankNumber != newBankNumber)
		{
            this->changeMBC5RomBanks(newBankNumber);
		}

	}
	else if (address >= 0x3000 && address <= 0x3FFF)
	{
		//Set the 9th bit of Rom Bank Number
		if (value > 0) //Ensure we are only setting 1 bit to newBankNumber
		{
			value = 1;
		}

        unsigned char newBankNumber = ((this->romBankNumber & 0xFF) | (value << 8));

        if (this->romBankNumber != newBankNumber)
		{
            this->changeMBC5RomBanks(newBankNumber);
		}

	}
	else if (address >= 0x4000 && address <= 0x5FFF)
	{
		//Set Ram Bank Number
        if (this->bankingMode)
		{
			//Change Ram Bank
            unsigned char newBankNumber = value & 0x0F;

            if (this->ramBankNumber != newBankNumber)
			{
                this->changeRamBanks(newBankNumber);
			}
		}

	}


}

MBC5::~MBC5()
{
}

void MBC5::resetMBC5() {
    memset(beakExternalRam, 0, sizeof(beakExternalRam));
    ramEnabled = false;
    romBankNumber = false;
    romBankNumber = 0;
    bankingMode = false;
}
