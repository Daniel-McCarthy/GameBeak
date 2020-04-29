#include "src/Mappers/Mapper.h"
#include "src/Memory.h"

Mapper::Mapper(Memory& memory)
    : QObject(), memory(memory)
{
}

void Mapper::changeRamBanks(int bankNumber)
{
    short externalAddress = ramBankNumber * 0x2000;

    //Save Old Beak Ram Data to External Ram Array
    for (int i = 0; i < 0x2000; i++)
    {
        beakExternalRam[externalAddress + i] = memory.readMemory(0xA000 + i);
    }

    ramBankNumber = bankNumber;
    externalAddress = ramBankNumber * 0x2000;

    //Load New External Ram data to Beak Ram
    for (int i = 0; i < 0x2000; i++)
    {
        memory.directMemoryWrite(0xA000 + i, beakExternalRam[externalAddress + i]);
    }

}

Mapper::~Mapper()
{
}
