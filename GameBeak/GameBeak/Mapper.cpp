#include "Memory.h"
#include "Mapper.h"
#include "Main.h"


void Mapper::changeRamBanks(int bankNumber)
{
	short externalAddress = ramBankNumber * 0x2000;

	//Save Old Beak Ram Data to External Ram Array
	for (int i = 0; i < 0x2000; i++)
	{
		beakExternalRam[externalAddress + i] = beakMemory.readMemory(0xA000 + i);
	}

	ramBankNumber = bankNumber;
	externalAddress = ramBankNumber * 0x2000;

	//Load New External Ram data to Beak Ram
	for (int i = 0; i < 0x2000; i++)
	{
		beakMemory.directMemoryWrite(0xA000 + i, beakExternalRam[externalAddress + i]);
	}

}


Mapper::Mapper()
{
}


Mapper::~Mapper()
{
}
