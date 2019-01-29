#include <QObject>
#include "src/Mappers/Mapper.h"

#ifndef MBC1H
#define MBC1H

#pragma once
class Memory;
class Rom;
class MBC1 : Mapper
{
    Q_OBJECT

private:
    Memory& memory;
    Rom& rom;

public:
    MBC1(Memory& memory, Rom& rom);
    virtual ~MBC1();
    void changeMBC1RomBanks(int bankNumber);
    void writeMBC1Value(short address, unsigned char value);
};

#endif
