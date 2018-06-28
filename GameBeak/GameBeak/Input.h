#pragma once

#include <Windows.h>

using namespace std;

#ifndef INPUTH
#define INPUTH

#pragma once
class Input
{

public:
	bool keyRight = false, keyLeft = false, keyUp = false, keyDown = false, keyStart = false, keySelect = false, keyA = false, keyB = false;

	byte getKeyInput();
	bool isAnyKeyPressed();
	void readInput();
};

#endif // !INPUTH
