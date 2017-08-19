#include <stdio.h>
#include "Main.h"

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

	__declspec(dllexport) Image getScreenData()
	{
		return beakWindow.screen;
	}

	__declspec(dllexport) void setRom(byte* rom, int romSize)
	{
		beakMemory.loadRom(rom, romSize);
	}
}
