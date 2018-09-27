#pragma once

#include <Windows.h>
#include <string>

#ifndef BINARYH
#define BINARYH

byte rotateLeft(byte number);
byte rotateLeft(byte number, int shiftAmount);
byte rotateRight(byte number);
byte rotateRight(byte number, int shiftAmount);
byte returnHalfNibble(byte data, int halfNibblePosition);
byte reverseBits(byte number);
std::string hexToASCII(int value);
std::string hexToASCIIU(unsigned short value);
std::string hexToASCII(byte value);

#endif