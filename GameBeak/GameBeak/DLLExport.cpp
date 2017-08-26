#include <stdio.h>
#include "Main.h"
#include "Image.h"
#include "Debugger.h"

extern "C"
{

	__declspec(dllexport) void setPauseState(bool pauseEnabled)
	{
		paused = pauseEnabled;
	}
	__declspec(dllexport) bool getPauseState()
	{
		return paused;
	}

	__declspec(dllexport) void setRunState(bool runEnabled)
	{
		run = runEnabled;
	}
	__declspec(dllexport) bool getRunState()
	{
		return run;
	}

	__declspec(dllexport) int* getRegisters()
	{
		static int registers[] = { regAF, regBC, regDE, regHL };
		return registers;
	}

	__declspec(dllexport) short getAF()
	{
		return regAF;
	}

	__declspec(dllexport) short getBC()
	{
		return regBC;
	}

	__declspec(dllexport) short getDE()
	{
		return regDE;
	}

	__declspec(dllexport) short getHL()
	{
		return regHL;
	}

	__declspec(dllexport) int* getStackValues()
	{
		static int stackValues[] = { stackPointer, beakMemory.readMemory(stackPointer) };
		return stackValues;
	}

	__declspec(dllexport) short getPC()
	{
		return memoryPointer;
	}

	__declspec(dllexport) int* getCurrentMemoryMap()
	{

		static int romData[0x8000];
		copy(beakMemory.beakExternalRam, beakMemory.beakExternalRam + 0x7FFF, romData);
		return romData;
	}

	__declspec(dllexport) void getScreenPixelData(int* pixelData)
	{

		//beakWindow.screen.getIntArray(pixelData);
		//beakGPU.screenUpdated = false;

		while (beakGPU.screenDrawing)
		{

		}
		beakWindow.screen.getIntArray(pixelData);
	}

	__declspec(dllexport) bool getScreenUpdated()
	{
		return beakGPU.screenUpdated;
	}

	__declspec(dllexport) bool getScreenDrawing()
	{
		return beakGPU.screenDrawing;
	}

	__declspec(dllexport) int* getScreenDimensions()
	{
		static int dimensions[] = { beakWindow.screen.getSize().x, beakWindow.screen.getSize().y };
	
		return dimensions;
	}

	__declspec(dllexport) void setRom(byte* rom, int romSize)
	{
		beakMemory.loadRom(rom, romSize);
	}

	__declspec(dllexport) void setStep()
	{
		step = true;
	}

	__declspec(dllexport) byte readMemoryByte(short address)
	{
		return beakMemory.readMemory(address);
	}

	__declspec(dllexport) void initiateEmulator()
	{
		startEmulator();
	}

	__declspec(dllexport) void disassembleAddress(short& address, char* cString, int& stringLength)
	{
		tuple<string, int> disassembledTuple = disassembleInstruction(address);

		address += get<1>(disassembledTuple);

		string disassembledString = get<0>(disassembledTuple);
		stringLength = disassembledString.length();

		for (int i = 0; i < 100; i++)
		{
			if (i < disassembledString.length())
			{
				cString[i] = (char)disassembledString[i];
			}
			else
			{
				cString[i] = NULL;
			}
		}
	}

	__declspec(dllexport) void setKeyInput(int keyCode, bool enabled)
	{

		switch (keyCode)
		{
			case 0:
			{
				beakInput.keyUp = enabled;
			}
			case 1:
			{
				beakInput.keyDown = enabled;
			}
			case 2:
			{
				beakInput.keyLeft = enabled;
			}
			case 3:
			{
				beakInput.keyRight = enabled;
			}
			case 4:
			{
				beakInput.keyStart = enabled;
			}
			case 5:
			{
				beakInput.keySelect = enabled;
			}
			case 6:
			{
				beakInput.keyA = enabled;
			}
			case 7:
			{
				beakInput.keyB = enabled;
			}
		}
	}
}
