#pragma once
class MBC2
{
public:
    void changeMBC2RomBanks(int bankNumber);
    void writeMBC2Value(short address, unsigned char value);
    MBC2();
    ~MBC2();
};

