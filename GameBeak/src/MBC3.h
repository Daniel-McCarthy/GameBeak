#pragma once
class MBC3
{
public:
    void changeMBC3RomBanks(int bankNumber);
    void writeMBC3Value(short address, unsigned char value);
    MBC3();
    ~MBC3();
};

