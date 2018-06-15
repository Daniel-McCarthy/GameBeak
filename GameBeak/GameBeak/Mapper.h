#include <Windows.h>
#include <string>
using namespace std;

#pragma once
class Mapper
{
public:
	byte beakExternalRam[0x1E000];
	bool ramEnabled = false;
	short romBankNumber = 0;
	byte ramBankNumber = 0;
	bool bankingMode = false; //0: Rom 1: Ram

	void changeRamBanks(int bankNumber);

	Mapper();
	~Mapper();
};

