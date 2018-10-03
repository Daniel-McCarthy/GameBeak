#pragma once

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
	void setKeyInput(int keyCode, bool enabled);
};

#endif // !INPUTH
