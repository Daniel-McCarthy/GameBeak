#include <QObject>
#include "src/Mappers/Mapper.h"

#ifndef MBC5H
#define MBC5H

#pragma once
class Memory;
class Rom;
class MBC5 : Mapper
{
    Q_OBJECT

private:
    Memory& memory;
    Rom& rom;

public:
	void changeMBC5RomBanks(int bankNumber);
        void writeMBC5Value(short address, unsigned char value);
    MBC5(Memory& memory, Rom& rom);
	~MBC5();
    void resetMBC5();
};

#endif
