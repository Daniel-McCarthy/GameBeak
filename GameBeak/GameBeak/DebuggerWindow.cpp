#include "DebuggerWindow.h"
#include "Main.h"
#include "GameWindow.h"
#include <Windows.h>
#include <tuple>
#include "Debugger.h"

using namespace std;

DebuggerWindow::DebuggerWindow(string title, int width, int height)
{
	//Set Window
	//window = new RenderWindow(VideoMode(width, height), title);
	//window = Image(VideoMode(width, height), title);
	//window = 
	//auto sfgWindow = sfg::Window::Create();

	//desktop.Add(sfgWindow);

	//window->resetGLStates();
	//window.setFramerateLimit(60);

	//Set Icon
	char path1[MAX_PATH];
	string path;
	GetModuleFileNameA(NULL, path1, MAX_PATH);
	path = string(path1);
	path = path.substr(0, path.find_last_of('\\') + 1);
	setIcon(32, 32, path + "Beak3.png");

	//Set Button
	//buttonTexture.loadFromFile(path + "Button.png");
	//buttonSprite = Sprite(buttonTexture);

	//Set Font
	//font.loadFromFile(path + "cour.ttf");
}


DebuggerWindow::~DebuggerWindow()
{
}

void DebuggerWindow::setIcon(int width, int height, string path)
{
	Image image;
	//image.loadFromFile(path);
	//window.setIcon(32, 32, image.getPixelsPtr());
}

void DebuggerWindow::runLoop()
{
	if (run)
	{

		//Event event;
		//while (window.pollEvent(event))
		{
			//if (event.type == Event::Closed)
			{
				run = false;
			}
			
			//if (event.type == Event::MouseButtonPressed)
			{
				//if (event.mouseButton.button == Mouse::Button::Left)
				{
					//int x = event.mouseButton.x;
					//int y = event.mouseButton.y;

					//Button 1 //Play/Pause
					//if ((x > 50) && (x < 50 + buttonSprite.getGlobalBounds().width)
						//&& ((y > 350) && (y < 350 + buttonSprite.getGlobalBounds().height)))
					{
						paused = !paused;
					}

					//Button 2 //Step
					//if ((x > 150) && (x < 150 + buttonSprite.getGlobalBounds().width)
						//&& ((y > 350) && (y < 350 + buttonSprite.getGlobalBounds().height)))
					{
						step = true;
					}

					//Button 3 //Reset
					//if ((x > 250) && (x < 250 + buttonSprite.getGlobalBounds().width)
						//&& ((y > 350) && (y < 350 + buttonSprite.getGlobalBounds().height)))
					{
						memoryPointer = 0x100; //0x0
						//beakMemory.clearRegistersAndFlags();
						//beakMemory.clearRegistersFlagsAndMemory();
						beakMemory.initializeGameBoyValues();
					}


					//Button 4 //Registers Window
					//if ((x > 50) && (x < 50 + buttonSprite.getGlobalBounds().width)
						//&& ((y > 300) && (y < 300 + buttonSprite.getGlobalBounds().height)))
					{
						debuggerPage = 0;
					}

					//Button 2 //Memory Window
					//if ((x > 150) && (x < 150 + buttonSprite.getGlobalBounds().width)
						//&& ((y > 300) && (y < 300 + buttonSprite.getGlobalBounds().height)))
					{
						debuggerPage = 1;
					}

					//Button 3 //Disassembler Window
					//if ((x > 250) && (x < 250 + buttonSprite.getGlobalBounds().width)
						//&& ((y > 300) && (y < 300 + buttonSprite.getGlobalBounds().height)))
					{
						debuggerPage = 2;
					}





				}
			}
		}

		//if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
		{
			run = false;
		}

		//if (window.hasFocus() && debuggerPage == 1 && Keyboard::isKeyPressed(Keyboard::Key::Up))
		{
			if (memoryPosition - 16 >= 0)
			{
				memoryPosition -= 16;
			}
		}

		//if (window.hasFocus() && debuggerPage == 1 && Keyboard::isKeyPressed(Keyboard::Key::Down))
		{
			if (memoryPosition + 16 < 0xFFFF)
			{
				memoryPosition += 16;
			}
			else
			{
				memoryPosition = 0xFFFF - 16;
			}
		}

		//if (window.hasFocus() && debuggerPage == 1 && Keyboard::isKeyPressed(Keyboard::Key::Up) && (Keyboard::isKeyPressed(Keyboard::Key::RShift) || Keyboard::isKeyPressed(Keyboard::Key::LShift)))
		{
			if (memoryPosition - 256 >= 0)
			{
				memoryPosition -= 256;
			}
			else
			{
				memoryPosition = 0;
			}
		}

		//if (window.hasFocus() && debuggerPage == 1 && Keyboard::isKeyPressed(Keyboard::Key::Down) && (Keyboard::isKeyPressed(Keyboard::Key::RShift) || Keyboard::isKeyPressed(Keyboard::Key::LShift)))
		{
			if (memoryPosition + 256 <= 0xFFFF)
			{
				memoryPosition += 256;
			}
			else
			{
				memoryPosition = 0xFFFF - 256;
			}
		}

		//window.setVisible(true);

		//window.clear();

		if (debuggerPage == 0)
		{
			displayRegisters();
		}

		if (debuggerPage == 1)
		{
			displayMemory();
		}

		if (debuggerPage == 2)
		{
			displayDisassembly();
		}

		//Setup Registers/Memory/Disassembler Buttons
		int buttonPosX = 50;
		int buttonPosY = 300;
		
		drawButton(buttonPosX, buttonPosY, .5, .5);
		printText("Registers", buttonPosX + 10, buttonPosY + 13, Color::Black);
		drawButton(buttonPosX + 100, buttonPosY, .5, .5);
		printText("Memory", buttonPosX + 120, buttonPosY + 13, Color::Black);
		drawButton(buttonPosX + 198, buttonPosY, .5, .5);
		printText("Disassembler", buttonPosX + 200, buttonPosY + 13, Color::Black);


		//Setup Play-Pause/Step/Reset Buttons
		buttonPosX = 50;
		buttonPosY = 350;

		drawButton(buttonPosX, buttonPosY, .5, .5);
		string pausePlayButtonText = (paused) ? "Play" : "Pause";
		printText(pausePlayButtonText, buttonPosX + 21, buttonPosY + 13, Color::Black);
		drawButton(buttonPosX + 100, buttonPosY, .5, .5);
		printText("Step", buttonPosX + 121, buttonPosY + 13, Color::Black);
		drawButton(buttonPosX + 200, buttonPosY, .5, .5);
		printText("Reset", buttonPosX + 221, buttonPosY + 13, Color::Black);

		//displayMemory();

		//window.display();

	}
	else
	{
		//window.setVisible(false);
	}
}

