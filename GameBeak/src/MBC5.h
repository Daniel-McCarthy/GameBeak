#pragma once
class MBC5
{
public:
	void changeMBC5RomBanks(int bankNumber);
        void writeMBC5Value(short address, unsigned char value);
	MBC5();
	~MBC5();
};

