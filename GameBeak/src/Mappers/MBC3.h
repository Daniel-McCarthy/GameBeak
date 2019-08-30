#include <QObject>
#include "src/Mappers/Mapper.h"

#ifndef MBC3H
#define MBC3H

#pragma once
class Memory;
class Rom;
class MBC3 : Mapper
{
    Q_OBJECT

private:
    Memory& memory;
    Rom& rom;

public:
    void changeMBC3RomBanks(int bankNumber);
    void writeMBC3Value(short address, unsigned char value);
    MBC3(Memory& memory, Rom& rom);
    void resetMBC3();
    ~MBC3();
};

#endif
