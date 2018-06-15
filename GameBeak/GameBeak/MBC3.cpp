#include "Memory.h"
#include "MBC3.h"
#include "Main.h"

void MBC3::changeMBC3RomBanks(int bankNumber)
{
	if (bankNumber == 0)
	{
		bankNumber++;
	}

	if ((bankNumber >= 0) && (bankNumber <= 0x7F))
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

void MBC3::writeMBC3Value(short address, byte value)
{
	if (address >= 0x0000 && address <= 0x1FFF)
	{
		//Ram/RTC Register  Enable/Disable
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
		//Set Rom Bank Number 7 bits
		byte newBankNumber = (value & 0x7F);

		if (mapper.romBankNumber != newBankNumber)
		{
			changeMBC3RomBanks(newBankNumber);
		}

	}
	else if (address >= 0x4000 && address <= 0x5FFF)
	{
		//Set Ram Bank Number /OR/ RTC Register Select

		if ((value >= 0) && (value <= 3))
		{
			//Change Ram Bank
			byte newBankNumber = value & 0x03;

			if (mapper.ramBankNumber != newBankNumber)
			{
				mapper.changeRamBanks(newBankNumber);
			}
		}

		if ((value >= 8) && (value <= 0x0C))
		{
			//RTC Register Select

			//Todo: Implement this
		}

	}
	else if (address >= 0x6000 && address <= 0x7FFF)
	{
		//Latch Clock Write
		//if ((previousRTCWrite == 0) && (value == 1))
		if (value == 1)
		{
			//Update RTC registers

			//LPSYSTEMTIME time;
			//GetSystemTime(time);


			/*
			08h  RTC S   Seconds   0-59 (0-3Bh)
			09h  RTC M	Minutes   0-59 (0-3Bh)
			0Ah  RTC H	Hours     0-23 (0-17h)
			0Bh  RTC DL	Lower 8 bits of Day Counter (0-FFh)
			0Ch  RTC DH	Upper 1 bit of Day Counter, Carry Bit, Halt Flag
			Bit 0	Most significant bit of Day Counter (Bit 8)
			Bit 6	Halt (0=Active, 1=Stop Timer)
			Bit 7	Day Counter Carry Bit (1=Counter Overflow)

			The Halt Flag is supposed to be set before <writing> to the RTC Registers.
			*/

		}
		//Todo: Implement this
	}

}



MBC3::MBC3()
{
}


MBC3::~MBC3()
{
}