void DebuggerWindow::printText(string text)
{
	//Text textConverted(text, font, 12);
	//window.draw(textConverted);
}

void DebuggerWindow::printText(string text, int x, int y)
{
	//Text textConverted(text, font, 12);
	//textConverted.setPosition(x, y);
	//window.draw(textConverted);

}

void DebuggerWindow::printText(string text, int x, int y, Color color)
{
	//Text textConverted(text, font, 12);
	//textConverted.setFillColor(color);
	//textConverted.setPosition(x, y);
	//window.draw(textConverted);

}

void DebuggerWindow::drawButton(int x, int y)
{
	//buttonSprite.setPosition(x, y);
	//window.draw(buttonSprite);
}

void DebuggerWindow::drawButton(int x, int y, float scaleX, float scaleY)
{
	//buttonSprite.setPosition(x, y);
	//buttonSprite.setScale(scaleX, scaleY);
	//window.draw(buttonSprite);
}

void DebuggerWindow::displayRegisters()
{
	stringstream ss;
	ss << std::hex << memoryPointer;
	string memPointerHex = ss.str();
	ss.str(""); //Clears data from ss
	ss << std::hex << stackPointer;
	string stackPointerHex = ss.str();

	ss.str("");
	ss << std::hex << ((short)(beakMemory.getA()) & 0x00FF);
	string a = ss.str();

	ss.str("");
	ss << std::hex << ((short)(beakMemory.getF()) & 0x00FF);
	string f = ss.str();

	ss.str("");
	ss << std::hex << (short)beakMemory.getAF();
	string af = ss.str();

	ss.str("");
	ss << std::hex << ((short)(beakMemory.getB()) & 0x00FF);
	string b = ss.str();

	ss.str("");
	ss << std::hex << ((short)(beakMemory.getC()) & 0x00FF);
	string c = ss.str();

	ss.str("");
	ss << std::hex << (short)beakMemory.getBC();
	string bc = ss.str();

	ss.str("");
	ss << std::hex << ((short)(beakMemory.getD()) & 0x00FF);
	string d = ss.str();

	ss.str("");
	ss << std::hex << ((short)(beakMemory.getE()) & 0x00FF);
	string e = ss.str();

	ss.str("");
	ss << std::hex << (short)beakMemory.getDE();
	string de = ss.str();

	ss.str("");
	ss << std::hex << ((short)(beakMemory.getH()) & 0x00FF);
	string h = ss.str();

	ss.str("");
	ss << std::hex << ((short)(beakMemory.getL()) & 0x00FF);
	string l = ss.str();

	ss.str("");
	ss << std::hex << (short)beakMemory.getHL();
	string hl = ss.str();

	ss.str("");
	ss << std::hex << ((short)(beakMemory.readMemory(0xFF00)) & 0x00FF);
	string keyInput = ss.str();

	ss.str("");
	ss << std::hex << ((short)(beakMemory.readMemory(0xFF40)) & 0x00FF);
	string lcdControl = ss.str();

	ss.str("");
	ss << std::hex << ((short)(beakMemory.readMemory(0xFF41)) & 0x00FF);
	string lcdStatus = ss.str();

	ss.str("");
	ss << std::hex << ((short)(beakMemory.readMemory(0xFF44)) & 0x00FF);
	string lcdLY = ss.str();

	ss.str("");
	ss << std::hex << beakWindow.getGPUMode();
	string lcdMode = ss.str();

	string interruptIME = to_string(cpu.interruptsEnabled);

	ss.str("");
	ss << std::hex << ((short)(beakMemory.readMemory(0xFFFF)) & 0x00FF);
	string interruptIE = ss.str();

	ss.str("");
	ss << std::hex << ((short)(beakMemory.readMemory(0xFF0F)) & 0x00FF);
	string interruptIF = ss.str();

	ss.str("");
	ss << std::hex << ((short)(beakMemory.readMemory(0xFF05)) & 0x00FF);
	string tima = ss.str();

	ss.str("");
	ss << std::hex << ((short)(beakMemory.readMemory(0xFF42)) & 0x00FF);
	string scrollY = ss.str();

	ss.str("");
	ss << std::hex << ((short)(beakMemory.readMemory(0xFF43)) & 0x00FF);
	string scrollX = ss.str();

	ss.str("");
	ss << std::hex << (short)(stackPointer);
	string address2;
	address2 = ss.str();
	ss.str("");
	ss << std::hex << (short)((beakMemory.readMemory(stackPointer + 1) << 8) | (beakMemory.readMemory(stackPointer)));
	string value2;
	value2 = ss.str();
	string stackVal2 = address2 + ": " + value2;

	printText("Reg A: " + a +
		"\tReg F: " + f +
		"\tReg AF: " + af +
		"\nReg B: " + b +
		"\tReg C: " + c +
		"\tReg BC: " + bc +
		"\nReg D: " + d +
		"\tReg E: " + e +
		"\tReg DE: " + de +
		"\nReg H: " + h +
		"\tReg L: " + l +
		"\tReg HL: " + hl +
	"\n\nFlag Z: " + to_string(beakMemory.getZFlag()) +
	"\tFlag N: " + to_string(beakMemory.getNFlag()) +
	"\tFlag H: " + to_string(beakMemory.getHFlag()) +
	"\tFlag C: " + to_string(beakMemory.getCFlag()) +
	"\nSP: " + stackPointerHex + "\tStack Val: " + value2 + "\nPC: " + memPointerHex +
	"\n\n" + "(Keys) FF00: " + keyInput +
	"\n" + "(LCDC) FF40: " + lcdControl +
	"\n" + "(LCDStat) FF41: " + lcdStatus +
	"\n" + "(LCDLY) FF44: " + lcdLY +
	"\n" + "(LCDMode): " + lcdMode +
	"\n" + "(IME)    : " + interruptIME +
	"\n" + "(IE) FFFF: " + interruptIE +
	"\n" + "(IF) FF0F: " + interruptIF +
	"\n" + "(TIMA) FF05: " + tima +
	"\n" + "(ScrollX) FF43: " + scrollX +
	"\n" + "(ScrollY) FF42: " + scrollY);
}

void DebuggerWindow::displayMemory()
{
	string text = "       00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n       __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __\n";

	stringstream ss;

	for (int i = 0; i < 16; i++)
	{
		ss << std::hex << memoryPosition + (i * 16);
		string lineNumber = ss.str();
		while (lineNumber.length() < 4)
		{
			lineNumber = '0' + lineNumber;
		}
		text += lineNumber + " | ";
		ss.str("");

		for (int j = 0; j < 16; j++)
		{
			ss << std::hex << (int)beakMemory.readMemory(memoryPosition + j + (i * 16));
			string hex = (ss.str().length() == 1) ? '0' + ss.str() : ss.str();
			
			text += hex + ' ';
			ss.str("");
		}

		text += '\n';
	}

	printText(text);
}

void DebuggerWindow::displayDisassembly()
{
	int instructionLocation = memoryPointer;

	string text = "";

	for (int i = 0; i < 16; i++)
	{
		tuple<string, int> disassembly = disassembleInstruction(instructionLocation);
		text += get<0>(disassembly) + '\n';
		instructionLocation += get<1>(disassembly);
	}

	printText(text);
}




