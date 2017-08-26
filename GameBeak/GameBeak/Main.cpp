#include "Main.h"
#include "sharpCPU.h"
#include "GameWindow.h"
#include "DebuggerWindow.h"
#include "Input.h"
#include "Debugger.h"


using namespace std;

int resolutionScaling = 1;

GameWindow beakWindow("GameBeak", 320 * resolutionScaling, 288 * resolutionScaling);
//DebuggerWindow* debugWindow;

short memoryPointer = 0x100;
short stackPointer = 0;
int clocks = 4500;
bool run = true;
bool enableInterruptsNextCycle = false;
bool interruptNextCycle = false;

//Palette Values:
const int blackAndWhite = 0;
const int greenDMG = 1;
const int gamebeakPink = 2;
const int gamebeakPinkAlt = 3;
const int ultraPink = 4;
const int grapeCherry = 5;
const int mintPink = 6;
const int kigb = 7;
const int bgb = 8;
const int noCashGMB = 9;
const int playGuy = 10;
const int dreamGBC = 11;
const int heboWIN = 12;
const int fpgaBoy = 13;

//Settings values
byte paletteSetting = 0;
bool soundEnabled = false;
bool tileDrawMode = false;
bool fullMapScreenMode = false;

//Post-Processing Settings
const int NONE = 0;
const int EAGLE = 1;
const int SCALE2X = 2;
const int SCALE3X = 3;
const int SUPEREAGLE = 9;
const int SAI2X = 10;
const int SUPER2XSAI = 11;
const int XBR2X = 12;

byte filterSetting = NONE;

Memory beakMemory = Memory();
gpu beakGPU = gpu();
sharpCPU cpu = sharpCPU();
Audio beakAudio = Audio();
KeyInput beakInput = KeyInput();

//Debug Values
bool debugOnLaunch = false; //Decides if Debug Window launches on open
bool paused = debugOnLaunch;
bool step = false;

bool breakPointEnabled = false;
short breakPointAt = (short)0x144E;

bool accessBreakpoint = false;
short accessBreakpointAddress = 0x0000;

bool writeBreakpoint = false;
bool writeBreakpointValue = false;
short writeBreakpointAddress = 0xFF40;
byte breakpointValue = 0x03;

//Initialize registers
bool flagZ = false;
bool flagN = false;
bool flagH = false;
bool flagC = false;
short regAF = 0;
short regBC = 0;
short regDE = 0;
short regHL = 0;

//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
void startEmulator()
{
	//Gameboy/Gameboy Pocket:
	//8 bit CPU, 4.194 MHz clock fr
	//8 kb memory ram
	//8 kb memory vram
	//160x144 px res, 2 bit color palette, 4 shades of grey (or light to dark olive green)
	//Maximum sprite stotal 40, 10 per line
	//Sprite size 8x8 or 8x16
	//20x18 (360) tiles on screen
	//Horiz sync 9198 KHz
	//Vert sync 59.73 Hz

	//Gameboy Color:
	//8 bit CPU, 4.194 or  8.388 MHz clock fr (two modes)
	//32 kb memory ram
	//16 kb memory video ram
	//160x144 px res, 32,767 colors (15-bit), 56 simultaenously
	//Maximum sprites 40 total, 10 per line, 4 colors per sprite (one transparent)
	//Sprite size 8x8 or 8x16
	//512 tiles on screen, 360-399 visible, rest are scrolling buffer

	//Color palettes for original GB games with GB Color:
	//Button presses on gameboy logo screen:
	//Dpad:   |  None:    A:           B:
	//[Up]    | [Brown]  [Red]        [Dark brown]
	//[Down]  | [Pastel] [Orang]      [Yellow]
	//[Left]  | [Blue]   [Dark blue]  [Grayscale]
	//[Right] | [Green]  [Dark Green] [Inverted]

	//ifstream palettesXML = beakGPU.openCreatePalettesXML();
	/*
	if (palettesXML.fail())
	{
		paletteSetting = 0;
	}
	else
	{
		beakGPU.loadPalettesFromXML(beakGPU.openCreatePalettesXML());
	}
	*/
	//beakMemory.clearRegistersAndFlags();
	//beakMemory.loadGBBootStrapIntoMemory();
	beakMemory.initializeGameBoyValues();
	//beakMemory.loadRom("C://Users//Dan//Desktop//GB//lazerpong.gb"); //Working? Maybe a tad glitchy?
	//beakMemory.loadRom("C://Users//Dan//Desktop//desertboy.gb"); //None //Working
	//beakMemory.loadRom("C://Users//Dan//Desktop//cpu_instrs.gb");
	//beakMemory.loadRom("C://Users//Dan//Desktop//06.gb");
	//beakMemory.loadRom("C://Users//Dan//Desktop//GBLANDER.gb"); //None 
	//beakMemory.loadRom("C://Users//Dan//Desktop//SHIP.gb"); //None //Works perfectly?
	//beakMemory.loadRom("C://Users//Dan//Desktop//Poke97.gb"); //None //Works? Fully?
	//beakMemory.loadRom("C://Users//Dan//Desktop//TEST.gb"); //None //Displays properly, but gets stuck on first screen
	//beakMemory.loadRom("C://Users//Dan//Desktop//snake.gb"); //None //Works fully
	//beakMemory.loadRom("C://Users//Dan//Desktop//BubbleFactory.gb"); //MBC1
	//beakMemory.loadRom("C://Users//Dan//Desktop//dummy4.gb"); //None
	//beakMemory.loadRom("C://Users//Dan//Desktop//dummy5.gb"); //None

	beakMemory.readRomHeader();
	//beakMemory.clearRegistersAndFlags();
	//beakMemory.loadGBBootStrapIntoMemory();


	//int clocks = 4500;//4516;//4518;//4516;
	int clocksSinceLastTimerTIMAIncrement = 0;
	int clocksSinceLastTimerDIVIncrement = 0;
	int clocksSinceLastScanLineComplete = 0;
	int clocksSinceLastVBlank = 0;
	int clocksSinceLastScreenRefresh = 0;

	beakMemory.loadDecompressedNintendoLogoToMemory();

	while (run)
	{


		/*
		if (Keyboard::isKeyPressed(Keyboard::Key::Num0))
		{
			beakMemory.saveState();
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::Num1))
		{
			beakMemory.loadSaveState();
		}
		*/


		if (breakPointEnabled)
		{
			if (memoryPointer == breakPointAt)
			{
				paused = true;
			}
		}

		if (!paused || step)
		{
			beakInput.readInput();

			if (!cpu.checkForHaltOrInterrupt())
			{
				cpu.selectOpcode(beakMemory.readMemory(memoryPointer++));
			}
			else
			{
				cpu.selectOpcode(0); //Gets stuck at a halt without this, because no cycles are occuring (no opcode is running) the vblank interrupt never occurs
			}

			
			step = false;
			clocks += cpu.tClock;
			cpu.updateTIMA(clocks, clocksSinceLastTimerTIMAIncrement, clocksSinceLastTimerDIVIncrement);
			beakWindow.updateLCD(clocks, clocksSinceLastScanLineComplete, clocksSinceLastScreenRefresh, clocksSinceLastVBlank);
			cpu.mClock = 0;
			cpu.tClock = 0;

			/*
			if (soundEnabled)
			{
				beakAudio.updateSound();
			}
			*/

			if (checkForWriteBreakpoint(writeBreakpoint, writeBreakpointValue, breakpointValue, writeBreakpointAddress))
			{
				paused = true;
			}

		}

	}


	//return 0;
}


