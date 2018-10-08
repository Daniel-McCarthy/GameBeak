#pragma once
class Mapper
{
public:
    unsigned char beakExternalRam[0x1E000];
    bool ramEnabled = false;
    short romBankNumber = 0;
    unsigned char ramBankNumber = 0;
    bool bankingMode = false; //0: Rom 1: Ram

    void changeRamBanks(int bankNumber);

    Mapper();
    ~Mapper();
};

