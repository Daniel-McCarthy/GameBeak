
#include "Binary.h"

byte rotateLeft(byte number)
{
	byte lostBit = (number & 0x80) >> 7;
	number <<= 1;
	number |= lostBit;

	return number;
}

byte rotateLeft(byte number, int shiftAmount)
{
	for (int i = 0; i < shiftAmount; i++)
	{
		number = rotateLeft(number);
	}

	return number;
}

byte rotateRight(byte number)
{
	byte lostBit = (number & 0x01) << 7;
	number >>= 1;
	number |= lostBit;

	return number;
}

byte rotateRight(byte number, int shiftAmount)
{
	for (int i = 0; i < shiftAmount; i++)
	{
		number = rotateRight(number);
	}

	return number;
}

byte returnHalfNibble(byte data, int halfNibblePosition)
{
	//Returns 2 bits from byte.
	//If halfNibble Position == 0, it will index 000000XX
	//If halfNibble Position == 1, it will index 0000XX00
	//If halfNibble Position == 2, it will index 00XX0000
	//If halfNibble Position == 3, it will index XX000000

	return (data & (3 << (halfNibblePosition * 2))) >> (halfNibblePosition * 2);
}

byte reverseBits(byte number)
{
	number = ((number & 0xF0) >> 4) | ((number & 0x0F) << 4);
	number = ((number & 0xCC) >> 2) | ((number & 0x33) << 2);
	number = ((number & 0xAA) >> 1)  | ((number & 0x55) << 1);
	return number;
}

std::string hexToASCII(int value)
{
	std::string output = "";

	if (value > 0)
	{
		while (value > 0)
		{
			byte toConvert = value & 0x0F;
			value >>= 4;

			if (toConvert > 9)
			{
				//0x41 is ASCII 'a', value of character will index appropriate letter
				toConvert -= 0xA;
				output = (char)(0x61 + toConvert) + output;
			}
			else
			{
				//0x30 is ASCII '0', value of number will index appropriate character
				output = (char)(0x30 + toConvert) + output;
			}

		}

		return output;
	}
	else
	{
		return "0";
	}
}

std::string hexToASCIIU(unsigned short value)
{
	std::string output = "";

	if (value > 0)
	{
		while (value > 0)
		{
			byte toConvert = value & 0x0F;
			value >>= 4;

			if (toConvert > 9)
			{
				//0x41 is ASCII 'a', value of character will index appropriate letter
				toConvert -= 0xA;
				output = (char)(0x61 + toConvert) + output;
			}
			else
			{
				//0x30 is ASCII '0', value of number will index appropriate character
				output = (char)(0x30 + toConvert) + output;
			}

		}

		return output;
	}
	else
	{
		return "0";
	}
}

std::string hexToASCII(byte value)
{
	std::string output = "";

	if (value > 0)
	{
		while (value > 0)
		{
			byte toConvert = value & 0x0F;
			value >>= 4;

			if (toConvert > 9)
			{
				//0x41 is ASCII 'a', value of character will index appropriate letter
				toConvert -= 0xA;
				output = (char)(0x61 + toConvert) + output;
			}
			else
			{
				//0x30 is ASCII '0', value of number will index appropriate character
				output = (char)(0x30 + toConvert) + output;
			}

		}

		return output;
	}
	else
	{
		return "0";
	}
}