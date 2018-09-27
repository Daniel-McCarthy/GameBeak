#include <Windows.h>
#include <string>
using namespace std;

#pragma once
class MBC2
{
public:
	void changeMBC2RomBanks(int bankNumber);
	void writeMBC2Value(short address, byte value);
	MBC2();
	~MBC2();
};

