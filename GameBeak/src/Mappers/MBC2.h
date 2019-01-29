#include <QObject>
#include "src/Mappers/Mapper.h"

#ifndef MBC2H
#define MBC2H

#pragma once
class Memory;
class Rom;
class MBC2 : Mapper
{
    Q_OBJECT

private:
    Memory& memory;
    Rom& rom;

public:
    void changeMBC2RomBanks(int bankNumber);
    void writeMBC2Value(short address, unsigned char value);
    MBC2(Memory& memory, Rom& rom);
    ~MBC2();
};

#endif
