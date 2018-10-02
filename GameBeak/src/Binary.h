#pragma once

#include <QString>

#ifndef BINARYH
#define BINARYH

unsigned char rotateLeft(unsigned char number);
unsigned char rotateLeft(unsigned char number, int shiftAmount);
unsigned char rotateRight(unsigned char number);
unsigned char rotateRight(unsigned char number, int shiftAmount);
unsigned char returnHalfNibble(unsigned char data, int halfNibblePosition);
unsigned char reverseBits(unsigned char number);
QString hexToASCII(int value);
QString hexToASCIIU(unsigned short value);
QString hexToASCII(unsigned char value);

#endif
