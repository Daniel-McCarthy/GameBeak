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
//[Up][Left][Right][Down][Z][X][Enter][Control]


byte getKeyInput()
{
	return beakMemory.readMemory(0xFF00);
}



void readInput()
{
	byte keyInput = getKeyInput();
	bool interrupt = false;

	if (((keyInput & 0x10) >> 4) == 1)//(keyInput == 0x10)
	{
		beakWindow.window->setKeyRepeatEnabled(false);

		//keyInput = 0;

		if (Keyboard::isKeyPressed(Keyboard::Z)) { //Z //A
			//keyInput &= 0xFE;
			keyInput &= 0xFE;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x01;
		}

		if (Keyboard::isKeyPressed(Keyboard::X)) { //X //B
			//keyInput &= 0xFD;
			keyInput &= 0xFD;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x02;
		}

		if (Keyboard::isKeyPressed(Keyboard::RShift)) { //Control //Select
			//keyInput &= 0xFB;
			keyInput &= 0xFB;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x04;
		}

		if (Keyboard::isKeyPressed(Keyboard::Return)) { //Enter //Start
			//keyInput &= 0xF7;
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
		beakWindow.window->setKeyRepeatEnabled(true);

		if (Keyboard::isKeyPressed(Keyboard::Right)) { //Right arrow //Right
			//keyInput &= 0xFE;
			keyInput &= 0xFE;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x01;
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) { //Left arrow //Left
			//keyInput &= 0xFD;
			keyInput &= 0xFD;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x02;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) { //Up arrow //Up
			//keyInput &= 0xFB;
			keyInput &= 0xFB;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x04;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) { //Down arrow //Down
			//keyInput &= 0xF7;
			keyInput &= 0xF7;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x08;
		}

		//TEMP TEST! REMOVE
		//keyInput = 0xEE;
		//interrupt = true;

	}
	else// if ((keyInput != 0x20) && (keyInput != 0x10))
	{
		keyInput |= 0x01;
		keyInput |= 0x02;
		keyInput |= 0x04;
		keyInput |= 0x08;
	}


	//Bit 7 and 6 are always 1
	keyInput |= 0x80; //Bit 7
	keyInput |= 0x40; //Bit 6

	//if keyInput <
	if (interrupt)
	{
		beakMemory.writeMemory(0xFF0F, (byte)(beakMemory.readMemory(0xFF0F) | 0x10));
	}

	beakMemory.writeMemory(0xFF00, keyInput);
}


#endif // !INPUTH
