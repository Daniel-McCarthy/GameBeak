#include "Memory.h"
#include "MBC5.h"
#include "Main.h"


void MBC5::changeMBC5RomBanks(int bankNumber)
{
	if ((bankNumber >= 0) && (bankNumber <= 0x1FF))
	{

		int bankAddress = 0x4000 * bankNumber;

		int fixedBankAddress = 0x4000;
		for (int i = 0; i < 0x4000; i++)
		{
			beakMemory.directMemoryWrite(fixedBankAddress + i, rom.readByte(bankAddress + i));
		}

		mapper.romBankNumber = bankNumber;
	}
}

void MBC5::writeMBC5Value(short address, byte value)
{
	if (address >= 0x0000 && address <= 0x1FFF)
	{
		//Ram Enable/Disable
		if ((value & 0x0F) == 0x0A)
		{
			//Enable Ram
			mapper.ramEnabled = true;
		}
		else
		{
			//Disable Ram
			mapper.ramEnabled = false;
		}
	}
	else if (address >= 0x2000 && address <= 0x2FFF)
	{
		//Set Low 8 bits of Rom Bank Number
		byte newBankNumber = ((mapper.romBankNumber & 0x100) | (value)); //Keeps the 9th bit of current rom bank number, joins entire value.

		if (mapper.romBankNumber != newBankNumber)
		{
			mbc5.changeMBC5RomBanks(newBankNumber);
		}

	}
	else if (address >= 0x3000 && address <= 0x3FFF)
	{
		//Set the 9th bit of Rom Bank Number
		if (value > 0) //Ensure we are only setting 1 bit to newBankNumber
		{
			value = 1;
		}

		byte newBankNumber = ((mapper.romBankNumber & 0xFF) | (value << 8));

		if (mapper.romBankNumber != newBankNumber)
		{
			mbc5.changeMBC5RomBanks(newBankNumber);
		}

	}
	else if (address >= 0x4000 && address <= 0x5FFF)
	{
		//Set Ram Bank Number
		if (mapper.bankingMode)
		{
			//Change Ram Bank
			byte newBankNumber = value & 0x0F;

			if (mapper.ramBankNumber != newBankNumber)
			{
				mapper.changeRamBanks(newBankNumber);
			}
		}

	}


}


MBC5::MBC5()
{
}


MBC5::~MBC5()
{
}
