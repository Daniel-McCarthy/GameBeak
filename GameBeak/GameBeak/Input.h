#pragma once

#include <Windows.h>
#include "Main.h"
#include "Memory.h"
#include <SFML\System.hpp>
#include <fstream>

using namespace sf;

#ifndef INPUTH
#define INPUTH


//Gameboy keys:
//[Up][Left][Right][Down][A][B][Start][Select]

//Mapped to standard keyboard keys:
//[Up][Left][Right][Down][Z][X][Enter][RShift]

bool keyRight = false, keyLeft = false, keyUp = false, keyDown = false, keyStart = false, keySelect = false, keyA = false, keyB = false;

byte getKeyInput()
{
	return beakMemory.readMemory(0xFF00);
}



void readInput()
{
	byte keyInput = getKeyInput();
	bool interrupt = false;

	if (((keyInput & 0x10) >> 4) == 1)
	{
		beakWindow.window.setKeyRepeatEnabled(false);

		if (Keyboard::isKeyPressed(Keyboard::Z)) { //Z //A
			keyInput &= 0xFE;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x01;
		}

		if (Keyboard::isKeyPressed(Keyboard::X)) { //X //B
			keyInput &= 0xFD;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x02;
		}

		if (Keyboard::isKeyPressed(Keyboard::RShift)) { //Control //Select
			keyInput &= 0xFB;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x04;
		}

		if (Keyboard::isKeyPressed(Keyboard::Return)) { //Enter //Start
			keyInput &= 0xF7;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x08;
		}

	}
	else if (((keyInput & 0x20) >> 5) == 1)//(keyInput == 0x20)
	{
		beakWindow.window.setKeyRepeatEnabled(true);

		if (Keyboard::isKeyPressed(Keyboard::Right)) { //Right arrow //Right
			keyRight = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) { //Left arrow //Left
			keyLeft = true;
		}

		if (!(right && keyLeft)) //Detect if both inputs are NOT enabled at once
		{
			if (keyRight)
			{
				keyInput &= 0xFE;
				interrupt = true;
			}
			else
			{
				keyInput |= 0x01;
			}

			if (keyLeft)
			{
				keyInput &= 0xFD;
				interrupt = true;
			}
			else
			{
				keyInput |= 0x02;
			}
		}
		else //To solve issue of multiple key input on one axis we will ignore input when both left and right are pressed at the same time.
		{
			keyInput |= 0x01;
			keyInput |= 0x02;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) { //Up arrow //Up
			keyUp = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) { //Down arrow //Down
			keyDown = true;
		}

		if (!(keyUp && keyDown)) //Detect if both inputs are NOT enabled at once
		{
			if (keyUp)
			{
				keyInput &= 0xFB;
				interrupt = true;
			}
			else
			{
				keyInput |= 0x04;
			}

			if (keyDown)
			{
				keyInput &= 0xF7;
				interrupt = true;
			}
			else
			{
				keyInput |= 0x08;
			}
		}
		else //To solve issue of multiple key input on one axis we will ignore input when both left and right are pressed at the same time.
		{
			keyInput |= 0x04;
			keyInput |= 0x08;
		}

	}
	else
	{
		keyInput |= 0x01;
		keyInput |= 0x02;
		keyInput |= 0x04;
		keyInput |= 0x08;
	}


	//Bit 7 and 6 are always 1
	keyInput |= 0x80; //Bit 7
	keyInput |= 0x40; //Bit 6

	if (interrupt)
	{
		beakMemory.writeMemory(0xFF0F, (byte)(beakMemory.readMemory(0xFF0F) | 0x10));
	}

	beakMemory.writeMemory(0xFF00, keyInput);
}


#endif // !INPUTH
