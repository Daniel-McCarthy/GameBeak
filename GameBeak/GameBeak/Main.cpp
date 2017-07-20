#include "Main.h"
#include "sharpCPU.h"
#include "GameWindow.h"
#include "DebuggerWindow.h"
#include "Input.h"
#include "Debugger.h"

using namespace std;
using namespace sf;

GameWindow beakWindow = GameWindow("GameBeak", 320, 288);
DebuggerWindow* debugWindow;

short memoryPointer = 0x100;
short stackPointer = 0;
bool run = true;
bool interruptNextCycle = false;

//Settings values
byte paletteSetting = 2; //[0: Black and White Pocket][1: Green DMG][2: GameBeak Pink]
bool soundEnabled = false;
bool tileDrawMode = false;

Memory beakMemory = Memory();
gpu beakGPU = gpu();
sharpCPU cpu = sharpCPU();
Audio beakAudio = Audio();

//Debug Values
bool debugOnLaunch = false; //Decides if Debug Window launches on open
bool paused = debugOnLaunch;
bool step = false;

//Initialize registers
bool flagZ = false;
bool flagN = false;
bool flagH = false;
bool flagC = false;
short regAF = 0;
short regBC = 0;
short regDE = 0;
short regHL = 0;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
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

	//beakMemory.clearRegistersAndFlags();
	//beakMemory.loadGBBootStrapIntoMemory();
	beakMemory.initializeGameBoyValues();
	beakMemory.loadRom("C://Users//Dan//Desktop//GB//lazerpong.gb"); //Working? Maybe a tad glitchy?
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

	//open XML palette file
	char path1[MAX_PATH];
	string path;
	GetModuleFileNameA(NULL, path1, MAX_PATH);
	path = string(path1);
	path = path.substr(0, path.find_last_of('\\') + 1);

	ifstream colorFile(path + "palettes.xml");
	if (colorFile.fail())
	{
		ofstream file(path + "palettes.xml");
		file.close();
		colorFile.open(path + "palettes.xml");
	}

	string line;

	list<int> colorValues;

	while (getline(colorFile, line))
	{
		bool test1 = (line.find("<r>") != string::npos) && (line.find("</r>") != string::npos);
		bool test2 = (line.find("<g>") != string::npos) && (line.find("</g>") != string::npos);
		bool test3 = (line.find("<b>") != string::npos) && (line.find("</b>") != string::npos);

		if (test1 || test2 || test3)
		{
			int first = line.find_first_of('>') + 1;
			int last = line.find_last_of('<');

			line = line.substr(first, last - first);

			colorValues.push_back(stoi(line));
		}
	}

	if ((colorValues.size() / 12) > 0)
	{
		int paletteOffset = 0;
		int colorOffset = 0;

		while (colorValues.size() > (3*4))
		{
			for (int i = 0; i < 4; i++)
			{
				int r = colorValues.front();
				colorValues.pop_front();
				int g = colorValues.front();
				colorValues.pop_front();
				int b = colorValues.front();
				colorValues.pop_front();

				Color color = Color(r, g, b, 255);


				beakGPU.gameBeakPalette[(paletteOffset * 4) + colorOffset] = color;

				if (colorOffset >= 3)
				{
					colorOffset = 0;
				}
				else
				{
					colorOffset++;
				}
			}

			paletteOffset++;
		}

		paletteSetting = 4;
	}

	colorFile.close();

	RenderWindow* windowPointer = beakWindow.window;

	if (debugOnLaunch)
	{
		debugWindow = new DebuggerWindow("DebugBeak", 400, 400);
	}

	int clocks = 0;
	int clocksSinceLastTimerTIMAIncrement = 0;
	int clocksSinceLastTimerDIVIncrement = 0;
	int clocksSinceLastScanLineComplete = 0;
	int clocksSinceLastScreenRefresh = 0;

	beakMemory.loadDecompressedNintendoLogoToMemory();

	bool logging = false;
	string log = "";

	if (logging)
	{
		//Create and or clear logFile
		ofstream file("logFile.txt");
		file.close();
	}

	bool breakPointEnabled = false;
	short breakPointAt = (short)0x0E1D;

	bool accessBreakpoint = false;
	short accessBreakpointAddress = 0x0000;

	bool writeBreakpoint = false;
	short writeBreakpointAddress = 0x0000;

	byte pollingSkipping = 0;

	while (run)
	{
		
		if (Keyboard::isKeyPressed(Keyboard::Key::Tilde))
		{
			if (debugWindow == NULL)
			{
				debugWindow = new DebuggerWindow("DebugBeak", 400, 400);
			}
			else
			{
				debugWindow->run = !debugWindow->run;
			}

			//Reset game for debugging
			//memoryPointer = 0x100;
			//beakMemory.initializeGameBoyValues();
			paused = true;
			step = false;

		}
		
		Event event;

		//Poll Debug Window
		if (debugWindow != NULL)
		{
			debugWindow->runLoop();
		}

		if(pollingSkipping == 250)
		{

			//Poll Main SFML Window
			while (beakWindow.window->pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					run = false;
				}
				
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Key::T)
				{
					tileDrawMode = !tileDrawMode;

					if (tileDrawMode)
					{
						paused = true;
						beakGPU.drawAllTiles();
						beakWindow.drawImageToScreen(beakWindow.debugTileScreen);

					}
					else
					{
						beakWindow.drawImageToScreen(beakWindow.screen);
						paused = false;
					}
				}
				
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Key::Escape)
				{
					run = false;
				}

			}
			
			pollingSkipping = 0;
		}
		else
		{
			pollingSkipping++;
		}

		if (breakPointEnabled)
		{
			if (memoryPointer == breakPointAt)
			{
				paused = true;
			}
		}

		if (!paused || step)
		{
				readInput();

			
			if (logging)
			{
				log += get<0>(disassembleInstruction(memoryPointer)) + '\n';

				if(log.length() > 10000)
				{
					ofstream file("logFile.txt", ios_base::out | ios_base::app);
					if (file.is_open())
					{
						file << log << endl;
					}
					file.close();

					log = "";
				}
			}
			

			
			step = false;
			clocks += cpu.tClock;
			cpu.updateTIMA(clocks, clocksSinceLastTimerTIMAIncrement, clocksSinceLastTimerDIVIncrement);
			beakWindow.updateLCD(clocks, clocksSinceLastScanLineComplete, clocksSinceLastScreenRefresh);
			cpu.mClock = 0;
			cpu.tClock = 0;

			if (soundEnabled)
			{
				beakAudio.updateSound();
			}

			if (!cpu.checkForHaltOrInterrupt())
			{
				cpu.selectOpcode(beakMemory.readMemory(memoryPointer++));
			}
			else
			{
				cpu.selectOpcode(0); //Gets stuck at a halt without this, because no cycles are occuring (no opcode is running) the vblank interrupt never occurs
			}
		}

	}



	if (logging)
	{
		ofstream file2("logFile.txt", ios_base::out | ios_base::app);
		if (file2.is_open())
		{
			file2 << log << endl;
		}
		file2.close();
	}

	delete(debugWindow);

	return 0;
}


