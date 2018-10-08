#pragma once
class MBC1
{
public:
    MBC1();
    ~MBC1();
    void changeMBC1RomBanks(int bankNumber);
    void writeMBC1Value(short address, unsigned char value);
};

