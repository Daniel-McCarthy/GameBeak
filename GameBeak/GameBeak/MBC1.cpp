#include "Memory.h"
#include "MBC1.h"
#include "Main.h"

MBC1::MBC1()
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
			beakMemory.directMemoryWrite(fixedBankAddress + i, rom.readByte(bankAddress + i));
		}

		mapper.romBankNumber = bankNumber;
	}
}

void MBC1::writeMBC1Value(short address, byte value)
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
	else if (address >= 0x2000 && address <= 0x3FFF)
	{
		//Set Rom Bank Number 5 bits
		byte newBankNumber = ((mapper.romBankNumber & 0xE0) | (value & 0x1F));

		if (mapper.romBankNumber != newBankNumber)
		{
			changeMBC1RomBanks(newBankNumber);
		}

	}
	else if (address >= 0x4000 && address <= 0x5FFF)
	{
		//Set Ram Bank Number /OR/ Set Rom Bank Number 2 bits
		if (!mapper.bankingMode)
		{
			//Change Rom Bank
			byte newBankNumber = ((mapper.romBankNumber & 0x1F) | ((value & 0x03) << 5));
			if (mapper.romBankNumber != newBankNumber)
			{
				changeMBC1RomBanks(newBankNumber);
			}
		}
		else
		{
			//Change Ram Bank
			byte newBankNumber = value & 0x03;

			if (mapper.ramBankNumber != newBankNumber)
			{
				mapper.changeRamBanks(newBankNumber);
			}
		}

	}
	else if (address >= 0x6000 && address <= 0x7FFF)
	{
		//Rom Banking / Ram Banking Mode
		if (value & 0x01)
		{
			mapper.bankingMode = true;
		}
		else
		{
			mapper.bankingMode = false;
		}
	}

}