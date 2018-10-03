#include "Input.h"
#include "Core.h"

//Gameboy keys:
//[Up][Left][Right][Down][A][B][Start][Select]

//Mapped to standard keyboard keys:
//[Up][Left][Right][Down][Z][X][Enter][RShift]


unsigned char Input::getKeyInput()
{
	return beakMemory.readMemory(0xFF00);
}

bool Input::isAnyKeyPressed()
{
	return keyUp || keyDown || keyLeft || keyRight || keyStart || keySelect || keyA || keyB;
}

void Input::readInput()
{
    unsigned char keyInput = getKeyInput();
	bool interrupt = false;
	cpu.setStop(false);

	if (((keyInput & 0x10) >> 4) == 1)
	{
		beakWindow.window.setKeyRepeatEnabled(false);

		if (keyA) { //Z //A
			keyInput &= 0xFE;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x01;
		}

		if (keyB) { //X //B
			keyInput &= 0xFD;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x02;
		}

		if (keySelect) { //Control //Select
			keyInput &= 0xFB;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x04;
		}

		if (keyStart) { //Enter //Start
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

		if (!(keyRight && keyLeft)) //Detect if both inputs are NOT enabled at once
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
        beakMemory.writeMemory(0xFF0F, (unsigned char)(beakMemory.readMemory(0xFF0F) | 0x10));
	}

	beakMemory.writeMemory(0xFF00, keyInput);
}

void Input::setKeyInput(int keyCode, bool enabled)
{
	cpu.setStop(false);

	switch (keyCode)
	{
	case 0:
	{
		keyUp = enabled;
		break;
	}
	case 1:
	{
		keyDown = enabled;
		break;
	}
	case 2:
	{
		keyLeft = enabled;
		break;
	}
	case 3:
	{
		keyRight = enabled;
		break;
	}
	case 4:
	{
		keyStart = enabled;
		break;
	}
	case 5:
	{
		keySelect = enabled;
		break;
	}
	case 6:
	{
		keyA = enabled;
		break;
	}
	case 7:
	{
		keyB = enabled;
		break;
	}
	}
}

