#include "Core.h"
#include "Cpu.h"
#include "Binary.h"
#include "Debugger.h"

Cpu::Cpu(Core* core) {
    memory = core->getMemoryPointer();
    this->core = core;
}

void Cpu::selectOpcode(unsigned char opcode)
{

    if (core->enableInterruptsNextCycle)
	{
        core->enableInterruptsNextCycle = false;
		interruptsEnabled = true;
	}

	switch (opcode & 0xF0)
	{
		case 0x00:
		{
			switch (opcode & 0x0F)
			{
				case 0:
				{
					//Nop
					opcode00();
					break;
				}
				case 1:
				{
                    opcode01((memory->readMemory(memory->memory->memoryPointer++)) | (memory->readMemory(memory->memory->memoryPointer++) << 8));
					break;
				}
				case 2:
				{
					opcode02();
					break;
				}
				case 3:
				{
					opcode03();
					break;
				}
				case 4:
				{
					opcode04();
					break;
				}
				case 5:
				{
					opcode05();
					break;
				}
				case 6:
				{
                    opcode06(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 7:
				{
					opcode07();
					break;
				}
				case 8:
				{
                    opcode08((memory->readMemory(memory->memoryPointer++)) | (memory->readMemory(memory->memoryPointer++) << 8));
					break;
				}
				case 9:
				{
					opcode09();
					break;
				}
				case 0xA:
				{
					opcode0A();
					break;
				}
				case 0xB:
				{
					opcode0B();
					break;
				}
				case 0xC:
				{
					opcode0C();
					break;
				}
				case 0xD:
				{
					opcode0D();
					break;
				}
				case 0xE:
				{
                    opcode0E(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 0xF:
				{
					opcode0F();
					break;
				}
			}
			break;
		}
		case 0x10:
		{
			switch (opcode & 0x0F)
			{
				case 0:
				{
					opcode10();
					break;
				}
				case 1:
				{
                    opcode11((memory->readMemory(memory->memoryPointer++)) | (memory->readMemory(memory->memoryPointer++) << 8));
					break;
				}
				case 2:
				{
					opcode12();
					break;
				}
				case 3:
				{
					opcode13();
					break;
				}
				case 4:
				{
					opcode14();
					break;
				}
				case 5:
				{
					opcode15();
					break;
				}
				case 6:
				{
                    opcode16(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 7:
				{
					opcode17();
					break;
				}
				case 8:
				{
                    opcode18((char)memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 9:
				{
					opcode19();
					break;
				}
				case 0xA:
				{
					opcode1A();
					break;
				}
				case 0xB:
				{
					opcode1B();
					break;
				}
				case 0xC:
				{
					opcode1C();
					break;
				}
				case 0xD:
				{
					opcode1D();
					break;
				}
				case 0xE:
				{
                    opcode1E(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 0xF:
				{
					opcode1F();
					break;
				}
			}
			break;
		}
		case 0x20:
		{
			switch (opcode & 0x0F)
			{
				case 0:
				{
                    opcode20(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 1:
				{
                    opcode21((memory->readMemory(memory->memoryPointer++)) | (memory->readMemory(memory->memoryPointer++) << 8));
					break;
				}
				case 2:
				{
					opcode22();
					break;
				}
				case 3:
				{
					opcode23();
					break;
				}
				case 4:
				{
					opcode24();
					break;
				}
				case 5:
				{
					opcode25();
					break;
				}
				case 6:
				{
                    opcode26(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 7:
				{
					opcode27();
					break;
				}
				case 8:
				{
                    opcode28(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 9:
				{
					opcode29();
					break;
				}
				case 0xA:
				{
					opcode2A();
					break;
				}
				case 0xB:
				{
					opcode2B();
					break;
				}
				case 0xC:
				{
					opcode2C();
					break;
				}
				case 0xD:
				{
					opcode2D();
					break;
				}
				case 0xE:
				{
                    opcode2E(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 0xF:
				{
					opcode2F();
					break;
				}
			}
			break;
		}
		case 0x30:
		{
			switch (opcode & 0x0F)
			{
				case 0:
				{
                    opcode30(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 1:
				{
                    opcode31((memory->readMemory(memory->memoryPointer++)) | (memory->readMemory(memory->memoryPointer++) << 8));
					break;
				}
				case 2:
				{
					opcode32();
					break;
				}
				case 3:
				{
					opcode33();
					break;
				}
				case 4:
				{
					opcode34();
					break;
				}
				case 5:
				{
					opcode35();
					break;
				}
				case 6:
				{
                    opcode36(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 7:
				{
					opcode37();
					break;
				}
				case 8:
				{
                    opcode38(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 9:
				{
					opcode39();
					break;
				}
				case 0xA:
				{
					opcode3A();
					break;
				}
				case 0xB:
				{
					opcode3B();
					break;
				}
				case 0xC:
				{
					opcode3C();
					break;
				}
				case 0xD:
				{
					opcode3D();
					break;
				}
				case 0xE:
				{
                    opcode3E(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 0xF:
				{
					opcode3F();
					break;
				}
			}
			break;
		}
		case 0x40:
		{
			switch (opcode & 0x0F)
			{
				case 0:
				{
					opcode40();
					break;
				}
				case 1:
				{
					opcode41();
					break;
				}
				case 2:
				{
					opcode42();
					break;
				}
				case 3:
				{
					opcode43();
					break;
				}
				case 4:
				{
					opcode44();
					break;
				}
				case 5:
				{
					opcode45();
					break;
				}
				case 6:
				{
					opcode46();
					break;
				}
				case 7:
				{
					opcode47();
					break;
				}
				case 8:
				{
					opcode48();
					break;
				}
				case 9:
				{
					opcode49();
					break;
				}
				case 0xA:
				{
					opcode4A();
					break;
				}
				case 0xB:
				{
					opcode4B();
					break;
				}
				case 0xC:
				{
					opcode4C();
					break;
				}
				case 0xD:
				{
					opcode4D();
					break;
				}
				case 0xE:
				{
					opcode4E();
					break;
				}
				case 0xF:
				{
					opcode4F();
					break;
				}
			}
			break;
		}
		case 0x50:
		{
			switch (opcode & 0x0F)
			{
				case 0:
				{
					opcode50();
					break;
				}
				case 1:
				{
					opcode51();
					break;
				}
				case 2:
				{
					opcode52();
					break;
				}
				case 3:
				{
					opcode53();
					break;
				}
				case 4:
				{
					opcode54();
					break;
				}
				case 5:
				{
					opcode55();
					break;
				}
				case 6:
				{
					opcode56();
					break;
				}
				case 7:
				{
					opcode57();
					break;
				}
				case 8:
				{
					opcode58();
					break;
				}
				case 9:
				{
					opcode59();
					break;
				}
				case 0xA:
				{
					opcode5A();
					break;
				}
				case 0xB:
				{
					opcode5B();
					break;
				}
				case 0xC:
				{
					opcode5C();
					break;
				}
				case 0xD:
				{
					opcode5D();
					break;
				}
				case 0xE:
				{
					opcode5E();
					break;
				}
				case 0xF:
				{
					opcode5F();
					break;
				}
			}
			break;
		}
		case 0x60:
		{
			switch (opcode & 0x0F)
			{
				case 0:
				{
					opcode60();
					break;
				}
				case 1:
				{
					opcode61();
					break;
				}
				case 2:
				{
					opcode62();
					break;
				}
				case 3:
				{
					opcode63();
					break;
				}
				case 4:
				{
					opcode64();
					break;
				}
				case 5:
				{
					opcode65();
					break;
				}
				case 6:
				{
					opcode66();
					break;
				}
				case 7:
				{
					opcode67();
					break;
				}
				case 8:
				{
					opcode68();
					break;
				}
				case 9:
				{
					opcode69();
					break;
				}
				case 0xA:
				{
					opcode6A();
					break;
				}
				case 0xB:
				{
					opcode6B();
					break;
				}
				case 0xC:
				{
					opcode6C();
					break;
				}
				case 0xD:
				{
					opcode6D();
					break;
				}
				case 0xE:
				{
					opcode6E();
					break;
				}
				case 0xF:
				{
					opcode6F();
					break;
				}
			}
			break;
		}
		case 0x70:
		{
			switch(opcode & 0x0F)
			{
				case 0:
				{
					opcode70();
					break;
				}
				case 1:
				{
					opcode71();
					break;
				}
				case 2:
				{
					opcode72();
					break;
				}
				case 3:
				{
					opcode73();
					break;
				}
				case 4:
				{
					opcode74();
					break;
				}
				case 5:
				{
					opcode75();
					break;
				}
				case 6:
				{
					//Halt
					opcode76();
					break;
				}
				case 7:
				{
					opcode77();
					break;
				}
				case 8:
				{
					opcode78();
					break;
				}
				case 9:
				{
					opcode79();
					break;
				}
				case 0xA:
				{
					opcode7A();
					break;
				}
				case 0xB:
				{
					opcode7B();
					break;
				}
				case 0xC:
				{
					opcode7C();
					break;
				}
				case 0xD:
				{
					opcode7D();
					break;
				}
				case 0xE:
				{
					opcode7E();
					break;
				}
				case 0xF:
				{
					opcode7F();
					break;
				}
			}
			break;
		}
		case 0x80:
		{
			switch (opcode & 0x0F)
			{
				case 0:
				{
					opcode80();
					break;
				}
				case 1:
				{
					opcode81();
					break;
				}
				case 2:
				{
					opcode82();
					break;
				}
				case 3:
				{
					opcode83();
					break;
				}
				case 4:
				{
					opcode84();
					break;
				}
				case 5:
				{
					opcode85();
					break;
				}
				case 6:
				{
					opcode86();
					break;
				}
				case 7:
				{
					opcode87();
					break;
				}
				case 8:
				{
					opcode88();
					break;
				}
				case 9:
				{
					opcode89();
					break;
				}
				case 0xA:
				{
					opcode8A();
					break;
				}
				case 0xB:
				{
					opcode8B();
					break;
				}
				case 0xC:
				{
					opcode8C();
					break;
				}
				case 0xD:
				{
					opcode8D();
					break;
				}
				case 0xE:
				{
					opcode8E();
					break;
				}
				case 0xF:
				{
					opcode8F();
					break;
				}
			}
			break;
		}
		case 0x90:
		{
			switch (opcode & 0x0F)
			{
				case 0:
				{
					opcode90();
					break;
				}
				case 1:
				{
					opcode91();
					break;
				}
				case 2:
				{
					opcode92();
					break;
				}
				case 3:
				{
					opcode93();
					break;
				}
				case 4:
				{
					opcode94();
					break;
				}
				case 5:
				{
					opcode95();
					break;
				}
				case 6:
				{
					opcode96();
					break;
				}
				case 7:
				{
					opcode97();
					break;
				}
				case 8:
				{
					opcode98();
					break;
				}
				case 9:
				{
					opcode99();
					break;
				}
				case 0xA:
				{
					opcode9A();
					break;
				}
				case 0xB:
				{
					opcode9B();
					break;
				}
				case 0xC:
				{
					opcode9C();
					break;
				}
				case 0xD:
				{
					opcode9D();
					break;
				}
				case 0xE:
				{
					opcode9E();
					break;
				}
				case 0xF:
				{
					opcode9F();
					break;
				}
			}
			break;
		}
		case 0xA0:
		{
			switch (opcode & 0x0F)
			{
			case 0:
			{
				opcodeA0();
				break;
			}
			case 1:
			{
				opcodeA1();
				break;
			}
			case 2:
			{
				opcodeA2();
				break;
			}
			case 3:
			{
				opcodeA3();
				break;
			}
			case 4:
			{
				opcodeA4();
				break;
			}
			case 5:
			{
				opcodeA5();
				break;
			}
			case 6:
			{
				opcodeA6();
				break;
			}
			case 7:
			{
				opcodeA7();
				break;
			}
			case 8:
			{
				opcodeA8();
				break;
			}
			case 9:
			{
				opcodeA9();
				break;
			}
			case 0xA:
			{
				opcodeAA();
				break;
			}
			case 0xB:
			{
				opcodeAB();
				break;
			}
			case 0xC:
			{
				opcodeAC();
				break;
			}
			case 0xD:
			{
				opcodeAD();
				break;
			}
			case 0xE:
			{
				opcodeAE();
				break;
			}
			case 0xF:
			{
				opcodeAF();
				break;
			}
		}
			break;
		}
		case 0xB0:
		{
			switch (opcode & 0x0F)
			{
				case 0:
				{
					opcodeB0();
					break;
				}
				case 1:
				{
					opcodeB1();
					break;
				}
				case 2:
				{
					opcodeB2();
					break;
				}
				case 3:
				{
					opcodeB3();
					break;
				}
				case 4:
				{
					opcodeB4();
					break;
				}
				case 5:
				{
					opcodeB5();
					break;
				}
				case 6:
				{
					opcodeB6();
					break;
				}
				case 7:
				{
					opcodeB7();
					break;
				}
				case 8:
				{
					opcodeB8();
					break;
				}
				case 9:
				{
					opcodeB9();
					break;
				}
				case 0xA:
				{
					opcodeBA();
					break;
				}
				case 0xB:
				{
					opcodeBB();
					break;
				}
				case 0xC:
				{
					opcodeBC();
					break;
				}
				case 0xD:
				{
					opcodeBD();
					break;
				}
				case 0xE:
				{
					opcodeBE();
					break;
				}
				case 0xF:
				{
					opcodeBF();
					break;
				}
			}
			break;
		}
		case 0xC0:
		{
			switch (opcode & 0x0F)
			{
				case 0x00:
				{
					opcodeC0();
					break;
				}
				case 0x01:
				{
					opcodeC1();
					break;
				}
				case 0x02:
				{
                    opcodeC2((memory->readMemory(memory->memoryPointer++)) | (memory->readMemory(memory->memoryPointer++) << 8));
					break;
				}
				case 0x03:
				{
                    opcodeC3((memory->readMemory(memory->memoryPointer++)) | (memory->readMemory(memory->memoryPointer++) << 8));
					break;
				}
				case 0x04:
				{
                    opcodeC4((memory->readMemory(memory->memoryPointer++)) | (memory->readMemory(memory->memoryPointer++) << 8));
					break;
				}
				case 0x05:
				{
					opcodeC5();
					break;
				}
				case 0x06:
				{
                    opcodeC6(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 0x07:
				{
					opcodeC7();
					break;
				}
				case 0x08:
				{
					opcodeC8();
					break;
				}
				case 0x09:
				{
					opcodeC9();
					break;
				}
				case 0x0A:
				{
                    opcodeCA((memory->readMemory(memory->memoryPointer++)) | (memory->readMemory(memory->memoryPointer++) << 8));
					break;
				}
				case 0x0B:
				{
                    switch (memory->readMemory(memory->memoryPointer++))
					{

					case 0x00: { opcodeCB00(); break; }
					case 0x01: { opcodeCB01(); break; }
					case 0x02: { opcodeCB02(); break; }
					case 0x03: { opcodeCB03(); break; }
					case 0x04: { opcodeCB04(); break; }
					case 0x05: { opcodeCB05(); break; }
					case 0x06: { opcodeCB06(); break; }
					case 0x07: { opcodeCB07(); break; }
					case 0x08: { opcodeCB08(); break; }
					case 0x09: { opcodeCB09(); break; }
					case 0x0A: { opcodeCB0A(); break; }
					case 0x0B: { opcodeCB0B(); break; }
					case 0x0C: { opcodeCB0C(); break; }
					case 0x0D: { opcodeCB0D(); break; }
					case 0x0E: { opcodeCB0E(); break; }
					case 0x0F: { opcodeCB0F(); break; }
					case 0x10: { opcodeCB10(); break; }
					case 0x11: { opcodeCB11(); break; }
					case 0x12: { opcodeCB12(); break; }
					case 0x13: { opcodeCB13(); break; }
					case 0x14: { opcodeCB14(); break; }
					case 0x15: { opcodeCB15(); break; }
					case 0x16: { opcodeCB16(); break; }
					case 0x17: { opcodeCB17(); break; }
					case 0x18: { opcodeCB18(); break; }
					case 0x19: { opcodeCB19(); break; }
					case 0x1A: { opcodeCB1A(); break; }
					case 0x1B: { opcodeCB1B(); break; }
					case 0x1C: { opcodeCB1C(); break; }
					case 0x1D: { opcodeCB1D(); break; }
					case 0x1E: { opcodeCB1E(); break; }
					case 0x1F: { opcodeCB1F(); break; }
					case 0x20: { opcodeCB20(); break; }
					case 0x21: { opcodeCB21(); break; }
					case 0x22: { opcodeCB22(); break; }
					case 0x23: { opcodeCB23(); break; }
					case 0x24: { opcodeCB24(); break; }
					case 0x25: { opcodeCB25(); break; }
					case 0x26: { opcodeCB26(); break; }
					case 0x27: { opcodeCB27(); break; }
					case 0x28: { opcodeCB28(); break; }
					case 0x29: { opcodeCB29(); break; }
					case 0x2A: { opcodeCB2A(); break; }
					case 0x2B: { opcodeCB2B(); break; }
					case 0x2C: { opcodeCB2C(); break; }
					case 0x2D: { opcodeCB2D(); break; }
					case 0x2E: { opcodeCB2E(); break; }
					case 0x2F: { opcodeCB2F(); break; }
					case 0x30: { opcodeCB30(); break; }
					case 0x31: { opcodeCB31(); break; }
					case 0x32: { opcodeCB32(); break; }
					case 0x33: { opcodeCB33(); break; }
					case 0x34: { opcodeCB34(); break; }
					case 0x35: { opcodeCB35(); break; }
					case 0x36: { opcodeCB36(); break; }
					case 0x37: { opcodeCB37(); break; }
					case 0x38: { opcodeCB38(); break; }
					case 0x39: { opcodeCB39(); break; }
					case 0x3A: { opcodeCB3A(); break; }
					case 0x3B: { opcodeCB3B(); break; }
					case 0x3C: { opcodeCB3C(); break; }
					case 0x3D: { opcodeCB3D(); break; }
					case 0x3E: { opcodeCB3E(); break; }
					case 0x3F: { opcodeCB3F(); break; }
					case 0x40: { opcodeCB40(); break; }
					case 0x41: { opcodeCB41(); break; }
					case 0x42: { opcodeCB42(); break; }
					case 0x43: { opcodeCB43(); break; }
					case 0x44: { opcodeCB44(); break; }
					case 0x45: { opcodeCB45(); break; }
					case 0x46: { opcodeCB46(); break; }
					case 0x47: { opcodeCB47(); break; }
					case 0x48: { opcodeCB48(); break; }
					case 0x49: { opcodeCB49(); break; }
					case 0x4A: { opcodeCB4A(); break; }
					case 0x4B: { opcodeCB4B(); break; }
					case 0x4C: { opcodeCB4C(); break; }
					case 0x4D: { opcodeCB4D(); break; }
					case 0x4E: { opcodeCB4E(); break; }
					case 0x4F: { opcodeCB4F(); break; }
					case 0x50: { opcodeCB50(); break; }
					case 0x51: { opcodeCB51(); break; }
					case 0x52: { opcodeCB52(); break; }
					case 0x53: { opcodeCB53(); break; }
					case 0x54: { opcodeCB54(); break; }
					case 0x55: { opcodeCB55(); break; }
					case 0x56: { opcodeCB56(); break; }
					case 0x57: { opcodeCB57(); break; }
					case 0x58: { opcodeCB58(); break; }
					case 0x59: { opcodeCB59(); break; }
					case 0x5A: { opcodeCB5A(); break; }
					case 0x5B: { opcodeCB5B(); break; }
					case 0x5C: { opcodeCB5C(); break; }
					case 0x5D: { opcodeCB5D(); break; }
					case 0x5E: { opcodeCB5E(); break; }
					case 0x5F: { opcodeCB5F(); break; }
					case 0x60: { opcodeCB60(); break; }
					case 0x61: { opcodeCB61(); break; }
					case 0x62: { opcodeCB62(); break; }
					case 0x63: { opcodeCB63(); break; }
					case 0x64: { opcodeCB64(); break; }
					case 0x65: { opcodeCB65(); break; }
					case 0x66: { opcodeCB66(); break; }
					case 0x67: { opcodeCB67(); break; }
					case 0x68: { opcodeCB68(); break; }
					case 0x69: { opcodeCB69(); break; }
					case 0x6A: { opcodeCB6A(); break; }
					case 0x6B: { opcodeCB6B(); break; }
					case 0x6C: { opcodeCB6C(); break; }
					case 0x6D: { opcodeCB6D(); break; }
					case 0x6E: { opcodeCB6E(); break; }
					case 0x6F: { opcodeCB6F(); break; }
					case 0x70: { opcodeCB70(); break; }
					case 0x71: { opcodeCB71(); break; }
					case 0x72: { opcodeCB72(); break; }
					case 0x73: { opcodeCB73(); break; }
					case 0x74: { opcodeCB74(); break; }
					case 0x75: { opcodeCB75(); break; }
					case 0x76: { opcodeCB76(); break; }
					case 0x77: { opcodeCB77(); break; }
					case 0x78: { opcodeCB78(); break; }
					case 0x79: { opcodeCB79(); break; }
					case 0x7A: { opcodeCB7A(); break; }
					case 0x7B: { opcodeCB7B(); break; }
					case 0x7C: { opcodeCB7C(); break; }
					case 0x7D: { opcodeCB7D(); break; }
					case 0x7E: { opcodeCB7E(); break; }
					case 0x7F: { opcodeCB7F(); break; }
					case 0x80: { opcodeCB80(); break; }
					case 0x81: { opcodeCB81(); break; }
					case 0x82: { opcodeCB82(); break; }
					case 0x83: { opcodeCB83(); break; }
					case 0x84: { opcodeCB84(); break; }
					case 0x85: { opcodeCB85(); break; }
					case 0x86: { opcodeCB86(); break; }
					case 0x87: { opcodeCB87(); break; }
					case 0x88: { opcodeCB88(); break; }
					case 0x89: { opcodeCB89(); break; }
					case 0x8A: { opcodeCB8A(); break; }
					case 0x8B: { opcodeCB8B(); break; }
					case 0x8C: { opcodeCB8C(); break; }
					case 0x8D: { opcodeCB8D(); break; }
					case 0x8E: { opcodeCB8E(); break; }
					case 0x8F: { opcodeCB8F(); break; }
					case 0x90: { opcodeCB90(); break; }
					case 0x91: { opcodeCB91(); break; }
					case 0x92: { opcodeCB92(); break; }
					case 0x93: { opcodeCB93(); break; }
					case 0x94: { opcodeCB94(); break; }
					case 0x95: { opcodeCB95(); break; }
					case 0x96: { opcodeCB96(); break; }
					case 0x97: { opcodeCB97(); break; }
					case 0x98: { opcodeCB98(); break; }
					case 0x99: { opcodeCB99(); break; }
					case 0x9A: { opcodeCB9A(); break; }
					case 0x9B: { opcodeCB9B(); break; }
					case 0x9C: { opcodeCB9C(); break; }
					case 0x9D: { opcodeCB9D(); break; }
					case 0x9E: { opcodeCB9E(); break; }
					case 0x9F: { opcodeCB9F(); break; }
					case 0xA0: { opcodeCBA0(); break; }
					case 0xA1: { opcodeCBA1(); break; }
					case 0xA2: { opcodeCBA2(); break; }
					case 0xA3: { opcodeCBA3(); break; }
					case 0xA4: { opcodeCBA4(); break; }
					case 0xA5: { opcodeCBA5(); break; }
					case 0xA6: { opcodeCBA6(); break; }
					case 0xA7: { opcodeCBA7(); break; }
					case 0xA8: { opcodeCBA8(); break; }
					case 0xA9: { opcodeCBA9(); break; }
					case 0xAA: { opcodeCBAA(); break; }
					case 0xAB: { opcodeCBAB(); break; }
					case 0xAC: { opcodeCBAC(); break; }
					case 0xAD: { opcodeCBAD(); break; }
					case 0xAE: { opcodeCBAE(); break; }
					case 0xAF: { opcodeCBAF(); break; }
					case 0xB0: { opcodeCBB0(); break; }
					case 0xB1: { opcodeCBB1(); break; }
					case 0xB2: { opcodeCBB2(); break; }
					case 0xB3: { opcodeCBB3(); break; }
					case 0xB4: { opcodeCBB4(); break; }
					case 0xB5: { opcodeCBB5(); break; }
					case 0xB6: { opcodeCBB6(); break; }
					case 0xB7: { opcodeCBB7(); break; }
					case 0xB8: { opcodeCBB8(); break; }
					case 0xB9: { opcodeCBB9(); break; }
					case 0xBA: { opcodeCBBA(); break; }
					case 0xBB: { opcodeCBBB(); break; }
					case 0xBC: { opcodeCBBC(); break; }
					case 0xBD: { opcodeCBBD(); break; }
					case 0xBE: { opcodeCBBE(); break; }
					case 0xBF: { opcodeCBBF(); break; }
					case 0xC0: { opcodeCBC0(); break; }
					case 0xC1: { opcodeCBC1(); break; }
					case 0xC2: { opcodeCBC2(); break; }
					case 0xC3: { opcodeCBC3(); break; }
					case 0xC4: { opcodeCBC4(); break; }
					case 0xC5: { opcodeCBC5(); break; }
					case 0xC6: { opcodeCBC6(); break; }
					case 0xC7: { opcodeCBC7(); break; }
					case 0xC8: { opcodeCBC8(); break; }
					case 0xC9: { opcodeCBC9(); break; }
					case 0xCA: { opcodeCBCA(); break; }
					case 0xCB: { opcodeCBCB(); break; }
					case 0xCC: { opcodeCBCC(); break; }
					case 0xCD: { opcodeCBCD(); break; }
					case 0xCE: { opcodeCBCE(); break; }
					case 0xCF: { opcodeCBCF(); break; }
					case 0xD0: { opcodeCBD0(); break; }
					case 0xD1: { opcodeCBD1(); break; }
					case 0xD2: { opcodeCBD2(); break; }
					case 0xD3: { opcodeCBD3(); break; }
					case 0xD4: { opcodeCBD4(); break; }
					case 0xD5: { opcodeCBD5(); break; }
					case 0xD6: { opcodeCBD6(); break; }
					case 0xD7: { opcodeCBD7(); break; }
					case 0xD8: { opcodeCBD8(); break; }
					case 0xD9: { opcodeCBD9(); break; }
					case 0xDA: { opcodeCBDA(); break; }
					case 0xDB: { opcodeCBDB(); break; }
					case 0xDC: { opcodeCBDC(); break; }
					case 0xDD: { opcodeCBDD(); break; }
					case 0xDE: { opcodeCBDE(); break; }
					case 0xDF: { opcodeCBDF(); break; }
					case 0xE0: { opcodeCBE0(); break; }
					case 0xE1: { opcodeCBE1(); break; }
					case 0xE2: { opcodeCBE2(); break; }
					case 0xE3: { opcodeCBE3(); break; }
					case 0xE4: { opcodeCBE4(); break; }
					case 0xE5: { opcodeCBE5(); break; }
					case 0xE6: { opcodeCBE6(); break; }
					case 0xE7: { opcodeCBE7(); break; }
					case 0xE8: { opcodeCBE8(); break; }
					case 0xE9: { opcodeCBE9(); break; }
					case 0xEA: { opcodeCBEA(); break; }
					case 0xEB: { opcodeCBEB(); break; }
					case 0xEC: { opcodeCBEC(); break; }
					case 0xED: { opcodeCBED(); break; }
					case 0xEE: { opcodeCBEE(); break; }
					case 0xEF: { opcodeCBEF(); break; }
					case 0xF0: { opcodeCBF0(); break; }
					case 0xF1: { opcodeCBF1(); break; }
					case 0xF2: { opcodeCBF2(); break; }
					case 0xF3: { opcodeCBF3(); break; }
					case 0xF4: { opcodeCBF4(); break; }
					case 0xF5: { opcodeCBF5(); break; }
					case 0xF6: { opcodeCBF6(); break; }
					case 0xF7: { opcodeCBF7(); break; }
					case 0xF8: { opcodeCBF8(); break; }
					case 0xF9: { opcodeCBF9(); break; }
					case 0xFA: { opcodeCBFA(); break; }
					case 0xFB: { opcodeCBFB(); break; }
					case 0xFC: { opcodeCBFC(); break; }
					case 0xFD: { opcodeCBFD(); break; }
					case 0xFE: { opcodeCBFE(); break; }
					case 0xFF: { opcodeCBFF(); break; }

					}
					break;
				}
				case 0x0C:
				{
                    opcodeCC((memory->readMemory(memory->memoryPointer++)) | (memory->readMemory(memory->memoryPointer++) << 8));
					break;
				}
				case 0x0D:
				{
                    opcodeCD((memory->readMemory(memory->memoryPointer++)) | (memory->readMemory(memory->memoryPointer++) << 8));
					break;
				}
				case 0x0E:
				{
                    opcodeCE(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 0x0F:
				{
					opcodeCF();
					break;
				}
			}
			break;

		}
		case 0xD0:
		{
			switch (opcode & 0x0F)
			{
			case 0:
			{
				opcodeD0();
				break;
			}
				case 1:
				{
					opcodeD1();
					break;
				}
				case 2:
				{
                    opcodeD2((memory->readMemory(memory->memoryPointer++)) | (memory->readMemory(memory->memoryPointer++) << 8));
					break;
				}
				case 3:
				{
					//D3 does not exist
					break;
				}
				case 4:
				{
                    opcodeD4((memory->readMemory(memory->memoryPointer++)) | (memory->readMemory(memory->memoryPointer++) << 8));
					break;
				}
				case 5:
				{
					opcodeD5();
					break;
				}
				case 6:
				{
                    opcodeD6(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 7:
				{
					opcodeD7();
					break;
				}
				case 8:
				{
					opcodeD8();
					break;
				}
				case 9:
				{
					opcodeD9();
					break;
				}
				case 0xA:
				{
                    opcodeDA((memory->readMemory(memory->memoryPointer++)) | (memory->readMemory(memory->memoryPointer++) << 8));
					break;
				}
				case 0xB:
				{
					//Does not exist
					break;
				}
				case 0xC:
				{
                    opcodeDC((memory->readMemory(memory->memoryPointer++)) | (memory->readMemory(memory->memoryPointer++) << 8));
					break;
				}
				case 0xD:
				{
					//DD not exist
					break;
				}
				case 0xE:
				{
                    opcodeDE(memory->readMemory(memory->memoryPointer++));
					break;

				}
				case 0xF:
				{
					opcodeDF();
				}
			}
			break;
		}
		case 0xE0:
		{
			switch (opcode & 0x0F)
			{
				case 0:
				{
                    opcodeE0(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 1:
				{
					opcodeE1();
					break;
				}
				case 2:
				{
					opcodeE2();
					break;
				}
				case 3:
				{
					//E3 does not exist
					break;
				}
				case 4:
				{
					//E4 does not exist
					break;
				}
				case 5:
				{
					opcodeE5();
					break;
				}
				case 6:
				{
                    opcodeE6(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 7:
				{
					opcodeE7();
					break;
				}
				case 8:
				{
                    opcodeE8(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 9:
				{
					opcodeE9();
					break;
				}
				case 0xA:
				{
                    opcodeEA((memory->readMemory(memory->memoryPointer++)) | (memory->readMemory(memory->memoryPointer++) << 8));
					break;
				}
				case 0xB:
				{
					//EB not exist
					break;
				}
				case 0xC:
				{
					//EC not exist
					break;
				}
				case 0xD:
				{
					//ED not exist
					break;
				}
				case 0xE:
				{
                    opcodeEE(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 0xF:
				{
					opcodeEF();
					break;
				}
			}
			break;
		}
		case 0xF0:
		{
			switch (opcode & 0x0F)
			{
				case 0:
				{
                    opcodeF0(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 1:
				{
					opcodeF1();
					break;
				}
				case 2:
				{
					opcodeF2();
					break;
				}
				case 3:
				{
					//Disable Interrupts
					opcodeF3();
					break;
				}
				case 4:
				{
					//F4 not exist
					break;
				}
				case 5:
				{
					opcodeF5();
					break;
				}
				case 6:
				{
                    opcodeF6(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 7:
				{
					opcodeF7();
					break;
				}
				case 8:
				{
                    opcodeF8(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 9:
				{
					opcodeF9();
					break;
				}
				case 0xA:
				{
                    opcodeFA((memory->readMemory(memory->memoryPointer++)) | (memory->readMemory(memory->memoryPointer++) << 8));
					break;
				}
				case 0xB:
				{
					//Enable Interrupts
					opcodeFB();
					break;
				}
				case 0xC:
				{
					//FC not exist
					break;
				}
				case 0xD:
				{
					//FD not exist
					break;
				}
				case 0xE:
				{
                    opcodeFE(memory->readMemory(memory->memoryPointer++));
					break;
				}
				case 0xF:
				{
					opcodeFF();
					break;
				}
			}

			break;
		}
	}
}


void Cpu::opcode00()
{
	//NOP
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode01(short nn)
{
	//Load short into BC
    memory->setBC(nn);
	mClock += 3;
	tClock += 12;
}

void Cpu::opcode02()
{
	//Load A into data at BC
    memory->writeMemory(memory->getBC(), memory->getA());
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode03()
{
	//Inc BC

    memory->setBC(memory->getBC() + 1);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcode04()
{
	//Inc B

    memory->setB(memory->getB() + 1);

	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getB() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag((((memory->getB()) & 0x0F) == 0) ? 1 : 0);
}

void Cpu::opcode05()
{
	//Dec B

    memory->setB(memory->getB() - 1);

	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getB() == 0) ? 1 : 0);
    memory->setNFlag(true);
    memory->setHFlag((((memory->getB()) & 0x0F) == 0xF) ? 1 : 0);
}

void Cpu::opcode06(unsigned char n)
{
	//Load byte into B
    memory->setB(n);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode07()
{
	
	//Rotate A Left - Set C flag to old bit 7
    memory->setA(rotateLeft(memory->getA()));
    memory->setCFlag(((memory->getA() & 0x01) == 1) ? true : false);
	mClock += 1;
	tClock += 4;
	
    memory->setZFlag(false);
    memory->setHFlag(false);
    memory->setNFlag(false);

}

void Cpu::opcode08(short nn)
{
	//Load SP into data at NN
    memory->writeMemory(nn, stackPointer);
	mClock += 5;
	tClock += 20;
}

void Cpu::opcode09()
{
	//Add BC to HL

    unsigned short hl = memory->getHL();
    unsigned short bc = memory->getBC();
	int totalSum = hl + bc;

    memory->setHFlag((hl & 0x0FFF) > (totalSum & 0x0FFF));
    memory->setHL(totalSum & 0xFFFF);
    memory->setCFlag(totalSum > 0xFFFF);
	
	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);

}


void Cpu::opcode0A()
{
	//Load data at BC into A
    memory->setA(memory->readMemory(memory->getBC()));
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode0B()
{
	//Dec BC

    memory->setBC(memory->getBC() - 1);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcode0C()
{
	//Inc C

    memory->setC(memory->getC() + 1);

	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getC() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag((((memory->getC()) & 0x0F) == 0) ? 1 : 0);
}

void Cpu::opcode0D()
{
	//Dec C

    memory->setC(memory->getC() - 1);

	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getC() == 0) ? 1 : 0);
    memory->setNFlag(true);
    memory->setHFlag((((memory->getC()) & 0x0F) == 0xF) ? 1 : 0);
}

void Cpu::opcode0E(unsigned char n)
{
	//Load byte into C
    memory->setC(n);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode0F()
{
	//Rotate A Right, put previous bit 0 into Carry flag

    memory->setCFlag( (memory->getA() & 0x01) > 0);
    memory->setA(rotateRight(memory->getA()));

	mClock += 1;
	tClock += 4;

    memory->setZFlag(false);
    memory->setNFlag(false);
    memory->setHFlag(false);

}

void Cpu::opcode10()
{
	// Stop
	stop = true;

	// Skip operand byte.
    memory->memoryPointer++;
}

void Cpu::opcode11(short nn)
{
	//Load short into DE
    memory->setDE(nn);
	mClock += 3;
	tClock += 12;
}

void Cpu::opcode12()
{
	//Load A into data at DE
    memory->writeMemory(memory->getDE(), memory->getA());
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode13()
{
	//Inc DE

    memory->setDE(memory->getDE() + 1);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcode14()
{
	//Inc D

    memory->setD(memory->getD() + 1);

	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getD() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag((((memory->getD()) & 0x0F) == 0) ? 1 : 0);
}

void Cpu::opcode15()
{
	//Dec D

    memory->setD(memory->getD() - 1);

	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getD() == 0) ? 1 : 0);
    memory->setNFlag(true);
    memory->setHFlag((((memory->getD()) & 0x0F) == 0xF) ? 1 : 0);
}

void Cpu::opcode16(unsigned char n)
{
	//Load byte into D
    memory->setD(n);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode17()
{
	//RLCA Rotate A Left - Set right most bit to current carry flag
    unsigned char cFlag = (memory->getCFlag() == true) ? 0x01 : 0x00;
    memory->setCFlag( ((memory->getA() & 0x80) >> 7) > 0);
    memory->setA((memory->getA() << 1) | cFlag);

    memory->setZFlag(false);
    memory->setHFlag(false);
    memory->setNFlag(false);
	mClock += 1;
	tClock += 4;

}

void Cpu::opcode18(char n) //signed byte
{
	//Jump Relative to n
    memory->memoryPointer += (signed char)n;
	mClock += 3;
	tClock += 12;
}

void Cpu::opcode19()
{
	//Add DE to HL

    unsigned short hl = memory->getHL();
    unsigned short de = memory->getDE();
	int totalSum = hl + de;

    memory->setHFlag((hl & 0x0FFF) > (totalSum & 0x0FFF));
    memory->setHL(totalSum & 0xFFFF);
    memory->setCFlag(totalSum > 0xFFFF);

	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);
}

void Cpu::opcode1A()
{
	//Load data at DE into A
    memory->setA(memory->readMemory(memory->getDE()));
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode1B()
{
	//Dec DE

    memory->setDE(memory->getDE() - 1);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcode1C()
{
	//Inc E

    memory->setE(memory->getE() + 1);

	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getE() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag((((memory->getE()) & 0x0F) == 0) ? 1 : 0);
}

void Cpu::opcode1D()
{
	//Dec E

    memory->setE(memory->getE() - 1);

	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getE() == 0) ? 1 : 0);
    memory->setNFlag(true);
    memory->setHFlag((((memory->getE()) & 0x0F) == 0xF) ? 1 : 0);
}

void Cpu::opcode1E(unsigned char n)
{
	//Load byte into E
    memory->setE(n);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode1F()
{
	//RRA - Rotate A Right - Store old bit 0 in Carry Flag - Current Carry flag becomes new bit 7
	//Rotate A Right - Set left most bit to current carry flag
    unsigned char cFlag = (memory->getCFlag() == true) ? 0x80 : 0x00;
    memory->setCFlag(((memory->getA() & 0x01) == 1) ? true : false);
    memory->setA((memory->getA() >> 1) | cFlag);
	mClock += 1;
	tClock += 4;

    memory->setZFlag(false);
    memory->setHFlag(false);
    memory->setNFlag(false);
}

void Cpu::opcode20(unsigned char n)
{
	//Jump Relative to n if Not Zero
    if (!memory->getZFlag())
	{
        memory->memoryPointer += (signed char)n;
		mClock += 3;
		tClock += 12;

	}
	else
	{
		mClock += 2;
		tClock += 8;
	}
}

void Cpu::opcode21(short nn)
{
	//Load short into HL
    memory->setHL(nn);
	mClock += 3;
	tClock += 12;
}

void Cpu::opcode22()
{
	//Load A into data at HL and increment HL
    memory->writeMemory(memory->getHL(), memory->getA());
    memory->setHL(memory->getHL() + 1);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode23()
{
	//Inc HL

    memory->setHL(memory->getHL() + 1);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcode24()
{
	//Inc H

    memory->setH(memory->getH() + 1);

	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getH() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag((((memory->getH()) & 0x0F) == 0) ? 1 : 0);
}

void Cpu::opcode25()
{
	//Dec H

    memory->setH(memory->getH() - 1);

	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getH() == 0) ? 1 : 0);
    memory->setNFlag(true);
    memory->setHFlag((((memory->getH()) & 0x0F) == 0xF) ? 1 : 0);
}

void Cpu::opcode26(unsigned char n)
{
	//Load byte into H
    memory->setH(n);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode27()
{
	//DAA Load decimal representation of A into A

    uint8_t aValue = memory->getA();

    if (!memory->getNFlag())
	{
        if (memory->getCFlag() || (aValue > 0x99))
		{
			aValue += 0x60;
            memory->setCFlag(true);
		}

        if(memory->getHFlag() || ((aValue & 0x0F) > 0x09))
		{
			aValue += 0x06;
		}

	}
	else
	{
        if (memory->getHFlag())
		{
			aValue -= 0x6;
		}

        if (memory->getCFlag())
		{
			aValue -= 0x60;
		}
	}

    memory->setA(aValue);
    memory->setZFlag(aValue == 0);
    memory->setHFlag(false);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode28(unsigned char n)
{
    //Jump to memory->memoryPointer + n if Zero
    if (memory->getZFlag())
	{
        //memory->memoryPointer += (signed char)n;
        memory->memoryPointer += (signed char)n;
		mClock += 3;
		tClock += 12;
	}
	else
	{
		mClock += 2;
		tClock += 8;
	}
}

void Cpu::opcode29()
{
	//Add HL to HL

    unsigned short hl = memory->getHL();
	int totalSum = hl + hl;

    memory->setHFlag((hl & 0x0FFF) > (totalSum & 0x0FFF));
    memory->setHL(totalSum & 0xFFFF);
    memory->setCFlag(totalSum > 0xFFFF);

	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);
}

void Cpu::opcode2A()
{
	//Load data at HL to A and inc HL
    memory->setA(memory->readMemory(memory->getHL()));
    memory->setHL(memory->getHL() + 1);
	mClock += 2;
	tClock += 8;

}

void Cpu::opcode2B()
{
	//Dec HL
    memory->setHL(memory->getHL() - 1);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode2C()
{
	//Inc L
    memory->setL(memory->getL() + 1);
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getL() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag((((memory->getL()) & 0x0F) == 0) ? 1 : 0);
}

void Cpu::opcode2D()
{
	//Dec L
    memory->setL(memory->getL() - 1);
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getL() == 0) ? 1 : 0);
    memory->setNFlag(true);
    memory->setHFlag((((memory->getL()) & 0x0F) == 0xF) ? 1 : 0);
}

void Cpu::opcode2E(unsigned char n)
{
	//Load a byte into L
    memory->setL(n);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode2F()
{
	//CPL - Flip all bits in A
    memory->setA(~memory->getA());
	mClock += 1;
	tClock += 4;

    memory->setNFlag(true);
    memory->setHFlag(true);
}

void Cpu::opcode30(unsigned char n)
{
	//Jump Relative to n if Not Carry
    if (!memory->getCFlag())
	{
        memory->memoryPointer += (signed char)n;
		mClock += 3;
		tClock += 12;
	}
	else
	{
		mClock += 2;
		tClock += 8;
	}
}

void Cpu::opcode31(short nn)
{
	//Load short into SP
	stackPointer = nn;
	mClock += 3;
	tClock += 12;
}

void Cpu::opcode32()
{
	//Load A into data at HL and dec HL
    memory->writeMemory(memory->getHL(), memory->getA());
    memory->setHL(memory->getHL() - 1);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode33()
{
	//Inc SP
	stackPointer++;
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode34()
{
	//Inc data at HL
    memory->writeMemory(memory->getHL(), (unsigned char)(memory->readMemory(memory->getHL()) + 1));
	mClock += 3;
	tClock += 12;

    memory->setZFlag((memory->readMemory(memory->getHL()) == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag((((memory->readMemory(memory->getHL())) & 0x0F) == 0) ? 1 : 0);
}

void Cpu::opcode35()
{
	//Dec data at HL
    memory->writeMemory(memory->getHL(), (unsigned char)(memory->readMemory(memory->getHL()) - 1));
	mClock += 3;
	tClock += 12;

    memory->setZFlag((memory->readMemory(memory->getHL()) == 0) ? 1 : 0);
    memory->setNFlag(true);
    memory->setHFlag((((memory->readMemory(memory->getHL())) & 0x0F) == 0xF) ? 1 : 0);
}

void Cpu::opcode36(unsigned char n)
{
	//Load byte into data at HL
    memory->writeMemory(memory->getHL(), n);
	mClock += 3;
	tClock += 12;
}

void Cpu::opcode37()
{
	//SCF Set Carry Flag
    memory->setCFlag(true);
	mClock += 1;
	tClock += 4;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcode38(unsigned char n)
{
	//Jump Relative to n if Carry
    if (memory->getCFlag())
	{
        memory->memoryPointer += (signed char)n;
		mClock += 3;
		tClock += 12;
	}
	else
	{
		mClock += 2;
		tClock += 8;
	}
}

void Cpu::opcode39()
{
	//Add SP to HL
    unsigned short hl = memory->getHL();
	unsigned short sp = stackPointer;
	int totalSum = hl + sp;

    memory->setHFlag((hl & 0x0FFF) > (totalSum & 0x0FFF));
    memory->setHL(totalSum & 0xFFFF);
    memory->setCFlag(totalSum > 0xFFFF);

	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);
}

void Cpu::opcode3A()
{
	//Load data in HL into A and decrement HL
    memory->setA(memory->readMemory(memory->getHL()));
    memory->setHL(memory->getHL() - 1);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode3B()
{
	//Dec SP
	stackPointer--;
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode3C()
{
	//Inc A
    memory->setA(memory->getA() + 1);
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag((((memory->getA()) & 0x0F) == 0) ? 1 : 0);
}

void Cpu::opcode3D()
{
	//Dec A
    memory->setA(memory->getA() - 1);
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(true);
    memory->setHFlag((((memory->getA()) & 0x0F) == 0xF) ? 1 : 0);
}

void Cpu::opcode3E(unsigned char n)
{
	//Load byte into A
    memory->setA(n);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode3F()
{
	//Complement Carry Flag (Toggle C Flag)
    memory->setCFlag((memory->getCFlag() == 1) ? 0 : 1);
	mClock += 1;
	tClock += 4;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcode40()
{
	//Load B into B
    memory->setB(memory->getB());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode41()
{
	//Load C into B
    memory->setB(memory->getC());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode42()
{
	//Load D into B
    memory->setB(memory->getD());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode43()
{
	//Load E into B
    memory->setB(memory->getE());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode44()
{
	//Load H into B
    memory->setB(memory->getH());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode45()
{
	//Load L into B
    memory->setB(memory->getL());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode46()
{
	//Load data at HL into B
    memory->setB(memory->readMemory(memory->getHL()));
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode47()
{
	//Load A into B
    memory->setB(memory->getA());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode48()
{
	//Load B into C
    memory->setC(memory->getB());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode49()
{
	//Load C into C
    memory->setC(memory->getC());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode4A()
{
	//Load D into C
    memory->setC(memory->getD());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode4B()
{
	//Load E into C
    memory->setC(memory->getE());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode4C()
{
	//Load H into C
    memory->setC(memory->getH());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode4D()
{
	//Load L into C
    memory->setC(memory->getL());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode4E()
{
	//Load data at HL into C
    memory->setC(memory->readMemory(memory->getHL()));
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode4F()
{
	//Load A into C
    memory->setC(memory->getA());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode50()
{
	//Load B into D
    memory->setD(memory->getB());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode51()
{
	//Load C into D
    memory->setD(memory->getC());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode52()
{
	//Load D into D
    memory->setD(memory->getD());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode53()
{
	//Load E into D
    memory->setD(memory->getE());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode54()
{
	//Load H into D
    memory->setD(memory->getH());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode55()
{
	//Load L into D
    memory->setD(memory->getL());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode56()
{
	//Load data at HL into D
    memory->setD(memory->readMemory(memory->getHL()));
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode57()
{
	//Load A into D
    memory->setD(memory->getA());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode58()
{
	//Load B into E
    memory->setE(memory->getB());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode59()
{
	//Load C into E
    memory->setE(memory->getC());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode5A()
{
	//Load D into E
    memory->setE(memory->getD());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode5B()
{
	//Load E into E
    memory->setE(memory->getE());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode5C()
{
	//Load H into E
    memory->setE(memory->getH());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode5D()
{
	//Load L into D
    memory->setE(memory->getL());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode5E()
{
	//Load data at HL into E
    memory->setE(memory->readMemory(memory->getHL()));
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode5F()
{
	//Load A into E
    memory->setE(memory->getA());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode60()
{
	//Load B into H
    memory->setH(memory->getB());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode61()
{
	//Load C into H
    memory->setH(memory->getC());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode62()
{
	//Load D into H
    memory->setH(memory->getD());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode63()
{
	//Load E into H
    memory->setH(memory->getE());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode64()
{
	//Load H into H
    memory->setH(memory->getH());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode65()
{
	//Load L into H
    memory->setH(memory->getL());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode66()
{
	//Load data at HL into H
    memory->setH(memory->readMemory(memory->getHL()));
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode67()
{
	//Load A into H
    memory->setH(memory->getA());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode68()
{
	//Load B into L
    memory->setL(memory->getB());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode69()
{
	//Load C into L
    memory->setL(memory->getC());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode6A()
{
	//Load D into L
    memory->setL(memory->getD());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode6B()
{
	//Load E into L
    memory->setL(memory->getE());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode6C()
{
	//Load H into L
    memory->setL(memory->getH());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode6D()
{
	//Load L into L
    memory->setL(memory->getL());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode6E()
{
	//Load data at HL into L
    memory->setL(memory->readMemory(memory->getHL()));
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode6F()
{
	//Load A into L
    memory->setL(memory->getA());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode70()
{
	//Load B into data at HL
    memory->writeMemory(memory->getHL(), memory->getB());
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode71()
{
	//Load C into data at HL
    memory->writeMemory(memory->getHL(), memory->getC());
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode72()
{
	//Load D into data at HL
    memory->writeMemory(memory->getHL(), memory->getD());
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode73()
{
	//Load E into data at HL
    memory->writeMemory(memory->getHL(), memory->getE());
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode74()
{
	//Load H into data at HL
    memory->writeMemory(memory->getHL(), memory->getH());
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode75()
{
	//Load L into data at HL
    memory->writeMemory(memory->getHL(), memory->getL());
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode76()
{
	//Halt
	
	if (interruptsEnabled == true) //If IME == 1
	{
		//Enter Halt Normally
		haltMode = 1;
		halt = true;
	}
	else
	{
		if (checkForInterrupt())
		{
			//Halt is not entered, halt bug occurs
			haltMode = 0;
			halt = false;
			repeatBug = true;
		}
		else
		{
			//Halt Entered, but does not jump to interrupt vector
			haltMode = 2;
			halt = true;
		}
	}

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode77()
{
	//Load A into data at HL
    memory->writeMemory(memory->getHL(), memory->getA());
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode78()
{
	//Load B into A
    memory->setA(memory->getB());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode79()
{
	//Load C into A
    memory->setA(memory->getC());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode7A()
{
	//Load D into A
    memory->setA(memory->getD());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode7B()
{
	//Load E into A
    memory->setA(memory->getE());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode7C()
{
	//Load H into A
    memory->setA(memory->getH());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode7D()
{
	//Load L into A
    memory->setA(memory->getL());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode7E()
{
	//Load data at HL into A
    memory->setA(memory->readMemory(memory->getHL()));
	mClock += 2;
	tClock += 8;
}

void Cpu::opcode7F()
{
	//Load A into A
    memory->setA(memory->getA());
	mClock += 1;
	tClock += 4;
}

void Cpu::opcode80()
{
	//Add B to A
    int result = memory->getA() + memory->getB();

    memory->setHFlag((((memory->getA() & 0x0F) + (memory->getB() & 0x0F)) & 0x10) > 0);
    memory->setA((uint8_t)result & 0xFF);
    memory->setCFlag(result > 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 1;
	tClock += 4;

}

void Cpu::opcode81()
{
	//Add C to A
    int result = memory->getA() + memory->getC();

    memory->setHFlag((((memory->getA() & 0x0F) + (memory->getC() & 0x0F)) & 0x10) > 0);
    memory->setA((uint8_t)result & 0xFF);
    memory->setCFlag(result > 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode82()
{
	//Add D to A
    int result = memory->getA() + memory->getD();

    memory->setHFlag((((memory->getA() & 0x0F) + (memory->getD() & 0x0F)) & 0x10) > 0);
    memory->setA((uint8_t)result & 0xFF);
    memory->setCFlag(result > 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode83()
{
	//Add E to A
    int result = memory->getA() + memory->getE();

    memory->setHFlag((((memory->getA() & 0x0F) + (memory->getE() & 0x0F)) & 0x10) > 0);
    memory->setA((uint8_t)result & 0xFF);
    memory->setCFlag(result > 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode84()
{
	//Add H to A
    int result = memory->getA() + memory->getH();

    memory->setHFlag((((memory->getA() & 0x0F) + (memory->getH() & 0x0F)) & 0x10) > 0);
    memory->setA((uint8_t)result & 0xFF);
    memory->setCFlag(result > 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode85()
{
	//Add L to A
    int result = memory->getA() + memory->getL();

    memory->setHFlag((((memory->getA() & 0x0F) + (memory->getL() & 0x0F)) & 0x10) > 0);
    memory->setA((uint8_t)result & 0xFF);
    memory->setCFlag(result > 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode86()
{
	//Add data at HL to A
    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);

    uint8_t data = memory->readMemory(memory->getHL());
    int result = memory->getA() + data;

    memory->setHFlag((((memory->getA() & 0x0F) + (data & 0x0F)) & 0x10) > 0);
    memory->setA((uint8_t)result & 0xFF);
    memory->setCFlag(result > 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcode87()
{
	//Add A to A
    int result = memory->getA() + memory->getA();

    memory->setHFlag((((memory->getA() & 0x0F) + (memory->getA() & 0x0F)) & 0x10) > 0);
    memory->setA((uint8_t)result & 0xFF);
    memory->setCFlag(result > 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode88()
{
	//Add B and Carry flag to A
    int carry = memory->getCFlag() ? 1 : 0;
    int result = memory->getA() + memory->getB() + carry;

    memory->setHFlag((((memory->getA() & 0x0F) + (memory->getB() & 0x0F) + carry) & 0x10) > 0);
    memory->setA((uint8_t)result & 0xFF);
    memory->setCFlag(result > 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode89()
{
	//Add C and Carry flag to A
    int carry = memory->getCFlag() ? 1 : 0;
    int result = memory->getA() + memory->getC() + carry;

    memory->setHFlag((((memory->getA() & 0x0F) + (memory->getC() & 0x0F) + carry) & 0x10) > 0);
    memory->setA((uint8_t)result & 0xFF);
    memory->setCFlag(result > 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode8A()
{
	//Add D and Carry flag to A
    int carry = memory->getCFlag() ? 1 : 0;
    int result = memory->getA() + memory->getD() + carry;

    memory->setHFlag((((memory->getA() & 0x0F) + (memory->getD() & 0x0F) + carry) & 0x10) > 0);
    memory->setA((uint8_t)result & 0xFF);
    memory->setCFlag(result > 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode8B()
{
	//Add E and Carry flag to A
    int carry = memory->getCFlag() ? 1 : 0;
    int result = memory->getA() + memory->getE() + carry;

    memory->setHFlag((((memory->getA() & 0x0F) + (memory->getE() & 0x0F) + carry) & 0x10) > 0);
    memory->setA((uint8_t)result & 0xFF);
    memory->setCFlag(result > 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode8C()
{
	//Add H and Carry flag to A
    int carry = memory->getCFlag() ? 1 : 0;
    int result = memory->getA() + memory->getH() + carry;

    memory->setHFlag((((memory->getA() & 0x0F) + (memory->getH() & 0x0F) + carry) & 0x10) > 0);
    memory->setA((uint8_t)result & 0xFF);
    memory->setCFlag(result > 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode8D()
{
	//Add L and Carry flag to A
    int carry = memory->getCFlag() ? 1 : 0;
    int result = memory->getA() + memory->getL() + carry;

    memory->setHFlag((((memory->getA() & 0x0F) + (memory->getL() & 0x0F) + carry) & 0x10) > 0);
    memory->setA((uint8_t)result & 0xFF);
    memory->setCFlag(result > 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode8E()
{
	//Add data at HL and Carry flag to A
    int data = memory->readMemory(memory->getHL());
    int carry = memory->getCFlag() ? 1 : 0;
    int result = memory->getA() + data + carry;

    memory->setHFlag((((memory->getA() & 0x0F) + (data & 0x0F) + carry) & 0x10) > 0);
    memory->setA((uint8_t)result & 0xFF);
    memory->setCFlag(result > 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcode8F()
{
	//Add A and Carry flag to A
    int carry = memory->getCFlag() ? 1 : 0;
    int result = memory->getA() + memory->getA() + carry;

    memory->setHFlag((((memory->getA() & 0x0F) + (memory->getA() & 0x0F) + carry) & 0x10) > 0);
    memory->setA((uint8_t)result & 0xFF);
    memory->setCFlag(result > 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode90()
{
	//Sub B from A

    int result = memory->getA();
    result -= memory->getB();

    memory->setCFlag(memory->getB() > memory->getA());
    memory->setHFlag((memory->getB() & 0x0F) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setZFlag(result == 0);
    memory->setA(result);

	mClock += 1;
	tClock += 4;

}

void Cpu::opcode91()
{
	//Sub C from A

    int result = memory->getA();
    result -= memory->getC();

    memory->setCFlag(memory->getC() > memory->getA());
    memory->setHFlag((memory->getC() & 0x0F) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setZFlag(result == 0);
    memory->setA(result);

	mClock += 1;
	tClock += 4;

}

void Cpu::opcode92()
{
	//Sub D from A

    int result = memory->getA();
    result -= memory->getD();

    memory->setCFlag(memory->getD() > memory->getA());
    memory->setHFlag((memory->getD() & 0x0F) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setZFlag(result == 0);
    memory->setA(result);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode93()
{
	//Sub E from A

    int result = memory->getA();
    result -= memory->getE();

    memory->setCFlag(memory->getE() > memory->getA());
    memory->setHFlag((memory->getE() & 0x0F) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setZFlag(result == 0);
    memory->setA(result);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode94()
{
	//Sub B from H

    int result = memory->getA();
    result -= memory->getH();

    memory->setCFlag(memory->getH() > memory->getA());
    memory->setHFlag((memory->getH() & 0x0F) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setZFlag(result == 0);
    memory->setA(result);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode95()
{
	//Sub L from A

    int result = memory->getA();
    result -= memory->getL();

    memory->setCFlag(memory->getL() > memory->getA());
    memory->setHFlag((memory->getL() & 0x0F) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setZFlag(result == 0);
    memory->setA(result);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode96()
{
	//Sub data at HL from A

    int result = memory->getA();
    uint8_t n = memory->readMemory(memory->getHL());
	result -= n;

    memory->setCFlag(n > memory->getA());
    memory->setHFlag((n & 0x0F) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setZFlag(result == 0);
    memory->setA(result);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode97()
{
	//Sub A from A

    int result = memory->getA();
    result -= memory->getA();

    memory->setCFlag(memory->getA() > memory->getA());
    memory->setHFlag((memory->getA() & 0x0F) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setZFlag(result == 0);
    memory->setA(result);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode98()
{
	//Sub B and Carry flag from A

    uint8_t carry = memory->getCFlag() ? 1 : 0;
    int result = memory->getA();
    result -= memory->getB();
	result -= carry;

    memory->setCFlag((memory->getB() + carry) > memory->getA());
    memory->setHFlag(((memory->getB() & 0x0F) + carry) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setA(result & 0xFF);
    memory->setZFlag(memory->getA() == 0);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode99()
{
	//Sub C and Carry flag from A

    uint8_t carry = memory->getCFlag() ? 1 : 0;
    int result = memory->getA();
    result -= memory->getC();
	result -= carry;

    memory->setCFlag((memory->getC() + carry) > memory->getA());
    memory->setHFlag(((memory->getC() & 0x0F) + carry) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setA(result & 0xFF);
    memory->setZFlag(memory->getA() == 0);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode9A()
{
	//Sub D and Carry flag from A

    uint8_t carry = memory->getCFlag() ? 1 : 0;
    int result = memory->getA();
    result -= memory->getD();
	result -= carry;

    memory->setCFlag((memory->getD() + carry) > memory->getA());
    memory->setHFlag(((memory->getD() & 0x0F) + carry) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setA(result & 0xFF);
    memory->setZFlag(memory->getA() == 0);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode9B()
{
	//Sub E and Carry flag from A

    uint8_t carry = memory->getCFlag() ? 1 : 0;
    int result = memory->getA();
    result -= memory->getE();
	result -= carry;

    memory->setCFlag((memory->getE() + carry) > memory->getA());
    memory->setHFlag(((memory->getE() & 0x0F) + carry) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setA(result & 0xFF);
    memory->setZFlag(memory->getA() == 0);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode9C()
{
	//Sub H and Carry flag from A

    uint8_t carry = memory->getCFlag() ? 1 : 0;
    int result = memory->getA();
    result -= memory->getH();
	result -= carry;

    memory->setCFlag((memory->getH() + carry) > memory->getA());
    memory->setHFlag(((memory->getH() & 0x0F) + carry) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setA(result & 0xFF);
    memory->setZFlag(memory->getA() == 0);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode9D()
{
	//Sub L and Carry flag from A

    uint8_t carry = memory->getCFlag() ? 1 : 0;
    int result = memory->getA();
    result -= memory->getL();
	result -= carry;

    memory->setCFlag((memory->getL() + carry) > memory->getA());
    memory->setHFlag(((memory->getL() & 0x0F) + carry) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setA(result & 0xFF);
    memory->setZFlag(memory->getA() == 0);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcode9E()
{
	//Sub data at HL and Carry flag from A

    uint8_t data = memory->readMemory(memory->getHL());
    uint8_t carry = memory->getCFlag() ? 1 : 0;
    int result = memory->getA();
	result -= data;
	result -= carry;

    memory->setCFlag((data + carry) > memory->getA());
    memory->setHFlag(((data & 0x0F) + carry) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setA(result & 0xFF);
    memory->setZFlag(memory->getA() == 0);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcode9F()
{
	//Sub A and Carry flag from A

    uint8_t carry = memory->getCFlag() ? 1 : 0;
    int result = memory->getA();
    result -= memory->getA();
	result -= carry;

    memory->setCFlag((memory->getA() + carry) > memory->getA());
    memory->setHFlag(((memory->getA() & 0x0F) + carry) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setA(result & 0xFF);
    memory->setZFlag(memory->getA() == 0);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcodeA0()
{
	//And B from A
    memory->setA(memory->getA() & memory->getB());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(true);
    memory->setCFlag(false);
}

void Cpu::opcodeA1()
{
	//And C from A
    memory->setA(memory->getA() & memory->getC());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(true);
    memory->setCFlag(false);
}

void Cpu::opcodeA2()
{
	//And D from A
    memory->setA(memory->getA() & memory->getD());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(true);
    memory->setCFlag(false);
}

void Cpu::opcodeA3()
{
	//And E from A
    memory->setA(memory->getA() & memory->getE());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(true);
    memory->setCFlag(false);
}

void Cpu::opcodeA4()
{
	//And H from A
    memory->setA(memory->getA() & memory->getH());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(true);
    memory->setCFlag(false);
}

void Cpu::opcodeA5()
{
	//And L from A
    memory->setA(memory->getA() & memory->getL());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(true);
    memory->setCFlag(false);
}

void Cpu::opcodeA6()
{
	//And (HL) from A
    memory->setA(memory->getA() & memory->readMemory(memory->getHL()));
	mClock += 2;
	tClock += 8;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(true);
    memory->setCFlag(false);
}

void Cpu::opcodeA7()
{
	//And A from A
    memory->setA(memory->getA() & memory->getA());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(true);
    memory->setCFlag(false);
}

void Cpu::opcodeA8()
{
	//XOR B from A
    memory->setA(memory->getA() ^ memory->getB());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeA9()
{
	//XOR C from A
    memory->setA(memory->getA() ^ memory->getC());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeAA()
{
	//XOR D from A
    memory->setA(memory->getA() ^ memory->getD());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeAB()
{
	//XOR E from A
    memory->setA(memory->getA() ^ memory->getE());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeAC()
{
	//XOR H from A
    memory->setA(memory->getA() ^ memory->getH());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeAD()
{
	//XOR L from A
    memory->setA(memory->getA() ^ memory->getL());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeAE()
{
	//XOR data at HL from A
    memory->setA(memory->getA() ^ memory->readMemory(memory->getHL()));
	mClock += 2;
	tClock += 8;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeAF()
{
	//XOR A from A
    memory->setA(memory->getA() ^ memory->getA());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeB0()
{
	//OR B from A
    memory->setA(memory->getA() | memory->getB());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeB1()
{
	//OR C from A
    memory->setA(memory->getA() | memory->getC());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeB2()
{
	//OR D from A
    memory->setA(memory->getA() | memory->getD());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeB3()
{
	//OR E from A
    memory->setA(memory->getA() | memory->getE());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeB4()
{
	//OR H from A
    memory->setA(memory->getA() | memory->getH());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeB5()
{
	//OR L from A
    memory->setA(memory->getA() | memory->getL());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeB6()
{
	//OR (HL) from A
    memory->setA(memory->getA() | memory->readMemory(memory->getHL()));
	mClock += 2;
	tClock += 8;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeB7()
{
	//OR A from A
    memory->setA(memory->getA() | memory->getA());
	mClock += 1;
	tClock += 4;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeB8()
{
	//Compare B with A

    int test = memory->getA() - memory->getB();

    memory->setZFlag(test == 0);
    memory->setNFlag(true);
    memory->setHFlag((test & 0xF) > (memory->getA() & 0xF));
    memory->setCFlag(test < 0);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcodeB9()
{
	//Compare C with A

    int test = memory->getA() - memory->getC();

    memory->setZFlag(test == 0);
    memory->setNFlag(true);
    memory->setHFlag((test & 0xF) > (memory->getA() & 0xF));
    memory->setCFlag(test < 0);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcodeBA()
{
	//Compare D with A
	
    int test = memory->getA() - memory->getD();

    memory->setZFlag(test == 0);
    memory->setNFlag(true);
    memory->setHFlag((test & 0xF) > (memory->getA() & 0xF));
    memory->setCFlag(test < 0);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcodeBB()
{
	//Compare E with A
	
    int test = memory->getA() - memory->getE();

    memory->setZFlag(test == 0);
    memory->setNFlag(true);
    memory->setHFlag((test & 0xF) > (memory->getA() & 0xF));
    memory->setCFlag(test < 0);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcodeBC()
{
	//Compare H with A
	
    int test = memory->getA() - memory->getH();

    memory->setZFlag(test == 0);
    memory->setNFlag(true);
    memory->setHFlag((test & 0xF) > (memory->getA() & 0xF));
    memory->setCFlag(test < 0);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcodeBD()
{
	//Compare L with A
	
    int test = memory->getA() - memory->getL();

    memory->setZFlag(test == 0);
    memory->setNFlag(true);
    memory->setHFlag((test & 0xF) > (memory->getA() & 0xF));
    memory->setCFlag(test < 0);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcodeBE()
{
	//Compare data at HL with A

    unsigned char n = memory->readMemory(memory->getHL());
    int test = memory->getA() - n;

    memory->setZFlag(test == 0);
    memory->setNFlag(true);
    memory->setHFlag((test & 0xF) > (memory->getA() & 0xF));
    memory->setCFlag(test < 0);

	mClock += 2;
	tClock += 8;

}

void Cpu::opcodeBF()
{
	//Compare A with A
	
    int test = memory->getA() - memory->getA();

    memory->setZFlag(test == 0);
    memory->setNFlag(true);
    memory->setHFlag((test & 0xF) > (memory->getA() & 0xF));
    memory->setCFlag(test < 0);

	mClock += 1;
	tClock += 4;
}

void Cpu::opcodeC0()
{
	//RET if Not Zero
    if (!memory->getZFlag())
	{
        memory->memoryPointer = (memory->readMemory(stackPointer + 1) << 8) | (memory->readMemory(stackPointer));
		stackPointer += 2;
		mClock += 5;
		tClock += 20;
	}
	else
	{
		mClock += 2;
		tClock += 8;
	}
}

void Cpu::opcodeC1()
{
	//POP into BC
    memory->setBC((memory->readMemory(stackPointer + 1) << 8) | (memory->readMemory(stackPointer)));
	stackPointer += 2;
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeC2(short nn)
{
	//Jump if Not Zero
    if (!memory->getZFlag())
	{
        memory->memoryPointer = nn;
		mClock += 4;
		tClock += 16;
	}
	else
	{
		mClock += 3;
		tClock += 12;
	}
}

void Cpu::opcodeC3(short nn)
{
	//Jump to NNNN
    memory->memoryPointer = nn;
	mClock += 4;
	tClock += 16;
}

void Cpu::opcodeC4(short nn)
{
	//Call nn if Not Zero
    if (!memory->getZFlag())
	{
		stackPointer -= 2;
        memory->writeMemory(stackPointer, memory->memoryPointer);
        memory->memoryPointer = nn;
		mClock += 6;
		tClock += 24;
	}
	else
	{
		mClock += 3;
		tClock += 12;
	}
}

void Cpu::opcodeC5()
{
	//Push BC
	stackPointer -= 2;
    memory->writeMemory(stackPointer, memory->getBC());
	mClock += 4;
	tClock += 16;
}

void Cpu::opcodeC6(unsigned char n)
{
	//Add byte to A
    int result = memory->getA() + n;

    memory->setHFlag((((memory->getA() & 0x0F) + (n & 0x0F)) & 0x10) > 0);
    memory->setA((uint8_t)(result & 0xFF));
    memory->setCFlag(result > 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeC7()
{
	//Reset to 00
	stackPointer -= 2;
    memory->writeMemory(stackPointer, memory->memoryPointer);
    memory->memoryPointer = 0x00;
	mClock += 4;
	tClock += 16;

}

void Cpu::opcodeC8()
{
	//Ret if Zero
    if (memory->getZFlag())
	{
        memory->memoryPointer = (memory->readMemory(stackPointer + 1) << 8) | (memory->readMemory(stackPointer));
		stackPointer += 2;
		mClock += 5;
		tClock += 20;
	}
	else
	{
		mClock += 2;
		tClock += 8;
	}
}

void Cpu::opcodeC9()
{
	//Ret
    memory->memoryPointer = (memory->readMemory(stackPointer + 1) << 8) | (memory->readMemory(stackPointer));
	stackPointer += 2;
	mClock += 4;
	tClock += 16;
}

void Cpu::opcodeCA(short nn)
{
	//Jump to nn if Zero
    if (memory->getZFlag())
	{
        memory->memoryPointer = nn;
		mClock += 4;
		tClock += 16;
	}
	else
	{
		mClock += 3;
		tClock += 12;
	}
}

void Cpu::opcodeCC(short nn)
{
	//Call nn if Zero
    if (memory->getZFlag())
	{
		stackPointer -= 2;
        memory->writeMemory(stackPointer, memory->memoryPointer);
        memory->memoryPointer = nn;
		mClock += 6;
		tClock += 24;
	}
	else
	{
		mClock += 3;
		tClock += 12;
	}
}

void Cpu::opcodeCD(short nn)
{
	//Call nn
	stackPointer -= 2;
    memory->writeMemory(stackPointer, memory->memoryPointer);
    memory->memoryPointer = nn;
	mClock += 6;
	tClock += 24;
}

void Cpu::opcodeCE(unsigned char n)
{
	//Add n and Carry flag to A

    int carry = memory->getCFlag() ? 1 : 0;
    int result = memory->getA() + n + carry;

    memory->setHFlag((((memory->getA() & 0x0F) + (n & 0x0F) + carry) & 0x10) > 0);
    memory->setCFlag(result > 0xFF);
    memory->setA(result & 0xFF);
    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCF()
{
	//Reset to 08
	stackPointer -= 2;
    memory->writeMemory(stackPointer, memory->memoryPointer);
    memory->memoryPointer = 0x08;
	mClock += 4;
	tClock += 16;
}

void Cpu::opcodeD0()
{
	//Ret if not Carry
    if (!memory->getCFlag())
	{
        memory->memoryPointer = (memory->readMemory(stackPointer + 1) << 8) | (memory->readMemory(stackPointer));
		stackPointer += 2;
		mClock += 5;
		tClock += 20;
	}
	else
	{
		mClock += 2;
		tClock += 8;
	}
}

void Cpu::opcodeD1()
{
	//POP DE
    memory->setDE((memory->readMemory(stackPointer + 1) << 8) | (memory->readMemory(stackPointer)));
	stackPointer += 2;
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeD2(short nn)
{
	//Jump to nn if not Carry
    if (!memory->getCFlag())
	{
        memory->memoryPointer = nn;
		mClock += 4;
		tClock += 16;
	}
	else
	{
		mClock += 3;
		tClock += 12;
	}
}

//Opcode D3 does not exist?

void Cpu::opcodeD4(short nn)
{
	//Call nn if Not Carry
    if (!memory->getCFlag())
	{
		stackPointer -= 2;
        memory->writeMemory(stackPointer, memory->memoryPointer);
        memory->memoryPointer = nn;
		mClock += 6;
		tClock += 24;
	}
	else
	{
		mClock += 3;
		tClock += 12;
	}
}

void Cpu::opcodeD5()
{
	//Push DE
	stackPointer -= 2;
    memory->writeMemory(stackPointer, memory->getDE());
	mClock += 4;
	tClock += 16;
}

void Cpu::opcodeD6(unsigned char n)
{
	//Subtract n from A

    int result = memory->getA();
	result -= n;

    memory->setCFlag(n > memory->getA());
    memory->setHFlag((n & 0x0F) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setZFlag(result == 0);
    memory->setA(result);

	mClock += 2;
	tClock += 8;


}

void Cpu::opcodeD7()
{
	//Reset to 10
	stackPointer -= 2;
    memory->writeMemory(stackPointer, memory->memoryPointer);
    memory->memoryPointer = 0x10;
	mClock += 4;
	tClock += 16;
}

void Cpu::opcodeD8()
{
	//Ret if Carry
    if (memory->getCFlag())
	{
        memory->memoryPointer = (memory->readMemory(stackPointer + 1) << 8) | (memory->readMemory(stackPointer));
		stackPointer += 2;
		mClock += 5;
		tClock += 20;
	}
	else
	{
		mClock += 2;
		tClock += 8;
	}
}

void Cpu::opcodeD9()
{
	//Return and enable Interrupts
    memory->memoryPointer = (memory->readMemory(stackPointer + 1) << 8) | (memory->readMemory(stackPointer));
	stackPointer += 2;
	interruptsEnabled = true;
	mClock += 4;
	tClock += 16;
}

void Cpu::opcodeDA(short nn)
{
	//Jump to nn if Carry
    if (memory->getCFlag())
	{
        memory->memoryPointer = nn;
		mClock += 4;
		tClock += 16;
	}
	else
	{
		mClock += 3;
		tClock += 12;
	}
}

//Opcode DB does not exist?

void Cpu::opcodeDC(short nn)
{
	//Call nn if Carry
    if (memory->getCFlag())
	{
		stackPointer -= 2;
        memory->writeMemory(stackPointer, memory->memoryPointer);
        memory->memoryPointer = nn;
		mClock += 6;
		tClock += 24;
	}
	else
	{
		mClock += 3;
		tClock += 12;
	}
}

//Opcode DD does not exist?

void Cpu::opcodeDE(unsigned char n)
{
	//Sub n and Carry flag from A

    uint8_t carry = memory->getCFlag()? 1: 0;
    int result = memory->getA();
	result -= n;
	result -= carry;

    memory->setCFlag((n + carry) > memory->getA());
    memory->setHFlag(((n & 0x0F) + carry) > (memory->getA() & 0x0F));
    memory->setNFlag(true);
    memory->setA(result & 0xFF);
    memory->setZFlag(memory->getA() == 0);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeDF()
{
	//Reset to 18
	stackPointer -= 2;
    memory->writeMemory(stackPointer, memory->memoryPointer);
    memory->memoryPointer = 0x18;
	mClock += 4;
	tClock += 16;
}

void Cpu::opcodeE0(unsigned char n)
{
	//Load A into address at (FF00 + n)
    memory->writeMemory(0xFF00 + n, memory->getA());
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeE1()
{
	//Pop HL
    memory->setHL((memory->readMemory(stackPointer + 1) << 8) | (memory->readMemory(stackPointer)));
	stackPointer += 2;
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeE2()
{
	//Load A into address at (FF00 + C)
    memory->writeMemory(0xFF00 + memory->getC(), memory->getA());
	mClock += 2;
	tClock += 8;
}

//Opcode E3 does not exist?

//Opcode E4 does not exist?

void Cpu::opcodeE5()
{
	//Push HL
	stackPointer -= 2;
    memory->writeMemory(stackPointer, memory->getHL());
	mClock += 4;
	tClock += 16;
}

void Cpu::opcodeE6(unsigned char n)
{
	//And n from A
    memory->setA(memory->getA() & n);
	mClock += 2;
	tClock += 8;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(true);
    memory->setCFlag(false);
}

void Cpu::opcodeE7()
{
	//Reset to 20
	stackPointer -= 2;
    memory->writeMemory(stackPointer, memory->memoryPointer);
    memory->memoryPointer = 0x20;
	mClock += 4;
	tClock += 16;
}

void Cpu::opcodeE8(signed char n)
{
	//Add n to Stack Pointer

	int result = stackPointer + n;

    memory->setCFlag((result & 0xFF) < (stackPointer & 0xFF));
    memory->setHFlag((result & 0x0F) < (stackPointer & 0x0F));
    memory->setZFlag(false);
    memory->setNFlag(false);

    memory->setStackPointer((uint16_t)(result & 0xFFFF));

	mClock += 4;
	tClock += 16;
}

void Cpu::opcodeE9()
{
	//Jump to HL
    memory->memoryPointer = memory->getHL();
	mClock += 1;
	tClock += 4;
}

void Cpu::opcodeEA(short nn)
{
	//Store A at short
    memory->writeMemory(nn, memory->getA());
	mClock += 4;
	tClock += 16;
}

//Opcode EB doesn't exist?

//Opcode EC doesn't exist?

//Opcode ED doesn't exist?

void Cpu::opcodeEE(unsigned char n)
{
	//XOR byte with A
    memory->setA(memory->getA() ^ n);
	mClock += 2;
	tClock += 8;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeEF()
{
	//Reset to 28
	stackPointer -= 2;
    memory->writeMemory(stackPointer, memory->memoryPointer);
    memory->memoryPointer = 0x28;
	mClock += 4;
	tClock += 16;
}

void Cpu::opcodeF0(unsigned char n)
{
	//Load data at (FF00 + n) into A
    memory->setA(memory->readMemory(0xFF00 + n));
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeF1()
{
	//Pop AF
    memory->setAF((memory->readMemory(stackPointer + 1) << 8) | (memory->readMemory(stackPointer)));
	stackPointer += 2;
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeF2()
{
	//Load data at (FF00 + C) into A
    memory->setA(memory->readMemory(0xFF00 + memory->getC()));
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeF3()
{
	//Disable Interrupts
	interruptsEnabled = false;
	mClock += 1;
	tClock += 4;
}

//Opcode F4 doesn't exist?

void Cpu::opcodeF5()
{
	//Push AF
	stackPointer -= 2;
    memory->writeMemory(stackPointer, memory->getAF());
	mClock += 4;
	tClock += 16;
}

void Cpu::opcodeF6(unsigned char n)
{
	//OR byte with A
    memory->setA(memory->getA() | n);
	mClock += 2;
	tClock += 8;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeF7()
{
	//Reset to 30
	stackPointer -= 2;
    memory->writeMemory(stackPointer, memory->memoryPointer);
    memory->memoryPointer = 0x30;
	mClock += 4;
	tClock += 16;
}

void Cpu::opcodeF8(unsigned char n)
{
	//Load SP + n into HL

	int result = stackPointer + (int8_t)n;

    memory->setCFlag((result & 0xFF) < (stackPointer & 0xFF));
    memory->setHFlag((result & 0x0F) < (stackPointer & 0x0F));
    memory->setZFlag(false);
    memory->setNFlag(false);

    memory->setHL((short)(result & 0xFFFF));

	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeF9()
{
	//Load SP into HL
    stackPointer = memory->getHL();
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeFA(short nn)
{
	//Load data at short into A
    memory->setA(memory->readMemory(nn));
	mClock += 4;
	tClock += 16;
}

void Cpu::opcodeFB()
{
	//Enable Interrupts
    core->enableInterruptsNextCycle = true;
	//interruptsEnabled = true;
	mClock += 1;
	tClock += 4;
}
//Opcode FC doesn't exist?

//Opcode FD doesn't exist?

void Cpu::opcodeFE(unsigned char n)
{
	//Compare n with A
    //byte test = memory->getA() - n;
	mClock += 2;
	tClock += 8;

    //memory->setZFlag((test == 0) ? 1 : 0);
    //memory->setNFlag(true);
    //memory->setHFlag((test > memory->getA()));
    //memory->setCFlag((test < 0) ? 1 : 0);

    memory->setZFlag((memory->getA() == n) ? 1 : 0);
    memory->setNFlag(true);
    memory->setHFlag(((memory->getA() & 0x0F) < (n & 0x0F)) ? 1 : 0);
    memory->setCFlag((memory->getA() < n) ? 1 : 0);
}

void Cpu::opcodeFF()
{
	//Reset to 38
    //beakStack[--stackPointer] = memory->memoryPointer;
    //memory->writeMemory(--stackPointer, memory->memoryPointer);
	stackPointer -= 2;
    memory->writeMemory(stackPointer, memory->memoryPointer);
    memory->memoryPointer = 0x38;
	mClock += 4;
	tClock += 16;
}

void Cpu::opcodeCB00()
{
	//Rotate B Left, put previous bit 7 into Carry flag

    memory->setB(rotateLeft(memory->getB()));

    memory->setCFlag(memory->getB() & 0x01);
    memory->setZFlag(memory->getB() == 0);


    //memory->setB (memory->getB() << 1);

	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB01()
{
	//Rotate C Left, put previous bit 7 into Carry flag

    memory->setC(rotateLeft(memory->getC()));

    memory->setCFlag(memory->getC() & 0x01);
    memory->setZFlag(memory->getC() == 0);


    //memory->setC(memory->getC() << 1);

	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB02()
{
	//Rotate D Left, put previous bit 7 into Carry flag

    memory->setD(rotateLeft(memory->getD()));

    memory->setCFlag(memory->getD() & 0x01);
    memory->setZFlag(memory->getD() == 0);


    //memory->setD(memory->getD() << 1);

	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB03()
{
	//Rotate E Left, put previous bit 7 into Carry flag

    memory->setE(rotateLeft(memory->getE()));

    memory->setCFlag(memory->getE() & 0x01);
    memory->setZFlag(memory->getE() == 0);


    //memory->setE(memory->getE() << 1);

	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB04()
{
	//Rotate H Left, put previous bit 7 into Carry flag

    memory->setH(rotateLeft(memory->getH()));

    memory->setCFlag(memory->getH() & 0x01);
    memory->setZFlag(memory->getH() == 0);


    //memory->setH(memory->getH() << 1);

	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB05()
{
	//Rotate L Left, put previous bit 7 into Carry flag

    memory->setL(rotateLeft(memory->getL()));

    memory->setCFlag(memory->getL() & 0x01);
    memory->setZFlag(memory->getL() == 0);


    //memory->setL(memory->getL() << 1);

	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB06()
{
	//Rotate data in HL Left, put previous bit 7 into Carry flag

    memory->writeMemory(memory->getHL(), rotateLeft(memory->readMemory(memory->getHL())));

    memory->setCFlag(memory->readMemory(memory->getHL()) & 0x01);
    memory->setZFlag(memory->readMemory(memory->getHL()) == 0);


    //memory->writeMemory(memory->getHL(), (byte)(memory->readMemory(memory->getHL()) << 1));

	mClock += 3;
	tClock += 12;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB07()
{
	//Rotate A Left, put previous bit 7 into Carry flag

    memory->setA(rotateLeft(memory->getA()));

    memory->setCFlag(memory->getA() & 0x01);
    memory->setZFlag(memory->getA() == 0);


    //memory->setA(memory->getA() << 1);

	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB08()
{
	//Rotate B Right, put previous bit 0 into Carry flag

    memory->setB(rotateRight(memory->getB()));

    memory->setCFlag(((memory->getB() & 0x80) >> 7) > 0);
    memory->setZFlag(memory->getB() == 0);


    //memory->setB(memory->getB() >> 1);

	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB09()
{
	//Rotate C Right, put previous bit 0 into Carry flag

    memory->setC(rotateRight(memory->getC()));

    memory->setCFlag(((memory->getC() & 0x80) >> 7) > 0);
    memory->setZFlag(memory->getC() == 0);


    //memory->setC(memory->getC() >> 1);

	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB0A()
{
	//Rotate D Right, put previous bit 0 into Carry flag

    memory->setD(rotateRight(memory->getD()));

    memory->setCFlag(((memory->getD() & 0x80) >> 7) > 0);
    memory->setZFlag(memory->getD() == 0);

    //memory->setD(memory->getD() >> 1);

	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB0B()
{
	//Rotate E Right, put previous bit 0 into Carry flag

    memory->setE(rotateRight(memory->getE()));

    memory->setCFlag(((memory->getE() & 0x80) >> 7) > 0);
    memory->setZFlag(memory->getE() == 0);


    //memory->setE(memory->getE() >> 1);

	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB0C()
{
	//Rotate H Right, put previous bit 0 into Carry flag

    memory->setH(rotateRight(memory->getH()));

    memory->setCFlag(((memory->getH() & 0x80) >> 7) > 0);
    memory->setZFlag(memory->getH() == 0);

    //memory->setH(memory->getH() >> 1);

	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB0D()
{
	//Rotate L Right, put previous bit 0 into Carry flag

    memory->setL(rotateRight(memory->getL()));

    memory->setCFlag(((memory->getL() & 0x80) >> 7) > 0);
    memory->setZFlag(memory->getL() == 0);


    //memory->setL(memory->getL() >> 1);

	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB0E()
{
	//Rotate data at HL Right, put previous bit 0 into Carry flag

    memory->writeMemory(memory->getHL(), (unsigned char)(rotateRight(memory->readMemory(memory->getHL()))));

    memory->setB(rotateRight(memory->getB()));
    memory->setCFlag(((memory->readMemory(memory->getHL()) & 0x80) >> 7) > 0);
    memory->setZFlag(memory->readMemory(memory->getHL()) == 0);


    //memory->writeMemory(memory->getHL(), (byte)(memory->readMemory(memory->getHL()) >> 1));

	mClock += 3;
	tClock += 12;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB0F()
{
	//Rotate A Right, put previous bit 0 into Carry flag (Does not Or C flag in)

    memory->setA(rotateRight(memory->getA()));

    memory->setCFlag(((memory->getA() & 0x80) >> 7) > 0);
    memory->setZFlag(memory->getA() == 0);


    //memory->setA(memory->getA() >> 1);

	mClock += 2;
	tClock += 8;

    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB10()
{
	//Rotate B Left
    //memory->setB(rotateLeft(memory->getB()));

    unsigned char oldBit = (memory->getB() & 0x80) >> 7;
    memory->setB((memory->getB() << 1) | (unsigned char)memory->getCFlag());
    memory->setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getB() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB11()
{
	//Rotate C Left
    //memory->setC(rotateLeft(memory->getC()));

    unsigned char oldBit = (memory->getC() & 0x80) >> 7;
    memory->setC((memory->getC() << 1) | (unsigned char)memory->getCFlag());
    memory->setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getC() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB12()
{
	//Rotate D Left

    unsigned char oldBit = (memory->getD() & 0x80) >> 7;
    memory->setD((memory->getD() << 1) | (unsigned char)memory->getCFlag());
    memory->setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getD() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB13()
{
	//Rotate E Left

    unsigned char oldBit = (memory->getE() & 0x80) >> 7;
    memory->setE((memory->getE() << 1) | (unsigned char)memory->getCFlag());
    memory->setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getE() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB14()
{
	//Rotate H Left

    unsigned char oldBit = (memory->getH() & 0x80) >> 7;
    memory->setH((memory->getH() << 1) | (unsigned char)memory->getCFlag());
    memory->setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getH() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB15()
{
	//Rotate L Left

    unsigned char oldBit = (memory->getL() & 0x80) >> 7;
    memory->setL((memory->getL() << 1) | (unsigned char)memory->getCFlag());
    memory->setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getL() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB16()
{
	//Rotate data at HL Left

    unsigned char oldBit = (memory->readMemory(memory->getHL()) & 0x80) >> 7;
    memory->writeMemory(memory->getHL(), (unsigned char)((memory->readMemory(memory->getHL()) << 1) | (unsigned char)memory->getCFlag()));
    memory->setCFlag(oldBit > 0);

	mClock += 3;
	tClock += 12;

    memory->setZFlag(memory->readMemory(memory->getHL()) == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB17()
{
	//Rotate A Left

    unsigned char oldBit = (memory->getA() & 0x80) >> 7;
    memory->setA((memory->getA() << 1) | (unsigned char)memory->getCFlag());
    memory->setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB18()
{
	//Rotate B Right

    unsigned char oldBit = (memory->getB() & 0x01);
    memory->setB((memory->getB() >> 1) | (memory->getCFlag() << 7));
    memory->setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getB() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);

}

void Cpu::opcodeCB19()
{
	//Rotate C Right

    unsigned char oldBit = (memory->getC() & 0x01);
    memory->setC((memory->getC() >> 1) | (memory->getCFlag() << 7));
    memory->setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getC() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB1A()
{
	//Rotate D Right

    unsigned char oldBit = (memory->getD() & 0x01);
    memory->setD((memory->getD() >> 1) | (memory->getCFlag() << 7));
    memory->setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getD() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB1B()
{
	//Rotate E Right

    unsigned char oldBit = (memory->getE() & 0x01);
    memory->setE((memory->getE() >> 1) | (memory->getCFlag() << 7));
    memory->setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getE() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB1C()
{
	//Rotate H Right

    unsigned char oldBit = (memory->getH() & 0x01);
    memory->setH((memory->getH() >> 1) | (memory->getCFlag() << 7));
    memory->setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getH() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB1D()
{
	//Rotate L Right

    unsigned char oldBit = (memory->getL() & 0x01);
    memory->setL((memory->getL() >> 1) | (memory->getCFlag() << 7));
    memory->setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getL() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB1E()
{
	//Rotate/Shift HL Right

    unsigned char oldBit = (memory->readMemory(memory->getHL()) & 0x01);
    memory->writeMemory(memory->getHL(), (unsigned char)((memory->readMemory(memory->getHL()) >> 1) | (memory->getCFlag() << 7)));
    memory->setCFlag(oldBit > 0);

	mClock += 3;
	tClock += 12;

    memory->setZFlag(memory->readMemory(memory->getHL()) == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB1F()
{
	//Rotate A Right

    unsigned char oldBit = (memory->getA() & 0x01);
    memory->setA((memory->getA() >> 1) | (memory->getCFlag() << 7));
    memory->setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB20()
{
	//Shift B Left - Set Carry to old Bit 7

    memory->setCFlag(((memory->getB() & 0x80) >> 7) > 0);
    memory->setB(memory->getB() << 1);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getB() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB21()
{
	//Shift C Left - Set Carry to old Bit 7

    memory->setCFlag(((memory->getC() & 0x80) >> 7) > 0);
    memory->setC(memory->getC() << 1);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getC() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB22()
{
	//Shift D Left - Set Carry to old Bit 7

    memory->setCFlag(((memory->getD() & 0x80) >> 7) > 0);
    memory->setD(memory->getD() << 1);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getD() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB23()
{
	//Shift E Left - Set Carry to old Bit 7

    memory->setCFlag(((memory->getE() & 0x80) >> 7) > 0);
    memory->setE(memory->getE() << 1);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getE() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB24()
{
	//Shift H Left - Set Carry to old Bit 7

    memory->setCFlag(((memory->getH() & 0x80) >> 7) > 0);
    memory->setH(memory->getH() << 1);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getH() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB25()
{
	//Shift L Left - Set Carry to old Bit 7

    memory->setCFlag(((memory->getL() & 0x80) >> 7) > 0);
    memory->setL(memory->getL() << 1);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getL() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB26()
{
	//Shift data at HL Left - Set Carry to old Bit 7

    memory->setCFlag(((memory->readMemory(memory->getHL()) & 0x80) >> 7) > 0);
    memory->writeMemory(memory->getHL(), (unsigned char)(memory->readMemory(memory->getHL()) << 1));

	mClock += 3;
	tClock += 12;

    memory->setZFlag(memory->readMemory(memory->getHL()) == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB27()
{
	//Shift A Left - Set Carry to old Bit 7

    memory->setCFlag(((memory->getA() & 0x80) >> 7) > 0);
    memory->setA(memory->getA() << 1);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB28()
{
	//Shift B Right - Set Carry to old Bit 0

    unsigned char oldValue = memory->getB();
    memory->setCFlag((oldValue & 0x01) > 0);
    memory->setB((unsigned char)((oldValue & 0x80) | (oldValue >> 1)));

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getB() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB29()
{
	//Shift C Right - Set Carry to old Bit 0

    unsigned char oldValue = memory->getC();
    memory->setCFlag((oldValue & 0x01) > 0);
    memory->setC((unsigned char)((oldValue & 0x80) | (oldValue >> 1)));

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getC() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB2A()
{
	//Shift D Right - Set Carry to old Bit 0

    unsigned char oldValue = memory->getD();
    memory->setCFlag((oldValue & 0x01) > 0);
    memory->setD((unsigned char)((oldValue & 0x80) | (oldValue >> 1)));

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getD() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB2B()
{
	//Shift E Right - Set Carry to old Bit 0

    unsigned char oldValue = memory->getE();
    memory->setCFlag((oldValue & 0x01) > 0);
    memory->setE((unsigned char)((oldValue & 0x80) | (oldValue >> 1)));

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getE() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB2C()
{
	//Shift H Right - Set Carry to old Bit 0

    unsigned char oldValue = memory->getH();
    memory->setCFlag((oldValue & 0x01) > 0);
    memory->setH((unsigned char)((oldValue & 0x80) | (oldValue >> 1)));

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getH() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB2D()
{
	//Shift L Right - Set Carry to old Bit 0

    unsigned char oldValue = memory->getL();
    memory->setCFlag((oldValue & 0x01) > 0);
    memory->setL((unsigned char)((oldValue & 0x80) | (oldValue >> 1)));

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getL() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB2E()
{
	//Shift data at HL Right - Set Carry to old Bit 0

    unsigned char oldValue = memory->readMemory(memory->getHL());
    memory->setCFlag((oldValue & 0x01) > 0);
    memory->writeMemory(memory->getHL(), ((unsigned char)((oldValue & 0x80) | (oldValue >> 1))));

	mClock += 3;
	tClock += 12;

    memory->setZFlag(memory->readMemory(memory->getHL()) == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB2F()
{
	//Shift A Right - Set Carry to old Bit 0

    unsigned char oldValue = memory->getA();
    memory->setCFlag((oldValue & 0x01) > 0);
    memory->setA((unsigned char)((oldValue & 0x80) | (oldValue >> 1)));

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB30()
{
	//Swap nibbles in B
    unsigned char b = memory->getB();
	b = ((b & 0x0F) << 4) | ((b & 0xF0) >> 4);
    memory->setB(b);
	mClock += 2;
	tClock += 8;

    memory->setZFlag((memory->getB() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeCB31()
{
	//Swap nibbles in C
    unsigned char c = memory->getC();
	c = ((c & 0x0F) << 4) | ((c & 0xF0) >> 4);
    memory->setC(c);
	mClock += 2;
	tClock += 8;

    memory->setZFlag((memory->getC() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeCB32()
{
	//Swap nibbles in D
    unsigned char d = memory->getD();
	d = ((d & 0x0F) << 4) | ((d & 0xF0) >> 4);
    memory->setD(d);
	mClock += 2;
	tClock += 8;

    memory->setZFlag((memory->getD() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeCB33()
{
	//Swap nibbles in E
    unsigned char e = memory->getE();
	e = ((e & 0x0F) << 4) | ((e & 0xF0) >> 4);
    memory->setE(e);
	mClock += 2;
	tClock += 8;

    memory->setZFlag((memory->getE() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeCB34()
{
	//Swap nibbles in H
    unsigned char h = memory->getH();
	h = ((h & 0x0F) << 4) | ((h & 0xF0) >> 4);
    memory->setH(h);
	mClock += 2;
	tClock += 8;

    memory->setZFlag((memory->getH() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeCB35()
{
	//Swap nibbles in L
    unsigned char l = memory->getL();
	l = ((l & 0x0F) << 4) | ((l & 0xF0) >> 4);
    memory->setL(l);
	mClock += 2;
	tClock += 8;

    memory->setZFlag((memory->getL() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}


void Cpu::opcodeCB36()
{
	//Swap nibbles in memory at HL
    short hl = memory->getHL();
    unsigned char hlData = memory->readMemory(hl);
	hlData = ((hlData & 0x0F) << 4) | ((hlData & 0xF0) >> 4);
    memory->writeMemory(hl, hlData);
	mClock += 3;
	tClock += 12;

    memory->setZFlag((memory->readMemory(hl) == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeCB37()
{
	//Swap nibbles in A
    unsigned char a = memory->getA();
	a = ((a & 0x0F) << 4) | ((a & 0xF0) >> 4);
    memory->setA(a);
	mClock += 2;
	tClock += 8;

    memory->setZFlag((memory->getA() == 0) ? 1 : 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
    memory->setCFlag(false);
}

void Cpu::opcodeCB38()
{
	//Shift B Right
    memory->setCFlag(memory->getB() & 0x01);
    memory->setB(memory->getB() >> 1);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getB() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB39()
{
	//Shift C Right
    memory->setCFlag(memory->getC() & 0x01);
    memory->setC(memory->getC() >> 1);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getC() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB3A()
{
	//Shift D Right
    memory->setCFlag(memory->getD() & 0x01);
    memory->setD(memory->getD() >> 1);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getD() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB3B()
{
	//Shift E Right
    memory->setCFlag(memory->getE() & 0x01);
    memory->setE(memory->getE() >> 1);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getE() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB3C()
{
	//Shift H Right
    memory->setCFlag(memory->getH() & 0x01);
    memory->setH(memory->getH() >> 1);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getH() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB3D()
{
	//Shift L Right
    memory->setCFlag(memory->getL() & 0x01);
    memory->setL(memory->getL() >> 1);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getL() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB3E()
{
	//Shift data at HL Right
    memory->setCFlag(memory->readMemory(memory->getHL()) & 0x01);
    memory->writeMemory(memory->getHL(), (unsigned char)(memory->readMemory(memory->getHL()) >> 1));

	mClock += 3;
	tClock += 12;

    memory->setZFlag(memory->readMemory(memory->getHL()) == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB3F()
{
	//Shift A Right
    memory->setCFlag(memory->getA() & 0x01);
    memory->setA(memory->getA() >> 1);

	mClock += 2;
	tClock += 8;

    memory->setZFlag(memory->getA() == 0);
    memory->setNFlag(false);
    memory->setHFlag(false);
}

void Cpu::opcodeCB40()
{
	//Test bit 0 in B
    memory->setZFlag(((memory->getB() & 0x01) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB41()
{
	//Test bit 0 in C
    memory->setZFlag(((memory->getC() & 0x01) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB42()
{
	//Test bit 0 in D
    memory->setZFlag(((memory->getD() & 0x01) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB43()
{
	//Test bit 0 in E
    memory->setZFlag(((memory->getE() & 0x01) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB44()
{
	//Test bit 0 in H
    memory->setZFlag(((memory->getH() & 0x01) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB45()
{
	//Test bit 0 in L
    memory->setZFlag(((memory->getL() & 0x01) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB46()
{
	//Test bit 0 in data at HL
    short hl = memory->getHL();
    memory->setZFlag(((memory->readMemory(hl) & 0x01) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCB47()
{
	//Test bit 0 in A
    memory->setZFlag(((memory->getA() & 0x01) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB48()
{
	//Test bit 1 in B
    memory->setZFlag((((memory->getB() & 0x02) >> 1) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB49()
{
	//Test bit 1 in C
    memory->setZFlag((((memory->getC() & 0x02) >> 1) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB4A()
{
	//Test bit 1 in D
    memory->setZFlag((((memory->getD() & 0x02) >> 1) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB4B()
{
	//Test bit 1 in E
    memory->setZFlag((((memory->getE() & 0x02) >> 1) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB4C()
{
	//Test bit 1 in H
    memory->setZFlag((((memory->getH() & 0x02) >> 1) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB4D()
{
	//Test bit 1 in L
    memory->setZFlag((((memory->getL() & 0x02) >> 1) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB4E()
{
	//Test bit 1 in data at HL
    short hl = memory->getHL();
    memory->setZFlag((((memory->readMemory(hl) & 0x02) >> 1) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCB4F()
{
	//Test bit 1 in A
    memory->setZFlag((((memory->getA() & 0x02) >> 1) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB50()
{
	//Test bit 2 in B
    memory->setZFlag((((memory->getB() & 0x04) >> 2) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB51()
{
	//Test bit 2 in C
    memory->setZFlag((((memory->getC() & 0x04) >> 2) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB52()
{
	//Test bit 2 in D
    memory->setZFlag((((memory->getD() & 0x04) >> 2) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB53()
{
	//Test bit 2 in E
    memory->setZFlag((((memory->getE() & 0x04) >> 2) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB54()
{
	//Test bit 2 in H
    memory->setZFlag((((memory->getH() & 0x04) >> 2) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB55()
{
	//Test bit 2 in L
    memory->setZFlag((((memory->getL() & 0x04) >> 2) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB56()
{
	//Test bit 2 in data at HL
    short hl = memory->getHL();
    memory->setZFlag((((memory->readMemory(hl) & 0x04) >> 2) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCB57()
{
	//Test bit 2 in A
    memory->setZFlag((((memory->getA() & 0x04) >> 2) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB58()
{
	//Test bit 3 in B
    memory->setZFlag((((memory->getB() & 0x08) >> 3) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB59()
{
	//Test bit 3 in C
    memory->setZFlag((((memory->getC() & 0x08) >> 3) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB5A()
{
	//Test bit 3 in D
    memory->setZFlag((((memory->getD() & 0x08) >> 3) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB5B()
{
	//Test bit 3 in E
    memory->setZFlag((((memory->getE() & 0x08) >> 3) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB5C()
{
	//Test bit 3 in H
    memory->setZFlag((((memory->getH() & 0x08) >> 3) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB5D()
{
	//Test bit 3 in L
    memory->setZFlag((((memory->getL() & 0x08) >> 3) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB5E()
{
	//Test bit 3 in data at HL
    short hl = memory->getHL();
    memory->setZFlag((((memory->readMemory(hl) & 0x08) >> 3) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCB5F()
{
	//Test bit 3 in A
    memory->setZFlag((((memory->getA() & 0x08) >> 3) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB60()
{
	//Test bit 4 in B
    memory->setZFlag((((memory->getB() & 0x10) >> 4) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB61()
{
	//Test bit 4 in C
    memory->setZFlag((((memory->getC() & 0x10) >> 4) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB62()
{
	//Test bit 4 in D
    memory->setZFlag((((memory->getD() & 0x10) >> 4) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB63()
{
	//Test bit 4 in E
    memory->setZFlag((((memory->getE() & 0x10) >> 4) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB64()
{
	//Test bit 4 in H
    memory->setZFlag((((memory->getH() & 0x10) >> 4) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB65()
{
	//Test bit 4 in L
    memory->setZFlag((((memory->getL() & 0x10) >> 4) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB66()
{
	//Test bit 4 in data at HL
    short hl = memory->getHL();
    memory->setZFlag((((memory->readMemory(hl) & 0x10) >> 4) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCB67()
{
	//Test bit 4 in A
    memory->setZFlag((((memory->getA() & 0x10) >> 4) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB68()
{
	//Test bit 5 in B
    memory->setZFlag((((memory->getB() & 0x20) >> 5) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB69()
{
	//Test bit 5 in C
    memory->setZFlag((((memory->getC() & 0x20) >> 5) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB6A()
{
	//Test bit 5 in D
    memory->setZFlag((((memory->getD() & 0x20) >> 5) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB6B()
{
	//Test bit 5 in E
    memory->setZFlag((((memory->getE() & 0x20) >> 5) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB6C()
{
	//Test bit 5 in H
    memory->setZFlag((((memory->getH() & 0x20) >> 5) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB6D()
{
	//Test bit 5 in L
    memory->setZFlag((((memory->getL() & 0x20) >> 5) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB6E()
{
	//Test bit 5 in data at HL
    short hl = memory->getHL();
    memory->setZFlag((((memory->readMemory(hl) & 0x20) >> 5) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCB6F()
{
	//Test bit 5 in A
    memory->setZFlag((((memory->getA() & 0x20) >> 5) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB70()
{
	//Test bit 6 in B
    memory->setZFlag((((memory->getB() & 0x40) >> 6) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB71()
{
	//Test bit 6 in C
    memory->setZFlag((((memory->getC() & 0x40) >> 6) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB72()
{
	//Test bit 6 in D
    memory->setZFlag((((memory->getD() & 0x40) >> 6) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB73()
{
	//Test bit 6 in E
    memory->setZFlag((((memory->getE() & 0x40) >> 6) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB74()
{
	//Test bit 6 in H
    memory->setZFlag((((memory->getH() & 0x40) >> 6) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB75()
{
	//Test bit 6 in L
    memory->setZFlag((((memory->getL() & 0x40) >> 6) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB76()
{
	//Test bit 6 in data at HL
    short hl = memory->getHL();
    memory->setZFlag((((memory->readMemory(hl) & 0x40) >> 6) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCB77()
{
	//Test bit 6 in A
    memory->setZFlag((((memory->getA() & 0x40) >> 6) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB78()
{
	//Test bit 7 in B
    memory->setZFlag((((memory->getB() & 0x80) >> 7) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB79()
{
	//Test bit 7 in C
    memory->setZFlag((((memory->getC() & 0x80) >> 7) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB7A()
{
	//Test bit 7 in D
    memory->setZFlag((((memory->getD() & 0x80) >> 7) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB7B()
{
	//Test bit 7 in E
    memory->setZFlag((((memory->getE() & 0x80) >> 7) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB7C()
{
	//Test bit 7 in H
    memory->setZFlag((((memory->getH() & 0x80) >> 7) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB7D()
{
	//Test bit 7 in L
    memory->setZFlag((((memory->getL() & 0x80) >> 7) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB7E()
{
	//Test bit 7 in data at HL
    short hl = memory->getHL();
    memory->setZFlag((((memory->readMemory(hl) & 0x80) >> 7) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCB7F()
{
	//Test bit 7 in A
    memory->setZFlag((((memory->getA() & 0x80) >> 7) == 0) ? true : false);
    memory->setNFlag(false);
    memory->setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB80()
{
	//Reset bit 0 in B
    memory->setB(memory->getB() & 0xFE); //Masks off left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB81()
{
	//Reset bit 0 in C
    memory->setC(memory->getC() & 0xFE); //Masks off left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB82()
{
	//Reset bit 0 in D
    memory->setD(memory->getD() & 0xFE); //Masks off left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB83()
{
	//Reset bit 0 in E
    memory->setE(memory->getE() & 0xFE); //Masks off left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB84()
{
	//Reset bit 0 in H
    memory->setH(memory->getH() & 0xFE); //Masks off left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB85()
{
	//Reset bit 0 of data at L
    memory->setL(memory->getL() & 0xFE); //Masks off left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB86()
{
	//Reset bit 0 in HL
    short hl = memory->getHL();
    memory->writeMemory(hl, (unsigned char)(memory->readMemory(hl) & 0xFE)); //Masks off left most bit
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCB87()
{
	//Reset bit 0 of data at A
    memory->setA(memory->getA() & 0xFE); //Masks off left most bit
	mClock += 2;
	tClock += 8;
}


void Cpu::opcodeCB88()
{
	//Reset bit 1 in B
    memory->setB(memory->getB() & 0xFD); //Masks off second to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB89()
{
	//Reset bit 1 in C
    memory->setC(memory->getC() & 0xFD); //Masks off second to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB8A()
{
	//Reset bit 1 in D
    memory->setD(memory->getD() & 0xFD); //Masks off second to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB8B()
{
	//Reset bit 1 in E
    memory->setE(memory->getE() & 0xFD); //Masks off second to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB8C()
{
	//Reset bit 1 in H
    memory->setH(memory->getH() & 0xFD); //Masks off second to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB8D()
{
	//Reset bit 1 in L
    memory->setL(memory->getL() & 0xFD); //Masks off second to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB8E()
{
	//Reset bit 1 in HL
    short hl = memory->getHL();
    memory->writeMemory(hl, (unsigned char)(memory->readMemory(hl) & 0xFD)); //Masks off left most bit
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCB8F()
{
	//Reset bit 1 in A
    memory->setA(memory->getA() & 0xFD); //Masks off second to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB90()
{
	//Reset bit 2 in B
    memory->setB(memory->getB() & 0xFB); //Masks off third to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB91()
{
	//Reset bit 2 in C
    memory->setC(memory->getC() & 0xFB); //Masks off third to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB92()
{
	//Reset bit 2 in D
    memory->setD(memory->getD() & 0xFB); //Masks off third to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB93()
{
	//Reset bit 2 in E
    memory->setE(memory->getE() & 0xFB); //Masks off third to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB94()
{
	//Reset bit 2 in H
    memory->setH(memory->getH() & 0xFB); //Masks off third to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB95()
{
	//Reset bit 2 in L
    memory->setL(memory->getL() & 0xFB); //Masks off third to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB96()
{
	//Reset bit 2 in HL
    short hl = memory->getHL();
    memory->writeMemory(hl, (unsigned char)(memory->readMemory(hl) & 0xFB)); //Masks off left most bit
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCB97()
{
	//Reset bit 2 in A
    memory->setA(memory->getA() & 0xFB); //Masks off third to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB98()
{
	//Reset bit 3 in B
    memory->setB(memory->getB() & 0xF7); //Masks off fourth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB99()
{
	//Reset bit 3 in C
    memory->setC(memory->getC() & 0xF7); //Masks off fourth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB9A()
{
	//Reset bit 3 in D
    memory->setD(memory->getD() & 0xF7); //Masks off fourth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB9B()
{
	//Reset bit 3 in E
    memory->setE(memory->getE() & 0xF7); //Masks off fourth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB9C()
{
	//Reset bit 3 in H
    memory->setH(memory->getH() & 0xF7); //Masks off fourth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB9D()
{
	//Reset bit 3 in L
    memory->setL(memory->getL() & 0xF7); //Masks off fourth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCB9E()
{
	//Reset bit 3 in HL
    short hl = memory->getHL();
    memory->writeMemory(hl, (unsigned char)(memory->readMemory(hl) & 0xF7)); //Masks off left most bit
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCB9F()
{
	//Reset bit 3 in A
    memory->setA(memory->getA() & 0xF7); //Masks off fourth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBA0()
{
	//Reset bit 4 in B
    memory->setB(memory->getB() & 0xEF); //Masks off fifth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBA1()
{
	//Reset bit 4 in C
    memory->setC(memory->getC() & 0xEF); //Masks off fifth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBA2()
{
	//Reset bit 4 in D
    memory->setD(memory->getD() & 0xEF); //Masks off fifth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBA3()
{
	//Reset bit 4 in E
    memory->setE(memory->getE() & 0xEF); //Masks off fifth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBA4()
{
	//Reset bit 4 in H
    memory->setH(memory->getH() & 0xEF); //Masks off fifth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBA5()
{
	//Reset bit 4 in L
    memory->setL(memory->getL() & 0xEF); //Masks off fifth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBA6()
{
	//Reset bit 4 in HL
    short hl = memory->getHL();
    memory->writeMemory(hl, (unsigned char)(memory->readMemory(hl) & 0xEF)); //Masks off left most bit
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCBA7()
{
	//Reset bit 4 in A
    memory->setA(memory->getA() & 0xEF); //Masks off fifth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBA8()
{
	//Reset bit 5 in B
    memory->setB(memory->getB() & 0xDF); //Masks off sixth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBA9()
{
	//Reset bit 5 in C
    memory->setC(memory->getC() & 0xDF); //Masks off sixth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBAA()
{
	//Reset bit 5 in D
    memory->setD(memory->getD() & 0xDF); //Masks off sixth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBAB()
{
	//Reset bit 5 in E
    memory->setE(memory->getE() & 0xDF); //Masks off sixth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBAC()
{
	//Reset bit 5 in H
    memory->setH(memory->getH() & 0xDF); //Masks off sixth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBAD()
{
	//Reset bit 5 in L
    memory->setL(memory->getL() & 0xDF); //Masks off sixth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBAE()
{
	//Reset bit 5 in HL
    short hl = memory->getHL();
    memory->writeMemory(hl, (unsigned char)(memory->readMemory(hl) & 0xDF)); //Masks off left most bit
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCBAF()
{
	//Reset bit 5 in A
    memory->setA(memory->getA() & 0xDF); //Masks off sixth to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBB0()
{
	//Reset bit 6 in B
    memory->setB(memory->getB() & 0xBF); //Masks off seventh to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBB1()
{
	//Reset bit 6 in C
    memory->setC(memory->getC() & 0xBF); //Masks off seventh to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBB2()
{
	//Reset bit 6 in D
    memory->setD(memory->getD() & 0xBF); //Masks off seventh to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBB3()
{
	//Reset bit 6 in E
    memory->setE(memory->getE() & 0xBF); //Masks off seventh to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBB4()
{
	//Reset bit 6 in H
    memory->setH(memory->getH() & 0xBF); //Masks off seventh to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBB5()
{
	//Reset bit 6 in L
    memory->setL(memory->getL() & 0xBF); //Masks off seventh to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBB6()
{
	//Reset bit 6 in HL
    short hl = memory->getHL();
    memory->writeMemory(hl, (unsigned char)(memory->readMemory(hl) & 0xBF)); //Masks off left most bit
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCBB7()
{
	//Reset bit 6 in A
    memory->setA(memory->getA() & 0xBF); //Masks off seventh to left most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBB8()
{
	//Reset bit 7 in B
    memory->setB(memory->getB() & 0x7F); //Masks off right most bit
	mClock += 2;
	tClock += 8;
}
void Cpu::opcodeCBB9()
{
	//Reset bit 7 in C
    memory->setC(memory->getC() & 0x7F); //Masks off right most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBBA()
{
	//Reset bit 7 in D
    memory->setD(memory->getD() & 0x7F); //Masks off right most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBBB()
{
	//Reset bit 7 in E
    memory->setE(memory->getE() & 0x7F); //Masks off right most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBBC()
{
	//Reset bit 7 in H
    memory->setH(memory->getH() & 0x7F); //Masks off right most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBBD()
{
	//Reset bit 7 in L
    memory->setL(memory->getL() & 0x7F); //Masks off right most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBBE()
{
	//Reset bit 7 in HL
    short hl = memory->getHL();
    memory->writeMemory(hl, (unsigned char)(memory->readMemory(hl) & 0x7F)); //Masks off left most bit
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCBBF()
{
	//Reset bit 7 in A
    memory->setA(memory->getA() & 0x7F); //Masks off right most bit
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBC0()
{
	//Set Bit 0 of B
    memory->setB(memory->getB() | 0x01);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBC1()
{
	//Set Bit 0 of C
    memory->setC(memory->getC() | 0x01);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBC2()
{
	//Set Bit 0 of D
    memory->setD(memory->getD() | 0x01);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBC3()
{
	//Set Bit 0 of E
    memory->setE(memory->getE() | 0x01);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBC4()
{
	//Set Bit 0 of H
    memory->setH(memory->getH() | 0x01);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBC5()
{
	//Set Bit 0 of L
    memory->setL(memory->getL() | 0x01);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBC6()
{
	//Set Bit 0 of data at HL
    memory->writeMemory(memory->getHL(), (unsigned char)(memory->readMemory(memory->getHL()) | 0x01));
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCBC7()
{
	//Set Bit 0 of A
    memory->setA(memory->getA() | 0x01);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBC8()
{
	//Set Bit 1 of B
    memory->setB(memory->getB() | 0x02);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBC9()
{
	//Set Bit 1 of C
    memory->setC(memory->getC() | 0x02);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBCA()
{
	//Set Bit 1 of D
    memory->setD(memory->getD() | 0x02);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBCB()
{
	//Set Bit 1 of E
    memory->setE(memory->getE() | 0x02);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBCC()
{
	//Set Bit 1 of H
    memory->setH(memory->getH() | 0x02);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBCD()
{
	//Set Bit 1 of L
    memory->setL(memory->getL() | 0x02);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBCE()
{
	//Set Bit 1 of data at HL
    short hl = memory->getHL();
    memory->writeMemory(hl, (unsigned char)(memory->readMemory(hl) | 0x02));
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCBCF()
{
	//Set Bit 1 of A
    memory->setA(memory->getA() | 0x02);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBD0()
{
	//Set Bit 2 of B
    memory->setB(memory->getB() | 0x04);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBD1()
{
	//Set Bit 2 of C
    memory->setC(memory->getC() | 0x04);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBD2()
{
	//Set Bit 2 of D
    memory->setD(memory->getD() | 0x04);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBD3()
{
	//Set Bit 2 of E
    memory->setE(memory->getE() | 0x04);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBD4()
{
	//Set Bit 2 of H
    memory->setH(memory->getH() | 0x04);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBD5()
{
	//Set Bit 2 of L
    memory->setL(memory->getL() | 0x04);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBD6()
{
	//Set Bit 2 of data at HL
    short hl = memory->getHL();
    memory->writeMemory(hl, (unsigned char)(memory->readMemory(hl) | 0x04));
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCBD7()
{
	//Set Bit 2 of A
    memory->setA(memory->getA() | 0x04);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBD8()
{
	//Set Bit 3 of B
    memory->setB(memory->getB() | 0x08);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBD9()
{
	//Set Bit 3 of C
    memory->setC(memory->getC() | 0x08);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBDA()
{
	//Set Bit 3 of D
    memory->setD(memory->getD() | 0x08);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBDB()
{
	//Set Bit 3 of E
    memory->setE(memory->getE() | 0x08);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBDC()
{
	//Set Bit 3 of H
    memory->setH(memory->getH() | 0x08);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBDD()
{
	//Set Bit 3 of L
    memory->setL(memory->getL() | 0x08);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBDE()
{
	//Set Bit 3 of data at HL
    short hl = memory->getHL();
    memory->writeMemory(hl, (unsigned char)(memory->readMemory(hl) | 0x08));
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCBDF()
{
	//Set Bit 3 of A
    memory->setA(memory->getA() | 0x08);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBE0()
{
	//Set Bit 4 of B
    memory->setB(memory->getB() | 0x10);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBE1()
{
	//Set Bit 4 of C
    memory->setC(memory->getC() | 0x10);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBE2()
{
	//Set Bit 4 of D
    memory->setD(memory->getD() | 0x10);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBE3()
{
	//Set Bit 4 of E
    memory->setE(memory->getE() | 0x10);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBE4()
{
	//Set Bit 4 of H
    memory->setH(memory->getH() | 0x10);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBE5()
{
	//Set Bit 4 of L
    memory->setL(memory->getL() | 0x10);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBE6()
{
	//Set Bit 4 of data at HL
    short hl = memory->getHL();
    memory->writeMemory(hl, (unsigned char)(memory->readMemory(hl) | 0x10));
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCBE7()
{
	//Set Bit 4 of A
    memory->setA(memory->getA() | 0x10);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBE8()
{
	//Set Bit 5 of B
    memory->setB(memory->getB() | 0x20);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBE9()
{
	//Set Bit 5 of C
    memory->setC(memory->getC() | 0x20);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBEA()
{
	//Set Bit 5 of D
    memory->setD(memory->getD() | 0x20);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBEB()
{
	//Set Bit 5 of E
    memory->setE(memory->getE() | 0x20);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBEC()
{
	//Set Bit 5 of H
    memory->setH(memory->getH() | 0x20);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBED()
{
	//Set Bit 5 of L
    memory->setL(memory->getL() | 0x20);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBEE()
{
	//Set Bit 5 of data at HL
    short hl = memory->getHL();
    memory->writeMemory(hl, (unsigned char)(memory->readMemory(hl) | 0x20));
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCBEF()
{
	//Set Bit 5 of A
    memory->setA(memory->getA() | 0x20);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBF0()
{
	//Set Bit 6 of B
    memory->setB(memory->getB() | 0x40);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBF1()
{
	//Set Bit 6 of C
    memory->setC(memory->getC() | 0x40);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBF2()
{
	//Set Bit 6 of D
    memory->setD(memory->getD() | 0x40);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBF3()
{
	//Set Bit 6 of E
    memory->setE(memory->getE() | 0x40);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBF4()
{
	//Set Bit 6 of H
    memory->setH(memory->getH() | 0x40);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBF5()
{
	//Set Bit 6 of L
    memory->setL(memory->getL() | 0x40);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBF6()
{
	//Set Bit 6 of data at HL
    short hl = memory->getHL();
    memory->writeMemory(hl, (unsigned char)(memory->readMemory(hl) | 0x40));
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCBF7()
{
	//Set Bit 6 of A
    memory->setA(memory->getA() | 0x40);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBF8()
{
	//Set Bit 7 of B
    memory->setB(memory->getB() | 0x80);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBF9()
{
	//Set Bit 7 of C
    memory->setC(memory->getC() | 0x80);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBFA()
{
	//Set Bit 7 of D
    memory->setD(memory->getD() | 0x80);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBFB()
{
	//Set Bit 7 of E
    memory->setE(memory->getE() | 0x80);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBFC()
{
	//Set Bit 7 of H
    memory->setH(memory->getH() | 0x80);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBFD()
{
	//Set Bit 7 of L
    memory->setL(memory->getL() | 0x80);
	mClock += 2;
	tClock += 8;
}

void Cpu::opcodeCBFE()
{
	//Set Bit 7 of data at HL
    short hl = memory->getHL();
    memory->writeMemory(hl, (unsigned char)(memory->readMemory(hl) | 0x80));
	mClock += 3;
	tClock += 12;
}

void Cpu::opcodeCBFF()
{
	//Set Bit 7 of A
    memory->setA(memory->getA() | 0x80);
	mClock += 2;
	tClock += 8;
}

void Cpu::updateTIMA(int curClocks, int& clocksSinceLastTIMAUpdate, int& clocksSinceLastDIVUpdate)
{
	/*
	Purpose: Checks each loop cycle if enough cycles have passed to increment the timers.
	If so, it writes the incremented value to the timer register and requests an interrupt if it overflows.
	*/

    bool timerEnabled = ((memory->readMemory(0xFF07) & 0x04) > 0);

	if (timerEnabled)
	{

        unsigned char timerFrequency = memory->readMemory(0xFF07) & 0x03;
		int timerNumClocksToUpdate;

		switch (timerFrequency)
		{
			case 0:
			{
				timerNumClocksToUpdate = 1024; //4096 hz
				break;
			}
			case 1:
			{
				timerNumClocksToUpdate = 16; //262144 hz
				break;
			}
			case 2:
			{
				timerNumClocksToUpdate = 64; //65536 hz
				break;
			}
			case 3:
			{
				timerNumClocksToUpdate = 256; //16386 hz
				break;
			}
			default:
			{
				timerNumClocksToUpdate = 256;
				break;
			}
		}

		if((curClocks - clocksSinceLastTIMAUpdate) >= timerNumClocksToUpdate)
		{
			clocksSinceLastTIMAUpdate = curClocks;


			//Increment TIMA
            unsigned char tima = memory->readMemory(0xFF05);
			if (tima == 0xFF)
			{
				//Set Timer Overflow Interrupt Flag
                memory->writeMemory((short)0xFF0F, (unsigned char)(memory->readMemory(0xFF0F) | 0x4));

				//Load TMA value into TIMA
                memory->writeMemory((short)0xFF05, memory->readMemory(0xFF06));
			}
			else
			{
                memory->writeMemory((short)0xFF05, (unsigned char)(tima + 1));
			}
		}
	}

	if ((curClocks - clocksSinceLastDIVUpdate) >= 256) //16386 hz
	{
        memory->writeMemory((short)0xFF04, (unsigned char)(memory->readMemory(0xFF04) + 1));
		clocksSinceLastDIVUpdate = curClocks;
	}
}

bool Cpu::checkForInterrupt()
{
	/*
	Purpose: Checks if there are any interrupts pending so that they can be serviced later. The intention is to be able to check with
	minimal effort and not having any functionality related to servicing the interrupt itself.
	*/

    unsigned char IE = memory->readMemory(0xFFFF);
    unsigned char IF = memory->readMemory(0xFF0F);

	//The interrupt bits are within 0x1 an 0x1F
	//If a bit is enabled in both IE and IF, (IE & IF) will keep them
	//If a bit is within the interrupt bit range (x & 0x1F) will keep them
	//If the resulting value is not 0, then at least one interrupt is pending
	return ((IE & IF & 0x1F) != 0);
}

void Cpu::executeInterrupt()
{
	/*
	Purpose: Services any interrupts active in the IE and IF registers. If both IE and IF contain a matching bit, the current stack pointer
	is stored before jumping to the interrupt vector that corresponds to those enabled bits.
	*/

    unsigned char IE = memory->readMemory(0xFFFF);
    unsigned char IF = memory->readMemory(0xFF0F);

	stackPointer -= 2;
    memory->writeMemory(stackPointer, memory->memoryPointer);

	interruptsEnabled = false;

	//If there are several interrupts, VBLANK takes highest priority and goes down
	if (((IF & 0x01) == 1) && ((IE & 0x01) == 1))
	{
		//VBLANK
        memory->memoryPointer = 0x0040;
        memory->writeMemory(0xFF0F, (unsigned char)(IF & 0xFE)); //Clear bit in IF
	}
	else if (((((IF & 0x02) >> 1) == 1) && ((IE & 0x02) >> 1 == 1)))
	{
		//LCD
        memory->memoryPointer = 0x0048;
        memory->writeMemory(0xFF0F, (unsigned char)(IF & 0xFD)); //Clear bit in IF
	}
	else if (((((IF & 0x04) >> 2) == 1) && ((IE & 0x04) >> 2 == 1)))
	{
		//Timer Overflow
        memory->memoryPointer = 0x0050;
        memory->writeMemory(0xFF0F, (unsigned char)(IF & 0xFB)); //Clear bit in IF
	}
	else if (((((IF & 0x08) >> 3) == 1) && ((IE & 0x08) >> 3 == 1)))
	{
		//Serial
        memory->memoryPointer = 0x0058;
        memory->writeMemory(0xFF0F, (unsigned char)(IF & 0xF7)); //Clear bit in IF
	}
	else if (((((IF & 0x10) >> 4) == 1) && ((IE & 0x10) >> 4 == 1)))
	{
		//Joypad
        memory->memoryPointer = 0x0060;
        memory->writeMemory(0xFF0F, (unsigned char)(IF & 0xEF)); //Clear bit in IF
	}

	mClock += 5;
	tClock += 20;
}

bool Cpu::checkForHaltOrInterrupt()
{
	/*
	Purpose: Allows interrupts or halts to be serviced if they are active.
	Otherwise, it will return false and the next assembly instruction will be executed as normal.
	*/

	bool pendingInterrupt = checkForInterrupt();

	if (pendingInterrupt)
	{
		if (halt)
		{
			if (haltMode == 1)
			{
				//Halt Mode == 1, normal halt mode execution
				//Halt Mode 2 does not clear IF or jump
				executeInterrupt();
			}

			halt = false;
			haltMode = 0;
			mClock += 1;
			tClock += 4;
		}
		else
		{
			if (interruptsEnabled) //if IME == 1
			{
				//Not halting, normal interrupt execution
				executeInterrupt();
			}
		}
	}
	else
	{
		if (halt)
		{
			return true;
		}
	}

	return false;

	//0040: Vertical Blankl Interrupt Start Address
	//0048:LCDC Status Interrupt Start Address
	//0050:Timer Overflow Interrupt Start Address
	//0058 Serial Transfer Completion Interrupt
	//0060 High to Low P10-P13 Interrupt Start Address
}

void Cpu::executeStop()
{
	if (beakInput.isAnyKeyPressed())
	{
		stop = false;
	}
	else
	{
		if (interruptsEnabled)
		{
            unsigned char IE = memory->readMemory(0xFFFF);
            unsigned char IF = memory->readMemory(0xFF0F);

			if (((((IF & 0x10) >> 4) == 1) && ((IE & 0x10) >> 4 == 1)))
			{
				stop = false;
			}
		}
	}

	if (preparingSpeedChange)
	{
		doubleSpeedMode = !doubleSpeedMode;
		preparingSpeedChange = false;
	}
}


int Cpu::returnTClock()
{
	return tClock;
}

int Cpu::returnMClock()
{
	return mClock;
}

bool Cpu::returnHalt()
{
	return halt;
}

bool Cpu::returnStop()
{
	return stop;
}

bool Cpu::returnInterrupt()
{
	return interrupt;
}

bool Cpu::returnIME()
{
	return interruptsEnabled;
}

bool Cpu::returnRepeat()
{
	return repeatBug;
}

void Cpu::setTClock(int newTClock)
{
	tClock = newTClock;
}

void Cpu::setmClock(int newMClock)
{
	mClock = newMClock;
}

void Cpu::setHalt(bool newHalt)
{
	halt = newHalt;
}

void Cpu::setStop(bool newStop)
{
	stop = newStop;
}

void Cpu::setIME(bool ime)
{
	interruptsEnabled = ime;
}

void Cpu::setInterrupt(bool newInterrupt)
{
	interrupt = newInterrupt;
}
void Cpu::setRepeat(bool newRepeat)
{
	repeatBug = newRepeat;
}

void Cpu::setDoubleSpeedModeSignal(bool newSpeedSetting) {
    if (doubleSpeedMode != newSpeedSetting)
    {
        preparingSpeedChange = true;
    }
}
