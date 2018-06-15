#include <Windows.h>
#include <string>
using namespace std;

#pragma once
class MBC5
{
public:
	void changeMBC5RomBanks(int bankNumber);
	void writeMBC5Value(short address, byte value);
	MBC5();
	~MBC5();
};

