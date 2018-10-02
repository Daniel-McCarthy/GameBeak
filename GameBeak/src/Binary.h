#pragma once

#include <string>

#ifndef BINARYH
#define BINARYH

unsigned char rotateLeft(unsigned char number);
unsigned char rotateLeft(unsigned char number, int shiftAmount);
unsigned char rotateRight(unsigned char number);
unsigned char rotateRight(unsigned char number, int shiftAmount);
unsigned char returnHalfNibble(unsigned char data, int halfNibblePosition);
unsigned char reverseBits(unsigned char number);
std::string hexToASCII(int value);
std::string hexToASCIIU(unsigned short value);
std::string hexToASCII(unsigned char value);

#endif
