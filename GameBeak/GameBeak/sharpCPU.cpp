#include "sharpCPU.h"
#include "Main.h"
#include "Binary.h"


#include <tuple>
#include "Debugger.h"

void sharpCPU::selectOpcode(byte opcode)
{
	if (repeat)
	{
		//Sets memory pointer back one.
		//If opcode is one byte it should repeat.
		//If opcode requires operands, the opcode itself will be the first operand
		memoryPointer--;
		repeat = false;
	}

	if (enableInterruptsNextCycle)
	{
		enableInterruptsNextCycle = false;
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
					opcode01((beakMemory.readMemory(memoryPointer++)) | (beakMemory.readMemory(memoryPointer++) << 8));
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
					opcode06(beakMemory.readMemory(memoryPointer++));
					break;
				}
				case 7:
				{
					opcode07();
					break;
				}
				case 8:
				{
					opcode08((beakMemory.readMemory(memoryPointer++)) | (beakMemory.readMemory(memoryPointer++) << 8));
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
					opcode0E(beakMemory.readMemory(memoryPointer++));
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
					//10 not implemented
					break;
				}
				case 1:
				{
					opcode11((beakMemory.readMemory(memoryPointer++)) | (beakMemory.readMemory(memoryPointer++) << 8));
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
					opcode16(beakMemory.readMemory(memoryPointer++));
					break;
				}
				case 7:
				{
					opcode17();
					break;
				}
				case 8:
				{
					opcode18((char)beakMemory.readMemory(memoryPointer++));
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
					opcode1E(beakMemory.readMemory(memoryPointer++));
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
					opcode20(beakMemory.readMemory(memoryPointer++));
					break;
				}
				case 1:
				{
					opcode21((beakMemory.readMemory(memoryPointer++)) | (beakMemory.readMemory(memoryPointer++) << 8));
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
					opcode26(beakMemory.readMemory(memoryPointer++));
					break;
				}
				case 7:
				{
					opcode27();
					break;
				}
				case 8:
				{
					opcode28(beakMemory.readMemory(memoryPointer++));
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
					opcode2E(beakMemory.readMemory(memoryPointer++));
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
					opcode30(beakMemory.readMemory(memoryPointer++));
					break;
				}
				case 1:
				{
					opcode31((beakMemory.readMemory(memoryPointer++)) | (beakMemory.readMemory(memoryPointer++) << 8));
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
					opcode36(beakMemory.readMemory(memoryPointer++));
					break;
				}
				case 7:
				{
					opcode37();
					break;
				}
				case 8:
				{
					opcode38(beakMemory.readMemory(memoryPointer++));
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
					opcode3E(beakMemory.readMemory(memoryPointer++));
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
					opcodeC2((beakMemory.readMemory(memoryPointer++)) | (beakMemory.readMemory(memoryPointer++) << 8));
					break;
				}
				case 0x03:
				{
					opcodeC3((beakMemory.readMemory(memoryPointer++)) | (beakMemory.readMemory(memoryPointer++) << 8));
					break;
				}
				case 0x04:
				{
					opcodeC4((beakMemory.readMemory(memoryPointer++)) | (beakMemory.readMemory(memoryPointer++) << 8));
					break;
				}
				case 0x05:
				{
					opcodeC5();
					break;
				}
				case 0x06:
				{
					opcodeC6(beakMemory.readMemory(memoryPointer++));
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
					opcodeCA((beakMemory.readMemory(memoryPointer++)) | (beakMemory.readMemory(memoryPointer++) << 8));
					break;
				}
				case 0x0B:
				{
					switch (beakMemory.readMemory(memoryPointer++))
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
					opcodeCC((beakMemory.readMemory(memoryPointer++)) | (beakMemory.readMemory(memoryPointer++) << 8));
					break;
				}
				case 0x0D:
				{
					opcodeCD((beakMemory.readMemory(memoryPointer++)) | (beakMemory.readMemory(memoryPointer++) << 8));
					break;
				}
				case 0x0E:
				{
					opcodeCE(beakMemory.readMemory(memoryPointer++));
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
					opcodeD2((beakMemory.readMemory(memoryPointer++)) | (beakMemory.readMemory(memoryPointer++) << 8));
					break;
				}
				case 3:
				{
					//D3 does not exist
					break;
				}
				case 4:
				{
					opcodeD4((beakMemory.readMemory(memoryPointer++)) | (beakMemory.readMemory(memoryPointer++) << 8));
					break;
				}
				case 5:
				{
					opcodeD5();
					break;
				}
				case 6:
				{
					opcodeD6(beakMemory.readMemory(memoryPointer++));
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
					opcodeDA((beakMemory.readMemory(memoryPointer++)) | (beakMemory.readMemory(memoryPointer++) << 8));
					break;
				}
				case 0xB:
				{
					//Does not exist
					break;
				}
				case 0xC:
				{
					opcodeDC((beakMemory.readMemory(memoryPointer++)) | (beakMemory.readMemory(memoryPointer++) << 8));
					break;
				}
				case 0xD:
				{
					//DD not exist
					break;
				}
				case 0xE:
				{
					opcodeDE(beakMemory.readMemory(memoryPointer++));
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
					opcodeE0(beakMemory.readMemory(memoryPointer++));
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
					opcodeE6(beakMemory.readMemory(memoryPointer++));
					break;
				}
				case 7:
				{
					opcodeE7();
					break;
				}
				case 8:
				{
					opcodeE8(beakMemory.readMemory(memoryPointer++));
					break;
				}
				case 9:
				{
					opcodeE9();
					break;
				}
				case 0xA:
				{
					opcodeEA((beakMemory.readMemory(memoryPointer++)) | (beakMemory.readMemory(memoryPointer++) << 8));
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
					opcodeEE(beakMemory.readMemory(memoryPointer++));
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
					opcodeF0(beakMemory.readMemory(memoryPointer++));
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
					opcodeF6(beakMemory.readMemory(memoryPointer++));
					break;
				}
				case 7:
				{
					opcodeF7();
					break;
				}
				case 8:
				{
					opcodeF8(beakMemory.readMemory(memoryPointer++));
					break;
				}
				case 9:
				{
					opcodeF9();
					break;
				}
				case 0xA:
				{
					opcodeFA((beakMemory.readMemory(memoryPointer++)) | (beakMemory.readMemory(memoryPointer++) << 8));
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
					opcodeFE(beakMemory.readMemory(memoryPointer++));
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


void sharpCPU::opcode00()
{
	//NOP
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode01(short nn)
{
	//Load short into BC
	beakMemory.setBC(nn);
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcode02()
{
	//Load A into data at BC
	beakMemory.writeMemory(beakMemory.getBC(), beakMemory.getA());
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode03()
{
	//Inc BC

	beakMemory.setBC(beakMemory.getBC() + 1);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode04()
{
	//Inc B

	beakMemory.setB(beakMemory.getB() + 1);

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getB() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag((((beakMemory.getB()) & 0x0F) == 0) ? 1 : 0);
}

void sharpCPU::opcode05()
{
	//Dec B

	beakMemory.setB(beakMemory.getB() - 1);

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getB() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag((((beakMemory.getB()) & 0x0F) == 0xF) ? 1 : 0);
}

void sharpCPU::opcode06(byte n)
{
	//Load byte into B
	beakMemory.setB(n);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode07()
{
	/*
	//Rotate A Left - Set C flag to old bit 7
	beakMemory.setCFlag(((beakMemory.getA() & 0x01) == 1) ? true : false);
	beakMemory.setA(rotateLeft(beakMemory.getA()));
	mClock += 2;
	tClock += 8;
	*/

	//Rotate A Left, put previous bit 7 into Carry flag
	if (beakMemory.getA() != 0)
	{
		beakMemory.setCFlag(beakMemory.getA() & 0x01);
	}
	else
	{
		beakMemory.setZFlag(0);
		beakMemory.setCFlag(0);
	}

	//beakMemory.setA(beakMemory.getA() << 1);
	beakMemory.setA(rotateLeft(beakMemory.getA()));

	mClock += 1;
	tClock += 4;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);

}

void sharpCPU::opcode08(short nn)
{
	//Load SP into data at NN
	beakMemory.writeMemory(nn, stackPointer);
	mClock += 5;
	tClock += 20;
}

void sharpCPU::opcode09()
{
	//Add BC to HL

	unsigned short hl = beakMemory.getHL();
	unsigned short bc = beakMemory.getBC();
	unsigned int totalSum = hl + bc;
	unsigned int halfCarrySum = (hl & 0x0FFF) + (bc & 0x0FFF);

	if (totalSum > 0xFFFF)
	{
		int overflow = totalSum - 65536;//0xFFFF;
		beakMemory.setHL(0 + overflow);
		beakMemory.setCFlag(true);
		beakMemory.setHFlag(true);
	}
	else
	{
		beakMemory.setHFlag(halfCarrySum > 0x0FFF);
		beakMemory.setHL(beakMemory.getHL() + beakMemory.getBC());
		//TODO: Find out of H can be set by half overflow? Haven't found a circumstance in which it does yet
		beakMemory.setCFlag(false);
	}
	mClock += 2;
	tClock += 8;

	//beakMemory.setZFlag(beakMemory.getHL() == 0); //From testing, this opcode leaves Z as it was
	beakMemory.setNFlag(false);
}


void sharpCPU::opcode0A()
{
	//Load data at BC into A
	beakMemory.setA(beakMemory.readMemory(beakMemory.getBC()));
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode0B()
{
	//Dec BC

	beakMemory.setBC(beakMemory.getBC() - 1);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode0C()
{
	//Inc C

	beakMemory.setC(beakMemory.getC() + 1);

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getC() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag((((beakMemory.getC()) & 0x0F) == 0) ? 1 : 0);
}

void sharpCPU::opcode0D()
{
	//Dec C

	beakMemory.setC(beakMemory.getC() - 1);

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getC() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag((((beakMemory.getC()) & 0x0F) == 0xF) ? 1 : 0);
}

void sharpCPU::opcode0E(byte n)
{
	//Load byte into C
	beakMemory.setC(n);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode0F()
{
	//Rotate A Right, put previous bit 0 into Carry flag

	beakMemory.setCFlag( (beakMemory.getA() & 0x01) > 0);
	beakMemory.setA(rotateRight(beakMemory.getA()));

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag(false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);

}

//Need to implement 10 STOP 

void sharpCPU::opcode11(short nn)
{
	//Load short into DE
	beakMemory.setDE(nn);
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcode12()
{
	//Load A into data at DE
	beakMemory.writeMemory(beakMemory.getDE(), beakMemory.getA());
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode13()
{
	//Inc DE

	beakMemory.setDE(beakMemory.getDE() + 1);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode14()
{
	//Inc D

	beakMemory.setD(beakMemory.getD() + 1);

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getD() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag((((beakMemory.getD()) & 0x0F) == 0) ? 1 : 0);
}

void sharpCPU::opcode15()
{
	//Dec D

	beakMemory.setD(beakMemory.getD() - 1);

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getD() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag((((beakMemory.getD()) & 0x0F) == 0xF) ? 1 : 0);
}

void sharpCPU::opcode16(byte n)
{
	//Load byte into D
	beakMemory.setD(n);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode17()
{
	//RLCA Rotate A Left - Set right most bit to current carry flag
	byte cFlag = (beakMemory.getCFlag() == true) ? 0x01 : 0x00;
	beakMemory.setCFlag( ((beakMemory.getA() & 0x80) >> 7) > 0);
	beakMemory.setA((beakMemory.getA() << 1) | cFlag);

	beakMemory.setZFlag(false); 
	beakMemory.setHFlag(false);
	beakMemory.setNFlag(false);
	mClock += 1;
	tClock += 4;

}

void sharpCPU::opcode18(char n) //signed byte
{
	//Jump Relative to n
	memoryPointer += (signed char)n;
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcode19()
{
	//Add DE to HL

	unsigned short hl = beakMemory.getHL();
	unsigned short de = beakMemory.getDE();
	unsigned int totalSum = hl + de;
	unsigned int halfCarrySum = (hl & 0x0FFF) + (de & 0x0FFF);

	if (totalSum > 0xFFFF)
	{
		short overflow = (totalSum - 65536);//0xFFFF;
		beakMemory.setHL(0 + overflow);
		beakMemory.setCFlag(true);
		beakMemory.setHFlag(true);
	}
	else
	{
		beakMemory.setHFlag(halfCarrySum > 0x0FFF);
		beakMemory.setHL(beakMemory.getHL() + beakMemory.getDE());
		//TODO: Find out if half carry happens?
		beakMemory.setCFlag(false);
	}
	mClock += 2;
	tClock += 8;

	//beakMemory.setZFlag(beakMemory.getHL() == 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode1A()
{
	//Load data at DE into A
	beakMemory.setA(beakMemory.readMemory(beakMemory.getDE()));
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode1B()
{
	//Dec DE

	beakMemory.setDE(beakMemory.getDE() - 1);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode1C()
{
	//Inc E

	beakMemory.setE(beakMemory.getE() + 1);

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getE() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag((((beakMemory.getE()) & 0x0F) == 0) ? 1 : 0);
}

void sharpCPU::opcode1D()
{
	//Dec E

	beakMemory.setE(beakMemory.getE() - 1);

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getE() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag((((beakMemory.getE()) & 0x0F) == 0xF) ? 1 : 0);
}

void sharpCPU::opcode1E(byte n)
{
	//Load byte into E
	beakMemory.setE(n);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode1F()
{
	//RRA - Rotate A Right - Store old bit 0 in Carry Flag - Current Carry flag becomes new bit 7
	//Rotate A Right - Set left most bit to current carry flag
	byte cFlag = (beakMemory.getCFlag() == true) ? 0x80 : 0x00;
	beakMemory.setCFlag((((beakMemory.getA() & 0x80) >> 7) == 1) ? true : false);
	beakMemory.setA((beakMemory.getA() >> 1) | cFlag);
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode20(byte n)
{
	//Jump Relative to n if Not Zero
	if (!beakMemory.getZFlag())
	{
		memoryPointer += (signed char)n;
		mClock += 3;
		tClock += 12;

	}
	else
	{
		mClock += 2;
		tClock += 8;
	}
}

void sharpCPU::opcode21(short nn)
{
	//Load short into HL
	beakMemory.setHL(nn);
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcode22()
{
	//Load A into data at HL and increment HL
	beakMemory.writeMemory(beakMemory.getHL(), beakMemory.getA());
	beakMemory.setHL(beakMemory.getHL() + 1);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode23()
{
	//Inc HL

	beakMemory.setHL(beakMemory.getHL() + 1);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode24()
{
	//Inc H

	beakMemory.setH(beakMemory.getH() + 1);

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getH() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag((((beakMemory.getH()) & 0x0F) == 0) ? 1 : 0);
}

void sharpCPU::opcode25()
{
	//Dec H

	beakMemory.setH(beakMemory.getH() - 1);

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getH() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag((((beakMemory.getH()) & 0x0F) == 0xF) ? 1 : 0);
}

void sharpCPU::opcode26(byte n)
{
	//Load byte into H
	beakMemory.setH(n);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode27()
{
	//DAA Load decimal representation of A into A

	byte aValue = beakMemory.getA();

	if (beakMemory.getNFlag())
	{
		if (beakMemory.getCFlag())
		{
			beakMemory.setCFlag(true);

			if (beakMemory.getHFlag())
			{
				aValue += 0x9A;
			}
			else
			{
				aValue += 0xA0;
			}

		}
		else if (beakMemory.getHFlag())
		{
			aValue += 0xFA;
			beakMemory.setCFlag(false);
		}
	}
	else
	{
		if (beakMemory.getHFlag() || ((aValue & 0x0F) > 9))
		{
			aValue += 0x6;
			beakMemory.setCFlag(false);
		}

		if (beakMemory.getCFlag() || (aValue > 0x99))
		{
			aValue += 0x60;
			beakMemory.setCFlag(true);
		}
	}

	//beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setZFlag(aValue == 0);
	beakMemory.setA(aValue & 0xFF);

	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode28(byte n)
{
	//Jump to memoryPointer + n if Zero
	if (beakMemory.getZFlag())
	{
		//memoryPointer += (signed char)n;
		memoryPointer += (signed char)n;
		mClock += 3;
		tClock += 12;
	}
	else
	{
		mClock += 2;
		tClock += 8;
	}
}

void sharpCPU::opcode29()
{
	//Add HL to HL

	unsigned short hl = beakMemory.getHL();
	unsigned int totalSum = hl + hl;
	unsigned int halfCarrySum = (hl & 0x0FFF) * 2;

	if (totalSum > 0xFFFF)
	{
		short overflow = (totalSum - 65536);//0xFFFF;
		beakMemory.setHL(0 + overflow);
		beakMemory.setCFlag(true);
		beakMemory.setHFlag(true);
	}
	else
	{
		beakMemory.setHFlag(halfCarrySum > 0x0FFF);
		beakMemory.setHL(beakMemory.getHL() + beakMemory.getHL());
		//Todo: Find out if half carry occurs
		beakMemory.setCFlag(false);
	}
	mClock += 2;
	tClock += 8;

	//beakMemory.setZFlag(beakMemory.getHL() == 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode2A()
{
	//Load data at HL to A and inc HL
	beakMemory.setA(beakMemory.readMemory(beakMemory.getHL()));
	beakMemory.setHL(beakMemory.getHL() + 1);
	mClock += 2;
	tClock += 8;

}

void sharpCPU::opcode2B()
{
	//Dec HL
	beakMemory.setHL(beakMemory.getHL() - 1);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode2C()
{
	//Inc L
	beakMemory.setL(beakMemory.getL() + 1);
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getL() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag((((beakMemory.getL()) & 0x0F) == 0) ? 1 : 0);
}

void sharpCPU::opcode2D()
{
	//Dec L
	beakMemory.setL(beakMemory.getL() - 1);
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getL() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag((((beakMemory.getL()) & 0x0F) == 0xF) ? 1 : 0);
}

void sharpCPU::opcode2E(byte n)
{
	//Load a byte into L
	beakMemory.setL(n);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode2F()
{
	//CPL - Flip all bits in A
	beakMemory.setA(~beakMemory.getA());
	mClock += 1;
	tClock += 4;

	beakMemory.setNFlag(true);
	beakMemory.setHFlag(true);
}

void sharpCPU::opcode30(byte n)
{
	//Jump Relative to n if Not Carry
	if (!beakMemory.getCFlag())
	{
		memoryPointer += (signed char)n;
		mClock += 3;
		tClock += 12;
	}
	else
	{
		mClock += 2;
		tClock += 8;
	}
}

void sharpCPU::opcode31(short nn)
{
	//Load short into SP
	stackPointer = nn;
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcode32()
{
	//Load A into data at HL and dec HL
	beakMemory.writeMemory(beakMemory.getHL(), beakMemory.getA());
	beakMemory.setHL(beakMemory.getHL() - 1);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode33()
{
	//Inc SP
	stackPointer++;
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode34()
{
	//Inc data at HL
	beakMemory.writeMemory(beakMemory.getHL(), (byte)(beakMemory.readMemory(beakMemory.getHL()) + 1));
	mClock += 3;
	tClock += 12;

	beakMemory.setZFlag((beakMemory.readMemory(beakMemory.getHL()) == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag((((beakMemory.readMemory(beakMemory.getHL())) & 0x0F) == 0) ? 1 : 0);
}

void sharpCPU::opcode35()
{
	//Dec data at HL
	beakMemory.writeMemory(beakMemory.getHL(), (byte)(beakMemory.readMemory(beakMemory.getHL()) - 1));
	mClock += 3;
	tClock += 12;

	beakMemory.setZFlag((beakMemory.readMemory(beakMemory.getHL()) == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag((((beakMemory.readMemory(beakMemory.getHL())) & 0x0F) == 0xF) ? 1 : 0);
}

void sharpCPU::opcode36(byte n)
{
	//Load byte into data at HL
	beakMemory.writeMemory(beakMemory.getHL(), n);
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcode37()
{
	//SCF Set Carry Flag
	beakMemory.setCFlag(true);
	mClock += 1;
	tClock += 4;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcode38(byte n)
{
	//Jump Relative to n if Carry
	if (beakMemory.getCFlag())
	{
		memoryPointer += (signed char)n;
		mClock += 3;
		tClock += 12;
	}
	else
	{
		mClock += 2;
		tClock += 8;
	}
}

void sharpCPU::opcode39()
{
	//Add SP to HL
	if ((beakMemory.getHL() + stackPointer) > 0xFFFF)
	{
		beakMemory.setHL((beakMemory.getHL() + stackPointer) - 65536);//0xFFFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHL(beakMemory.getHL() + stackPointer);
		//Todo: Check if half carry can occur?
	}
	mClock += 2;
	tClock += 8;

	//No Z flag from what I've found
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode3A()
{
	//Load data in HL into A and decrement HL
	beakMemory.setA(beakMemory.readMemory(beakMemory.getHL()));
	beakMemory.setHL(beakMemory.getHL() - 1);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode3B()
{
	//Dec SP
	stackPointer--;
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode3C()
{
	//Inc A
	beakMemory.setA(beakMemory.getA() + 1);
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0) ? 1 : 0);
}

void sharpCPU::opcode3D()
{
	//Dec A
	beakMemory.setA(beakMemory.getA() - 1);
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
}

void sharpCPU::opcode3E(byte n)
{
	//Load byte into A
	beakMemory.setA(n);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode3F()
{
	//Complement Carry Flag (Toggle C Flag)
	beakMemory.setCFlag((beakMemory.getCFlag() == 1) ? 0 : 1);
	mClock += 1;
	tClock += 4;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcode40()
{
	//Load B into B
	beakMemory.setB(beakMemory.getB());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode41()
{
	//Load C into B
	beakMemory.setB(beakMemory.getC());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode42()
{
	//Load D into B
	beakMemory.setB(beakMemory.getD());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode43()
{
	//Load E into B
	beakMemory.setB(beakMemory.getE());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode44()
{
	//Load H into B
	beakMemory.setB(beakMemory.getH());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode45()
{
	//Load L into B
	beakMemory.setB(beakMemory.getL());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode46()
{
	//Load data at HL into B
	beakMemory.setB(beakMemory.readMemory(beakMemory.getHL()));
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode47()
{
	//Load A into B
	beakMemory.setB(beakMemory.getA());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode48()
{
	//Load B into C
	beakMemory.setC(beakMemory.getB());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode49()
{
	//Load C into C
	beakMemory.setC(beakMemory.getC());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode4A()
{
	//Load D into C
	beakMemory.setC(beakMemory.getD());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode4B()
{
	//Load E into C
	beakMemory.setC(beakMemory.getE());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode4C()
{
	//Load H into C
	beakMemory.setC(beakMemory.getH());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode4D()
{
	//Load L into C
	beakMemory.setC(beakMemory.getL());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode4E()
{
	//Load data at HL into C
	beakMemory.setC(beakMemory.readMemory(beakMemory.getHL()));
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode4F()
{
	//Load A into C
	beakMemory.setC(beakMemory.getA());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode50()
{
	//Load B into D
	beakMemory.setD(beakMemory.getB());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode51()
{
	//Load C into D
	beakMemory.setD(beakMemory.getC());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode52()
{
	//Load D into D
	beakMemory.setD(beakMemory.getD());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode53()
{
	//Load E into D
	beakMemory.setD(beakMemory.getE());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode54()
{
	//Load H into D
	beakMemory.setD(beakMemory.getH());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode55()
{
	//Load L into D
	beakMemory.setD(beakMemory.getL());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode56()
{
	//Load data at HL into D
	beakMemory.setD(beakMemory.readMemory(beakMemory.getHL()));
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode57()
{
	//Load A into D
	beakMemory.setD(beakMemory.getA());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode58()
{
	//Load B into E
	beakMemory.setE(beakMemory.getB());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode59()
{
	//Load C into E
	beakMemory.setE(beakMemory.getC());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode5A()
{
	//Load D into E
	beakMemory.setE(beakMemory.getD());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode5B()
{
	//Load E into E
	beakMemory.setE(beakMemory.getE());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode5C()
{
	//Load H into E
	beakMemory.setE(beakMemory.getH());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode5D()
{
	//Load L into D
	beakMemory.setE(beakMemory.getL());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode5E()
{
	//Load data at HL into E
	beakMemory.setE(beakMemory.readMemory(beakMemory.getHL()));
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode5F()
{
	//Load A into E
	beakMemory.setE(beakMemory.getA());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode60()
{
	//Load B into H
	beakMemory.setH(beakMemory.getB());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode61()
{
	//Load C into H
	beakMemory.setH(beakMemory.getC());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode62()
{
	//Load D into H
	beakMemory.setH(beakMemory.getD());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode63()
{
	//Load E into H
	beakMemory.setH(beakMemory.getE());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode64()
{
	//Load H into H
	beakMemory.setH(beakMemory.getH());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode65()
{
	//Load L into H
	beakMemory.setH(beakMemory.getL());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode66()
{
	//Load data at HL into H
	beakMemory.setH(beakMemory.readMemory(beakMemory.getHL()));
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode67()
{
	//Load A into H
	beakMemory.setH(beakMemory.getA());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode68()
{
	//Load B into L
	beakMemory.setL(beakMemory.getB());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode69()
{
	//Load C into L
	beakMemory.setL(beakMemory.getC());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode6A()
{
	//Load D into L
	beakMemory.setL(beakMemory.getD());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode6B()
{
	//Load E into L
	beakMemory.setL(beakMemory.getE());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode6C()
{
	//Load H into L
	beakMemory.setL(beakMemory.getH());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode6D()
{
	//Load L into L
	beakMemory.setL(beakMemory.getL());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode6E()
{
	//Load data at HL into L
	beakMemory.setL(beakMemory.readMemory(beakMemory.getHL()));
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode6F()
{
	//Load A into L
	beakMemory.setL(beakMemory.getA());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode70()
{
	//Load B into data at HL
	beakMemory.writeMemory(beakMemory.getHL(), beakMemory.getB());
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode71()
{
	//Load C into data at HL
	beakMemory.writeMemory(beakMemory.getHL(), beakMemory.getC());
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode72()
{
	//Load D into data at HL
	beakMemory.writeMemory(beakMemory.getHL(), beakMemory.getD());
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode73()
{
	//Load E into data at HL
	beakMemory.writeMemory(beakMemory.getHL(), beakMemory.getE());
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode74()
{
	//Load H into data at HL
	beakMemory.writeMemory(beakMemory.getHL(), beakMemory.getH());
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode75()
{
	//Load L into data at HL
	beakMemory.writeMemory(beakMemory.getHL(), beakMemory.getL());
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode76()
{
	//Halt
	
	if (checkForInterrupt() && !interruptsEnabled) //If interrupt true while IME is disabled, repeat next opcode.
	{
		repeat = true;
	}
	else
	{
		halt = true; //Halt should only be set if the first case is not true.
	}

	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode77()
{
	//Load A into data at HL
	beakMemory.writeMemory(beakMemory.getHL(), beakMemory.getA());
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode78()
{
	//Load B into A
	beakMemory.setA(beakMemory.getB());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode79()
{
	//Load C into A
	beakMemory.setA(beakMemory.getC());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode7A()
{
	//Load D into A
	beakMemory.setA(beakMemory.getD());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode7B()
{
	//Load E into A
	beakMemory.setA(beakMemory.getE());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode7C()
{
	//Load H into A
	beakMemory.setA(beakMemory.getH());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode7D()
{
	//Load L into A
	beakMemory.setA(beakMemory.getL());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode7E()
{
	//Load data at HL into A
	beakMemory.setA(beakMemory.readMemory(beakMemory.getHL()));
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcode7F()
{
	//Load A into A
	beakMemory.setA(beakMemory.getA());
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcode80()
{
	//Add B to A
	if((beakMemory.getA() + beakMemory.getB()) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + beakMemory.getB()) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (beakMemory.getB() & 0x0F)) > 0x0F);
		//beakMemory.setHFlag((beakMemory.getA() <= 0x0F) && ((beakMemory.getB() + beakMemory.getA()) > 0x0F));
		beakMemory.setA(beakMemory.getA() + beakMemory.getB());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode81()
{
	//Add C to A
	if ((beakMemory.getA() + beakMemory.getC()) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + beakMemory.getC()) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (beakMemory.getC() & 0x0F)) > 0x0F);
		//beakMemory.setHFlag((beakMemory.getA() <= 0x0F) && ((beakMemory.getC() + beakMemory.getA()) > 0x0F));
		beakMemory.setA(beakMemory.getA() + beakMemory.getC());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode82()
{
	//Add D to A
	if ((beakMemory.getA() + beakMemory.getD()) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + beakMemory.getD()) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (beakMemory.getD() & 0x0F)) > 0x0F);
		//beakMemory.setHFlag((beakMemory.getA() <= 0x0F) && ((beakMemory.getC() + beakMemory.getA()) > 0x0F));
		beakMemory.setA(beakMemory.getA() + beakMemory.getD());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode83()
{
	//Add E to A
	if ((beakMemory.getA() + beakMemory.getE()) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + beakMemory.getE()) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (beakMemory.getE() & 0x0F)) > 0x0F);
		//beakMemory.setHFlag((beakMemory.getA() <= 0x0F) && ((beakMemory.getE() + beakMemory.getA()) > 0x0F));
		beakMemory.setA(beakMemory.getA() + beakMemory.getE());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode84()
{
	//Add H to A
	if ((beakMemory.getA() + beakMemory.getH()) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + beakMemory.getH()) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (beakMemory.getH() & 0x0F)) > 0x0F);
		//beakMemory.setHFlag((beakMemory.getA() <= 0x0F) && ((beakMemory.getH() + beakMemory.getA()) > 0x0F));
		beakMemory.setA(beakMemory.getA() + beakMemory.getH());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode85()
{
	//Add L to A
	if ((beakMemory.getA() + beakMemory.getL()) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + beakMemory.getL()) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (beakMemory.getL() & 0x0F)) > 0x0F);
		//beakMemory.setHFlag((beakMemory.getA() <= 0x0F) && ((beakMemory.getL() + beakMemory.getA()) > 0x0F));
		beakMemory.setA(beakMemory.getA() + beakMemory.getL());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode86()
{
	//Add data at HL to A
	if ((beakMemory.getA() + beakMemory.readMemory(beakMemory.getHL())) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + beakMemory.readMemory(beakMemory.getHL())) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (beakMemory.readMemory(beakMemory.getHL()) & 0x0F)) > 0x0F);
		//beakMemory.setHFlag((beakMemory.getA() <= 0x0F) && ((beakMemory.readMemory(beakMemory.getHL()) + beakMemory.getA()) > 0x0F));
		//beakMemory.setHFlag(((beakMemory.getA() | beakMemory.readMemory(beakMemory.getHL())) <= 0x0F) && (beakMemory.getA() + (beakMemory.readMemory(beakMemory.getHL())) > 0x0F));
		beakMemory.setA(beakMemory.getA() + beakMemory.readMemory(beakMemory.getHL()));
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode87()
{
	//Add A to A
	if ((beakMemory.getA() + beakMemory.getA()) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + beakMemory.getA()) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (beakMemory.getA() & 0x0F)) > 0x0F);
		//beakMemory.setHFlag(((beakMemory.getA() | beakMemory.getA()) <= 0x0F) && ((beakMemory.getA() + beakMemory.getA()) > 0x0F));
		beakMemory.setA(beakMemory.getA() + beakMemory.getA());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode88()
{
	//Add B and Carry flag to A
	if ((beakMemory.getA() + beakMemory.getB() + beakMemory.getCFlag()) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + beakMemory.getB() + beakMemory.getCFlag()) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (beakMemory.getB() & 0x0F) + beakMemory.getCFlag()) > 0x0F);
		//beakMemory.setHFlag((beakMemory.getA() <= 0x0F) && ((beakMemory.getB() + beakMemory.getA() + beakMemory.getCFlag()) > 0x0F));
		beakMemory.setA(beakMemory.getA() + beakMemory.getB() + beakMemory.getCFlag());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode89()
{
	//Add C and Carry flag to A
	if ((beakMemory.getA() + beakMemory.getC() + beakMemory.getCFlag()) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + beakMemory.getC() + beakMemory.getCFlag()) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (beakMemory.getC() & 0x0F) + beakMemory.getCFlag()) > 0x0F);
		//beakMemory.setHFlag((beakMemory.getA() <= 0x0F) && ((beakMemory.getC() + beakMemory.getA() + beakMemory.getCFlag()) > 0x0F));
		beakMemory.setA(beakMemory.getA() + beakMemory.getC() + beakMemory.getCFlag());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode8A()
{
	//Add D and Carry flag to A
	if ((beakMemory.getA() + beakMemory.getD() + beakMemory.getCFlag()) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + beakMemory.getD() + beakMemory.getCFlag()) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (beakMemory.getD() & 0x0F) + beakMemory.getCFlag()) > 0x0F);
		//beakMemory.setHFlag((beakMemory.getA() <= 0x0F) && ((beakMemory.getD() + beakMemory.getA() + beakMemory.getCFlag()) > 0x0F));
		beakMemory.setA(beakMemory.getA() + beakMemory.getD() + beakMemory.getCFlag());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode8B()
{
	//Add E and Carry flag to A
	if ((beakMemory.getA() + beakMemory.getE() + beakMemory.getCFlag()) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + beakMemory.getE() + beakMemory.getCFlag()) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (beakMemory.getE() & 0x0F) + beakMemory.getCFlag()) > 0x0F);
		//beakMemory.setHFlag((beakMemory.getA() <= 0x0F) && ((beakMemory.getE() + beakMemory.getA() + beakMemory.getCFlag()) > 0x0F));
		beakMemory.setA(beakMemory.getA() + beakMemory.getE() + beakMemory.getCFlag());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode8C()
{
	//Add H and Carry flag to A
	if ((beakMemory.getA() + beakMemory.getH() + beakMemory.getCFlag()) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + beakMemory.getH() + beakMemory.getCFlag()) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (beakMemory.getH() & 0x0F) + beakMemory.getCFlag()) > 0x0F);
		//beakMemory.setHFlag((beakMemory.getA() <= 0x0F) && ((beakMemory.getH() + beakMemory.getA() + beakMemory.getCFlag()) > 0x0F));
		beakMemory.setA(beakMemory.getA() + beakMemory.getH() + beakMemory.getCFlag());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode8D()
{
	//Add L and Carry flag to A
	if ((beakMemory.getA() + beakMemory.getL() + beakMemory.getCFlag()) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + beakMemory.getL() + beakMemory.getCFlag()) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (beakMemory.getL() & 0x0F) + beakMemory.getCFlag()) > 0x0F);
		//beakMemory.setHFlag((beakMemory.getA() <= 0x0F) && ((beakMemory.getL() + beakMemory.getA() + beakMemory.getCFlag()) > 0x0F));
		beakMemory.setA(beakMemory.getA() + beakMemory.getL() + beakMemory.getCFlag());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode8E()
{
	//Add data at HL and Carry flag to A
	if ((beakMemory.getA() + beakMemory.readMemory(beakMemory.getHL()) + beakMemory.getCFlag()) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + beakMemory.readMemory(beakMemory.getHL()) + beakMemory.getCFlag()) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (beakMemory.readMemory(beakMemory.getHL()) & 0x0F) + beakMemory.getCFlag()) > 0x0F);
		//beakMemory.setHFlag((beakMemory.getA() <= 0x0F) && ((beakMemory.readMemory(beakMemory.getHL()) + beakMemory.getA() + beakMemory.getCFlag()) > 0x0F));
		beakMemory.setA(beakMemory.getA() + beakMemory.readMemory(beakMemory.getHL()) + beakMemory.getCFlag());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode8F()
{
	//Add A and Carry flag to A
	if ((beakMemory.getA() + beakMemory.getA() + beakMemory.getCFlag()) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + beakMemory.getA() + beakMemory.getCFlag()) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (beakMemory.getA() & 0x0F) + beakMemory.getCFlag()) > 0x0F);
		//beakMemory.setHFlag((beakMemory.getA() <= 0x0F) && ((beakMemory.getA() + beakMemory.getA() + beakMemory.getCFlag()) > 0x0F));
		beakMemory.setA(beakMemory.getA() + beakMemory.getA() + beakMemory.getCFlag());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcode90()
{
	//Sub B from A
	if ((beakMemory.getA() - beakMemory.getB()) < 0x00)
	{
		beakMemory.setA((beakMemory.getA() - beakMemory.getB()) + 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setCFlag(beakMemory.getA() < beakMemory.getB());
		beakMemory.setHFlag((beakMemory.getA() & 0x0F) < (beakMemory.getB() & 0x0F));
		//beakMemory.setHFlag(beakMemory.getA() < beakMemory.getB());
		//beakMemory.setHFlag((beakMemory.getA() > 0x0F) && ((beakMemory.getA() - beakMemory.getB()) <= 0x0F));
		beakMemory.setA(beakMemory.getA() - beakMemory.getB());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		//beakMemory.setCFlag(false);
	}

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
}

void sharpCPU::opcode91()
{
	//Sub C from A
	if ((beakMemory.getA() - beakMemory.getC()) < 0x00)
	{
		beakMemory.setA((beakMemory.getA() - beakMemory.getC()) + 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setCFlag(beakMemory.getA() < beakMemory.getC());
		beakMemory.setHFlag((beakMemory.getA() & 0x0F) < (beakMemory.getC() & 0x0F));
		//beakMemory.setHFlag(beakMemory.getA() < beakMemory.getC());
		//beakMemory.setHFlag((beakMemory.getA() > 0x0F) && ((beakMemory.getA() - beakMemory.getC()) <= 0x0F));
		beakMemory.setA(beakMemory.getA() - beakMemory.getC());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		//beakMemory.setCFlag(false);
	}

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
}

void sharpCPU::opcode92()
{
	//Sub D from A
	if ((beakMemory.getA() - beakMemory.getD()) < 0x00)
	{
		beakMemory.setA((beakMemory.getA() - beakMemory.getD()) + 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setCFlag(beakMemory.getA() < beakMemory.getD());
		beakMemory.setHFlag((beakMemory.getA() & 0x0F) < (beakMemory.getD() & 0x0F));
		//beakMemory.setHFlag(beakMemory.getA() < beakMemory.getD());
		//beakMemory.setHFlag((beakMemory.getA() > 0x0F) && ((beakMemory.getA() - beakMemory.getD()) <= 0x0F));
		beakMemory.setA(beakMemory.getA() - beakMemory.getD());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		//beakMemory.setCFlag(false);
	}

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
}

void sharpCPU::opcode93()
{
	//Sub E from A
	if ((beakMemory.getA() - beakMemory.getE()) < 0x00)
	{
		beakMemory.setA((beakMemory.getA() - beakMemory.getE()) + 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setCFlag(beakMemory.getA() < beakMemory.getE());
		beakMemory.setHFlag((beakMemory.getA() & 0x0F) < (beakMemory.getE() & 0x0F));
		//beakMemory.setHFlag(beakMemory.getA() < beakMemory.getE());
		//beakMemory.setHFlag((beakMemory.getA() > 0x0F) && ((beakMemory.getA() - beakMemory.getE()) <= 0x0F));
		beakMemory.setA(beakMemory.getA() - beakMemory.getE());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		//beakMemory.setCFlag(false);
	}

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
}

void sharpCPU::opcode94()
{
	//Sub B from H
	if ((beakMemory.getA() - beakMemory.getH()) < 0x00)
	{
		beakMemory.setA((beakMemory.getA() - beakMemory.getH()) + 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setCFlag(beakMemory.getA() < beakMemory.getH());
		beakMemory.setHFlag((beakMemory.getA() & 0x0F) < (beakMemory.getH() & 0x0F));
		//beakMemory.setHFlag(beakMemory.getA() < beakMemory.getH());
		//beakMemory.setHFlag((beakMemory.getA() > 0x0F) && ((beakMemory.getA() - beakMemory.getH()) <= 0x0F));
		beakMemory.setA(beakMemory.getA() - beakMemory.getH());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		//beakMemory.setCFlag(false);
	}

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
}

void sharpCPU::opcode95()
{
	//Sub L from A
	if ((beakMemory.getA() - beakMemory.getL()) < 0x00)
	{
		beakMemory.setA((beakMemory.getA() - beakMemory.getL()) + 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setCFlag(beakMemory.getA() < beakMemory.getL());
		beakMemory.setHFlag((beakMemory.getA() & 0x0F) < (beakMemory.getL() & 0x0F));
		//beakMemory.setHFlag((beakMemory.getA() > 0x0F) && ((beakMemory.getA() - beakMemory.getL()) <= 0x0F));
		beakMemory.setA(beakMemory.getA() - beakMemory.getL());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		//beakMemory.setCFlag(false);
	}

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
}

void sharpCPU::opcode96()
{
	//Sub data at HL from A
	if ((beakMemory.getA() - beakMemory.readMemory(beakMemory.getHL())) < 0x00)
	{
		beakMemory.setA((beakMemory.getA() - beakMemory.readMemory(beakMemory.getHL())) + 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setCFlag(beakMemory.getA() < beakMemory.readMemory(beakMemory.getHL()));
		beakMemory.setHFlag((beakMemory.getA() & 0x0F) < (beakMemory.readMemory(beakMemory.getHL()) & 0x0F));
		//beakMemory.setHFlag(beakMemory.getA() < beakMemory.readMemory(beakMemory.getHL()));
		//beakMemory.setHFlag((beakMemory.getA() > 0x0F) && ((beakMemory.getA() - beakMemory.readMemory(beakMemory.getHL())) <= 0x0F));
		beakMemory.setA(beakMemory.getA() - beakMemory.readMemory(beakMemory.getHL()));
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		//beakMemory.setCFlag(false);
	}

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
}

void sharpCPU::opcode97()
{
	//Sub A from A
	if ((beakMemory.getA() - beakMemory.getA()) < 0x00)
	{
		beakMemory.setA((beakMemory.getA() - beakMemory.getA()) + 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setCFlag(false);
		beakMemory.setHFlag(false);
		//beakMemory.setHFlag(beakMemory.getA() < beakMemory.getA());
		//beakMemory.setHFlag((beakMemory.getA() > 0x0F) && ((beakMemory.getA() - beakMemory.getA()) <= 0x0F));
		beakMemory.setA(beakMemory.getA() - beakMemory.getA());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		//beakMemory.setCFlag(false);
	}

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
}

void sharpCPU::opcode98()
{
	//Sub B and Carry flag from A
	if ((beakMemory.getA() - (beakMemory.getB() + beakMemory.getCFlag())) < 0x00)
	{
		beakMemory.setA((beakMemory.getA() - (beakMemory.getB() + beakMemory.getCFlag())) + 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag((beakMemory.getA() & 0x0F) < ((beakMemory.getB() & 0x0F) + beakMemory.getCFlag()));
		beakMemory.setA(beakMemory.getA() - (beakMemory.getB() + beakMemory.getCFlag()));
		beakMemory.setCFlag(false);
	}

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
}

void sharpCPU::opcode99()
{
	//Sub C and Carry flag from A
	if ((beakMemory.getA() - (beakMemory.getC() + beakMemory.getCFlag())) < 0x00)
	{
		beakMemory.setA((beakMemory.getA() - (beakMemory.getC() + beakMemory.getCFlag())) + 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag((beakMemory.getA() & 0x0F) < ((beakMemory.getC() & 0x0F) + beakMemory.getCFlag()));
		beakMemory.setA(beakMemory.getA() - (beakMemory.getC() + beakMemory.getCFlag()));
		beakMemory.setCFlag(false);
	}

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
}

void sharpCPU::opcode9A()
{
	//Sub D and Carry flag from A
	if ((beakMemory.getA() - (beakMemory.getD() + beakMemory.getCFlag())) < 0x00)
	{
		beakMemory.setA((beakMemory.getA() - (beakMemory.getD() + beakMemory.getCFlag())) + 256);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag((beakMemory.getA() & 0x0F) < ((beakMemory.getD() & 0x0F) + beakMemory.getCFlag()));
		beakMemory.setA(beakMemory.getA() - (beakMemory.getD() + beakMemory.getCFlag()));
		beakMemory.setCFlag(false);
	}

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
}

void sharpCPU::opcode9B()
{
	//Sub E and Carry flag from A
	if ((beakMemory.getA() - (beakMemory.getE() + beakMemory.getCFlag())) < 0x00)
	{
		beakMemory.setA((beakMemory.getA() - (beakMemory.getE() + beakMemory.getCFlag())) + 256);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag((beakMemory.getA() & 0x0F) < ((beakMemory.getE() & 0x0F) + beakMemory.getCFlag()));
		beakMemory.setA(beakMemory.getA() - (beakMemory.getE() + beakMemory.getCFlag()));
		beakMemory.setCFlag(false);
	}

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
}

void sharpCPU::opcode9C()
{
	//Sub H and Carry flag from A
	if ((beakMemory.getA() - (beakMemory.getH() + beakMemory.getCFlag())) < 0x00)
	{
		beakMemory.setA((beakMemory.getA() - (beakMemory.getH() + beakMemory.getCFlag())) + 256);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag((beakMemory.getA() & 0x0F) < ((beakMemory.getH() & 0x0F) + beakMemory.getCFlag()));
		beakMemory.setA(beakMemory.getA() - (beakMemory.getH() + beakMemory.getCFlag()));
		beakMemory.setCFlag(false);
	}

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
}

void sharpCPU::opcode9D()
{
	//Sub L and Carry flag from A
	if ((beakMemory.getA() - (beakMemory.getL() + beakMemory.getCFlag())) < 0x00)
	{
		beakMemory.setA(((beakMemory.getA() & 0x0F) - ((beakMemory.getL() & 0x0F) + beakMemory.getCFlag())) + 256);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(beakMemory.getA() < (beakMemory.getL() + beakMemory.getCFlag()));
		beakMemory.setA(beakMemory.getA() - (beakMemory.getL() + beakMemory.getCFlag()));
		beakMemory.setCFlag(false);
	}

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
}

void sharpCPU::opcode9E()
{
	//Sub data at HL and Carry flag from A
	if ((beakMemory.getA() - (beakMemory.readMemory(beakMemory.getHL()) + beakMemory.getCFlag())) < 0x00)
	{
		beakMemory.setA((beakMemory.getA() - (beakMemory.readMemory(beakMemory.getHL()) + beakMemory.getCFlag())) + 256);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag((beakMemory.getA() & 0x0F) < ((beakMemory.readMemory(beakMemory.getHL()) & 0x0F) + beakMemory.getCFlag()));
		beakMemory.setA(beakMemory.getA() - (beakMemory.readMemory(beakMemory.getHL()) + beakMemory.getCFlag()));
		beakMemory.setCFlag(false);
	}

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
}

void sharpCPU::opcode9F()
{
	//Sub A and Carry flag from A
	if ((beakMemory.getA() - (beakMemory.getA() + beakMemory.getCFlag())) < 0x00)
	{
		beakMemory.setA((beakMemory.getA() - (beakMemory.getA() + beakMemory.getCFlag())) + 256);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag((beakMemory.getA() & 0x0F) < ((beakMemory.getA() & 0x0F) + beakMemory.getCFlag()));
		beakMemory.setA(beakMemory.getA() - (beakMemory.getA() + beakMemory.getCFlag()));
		beakMemory.setCFlag(false);
	}

	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
}

void sharpCPU::opcodeA0()
{
	//And B from A
	beakMemory.setA(beakMemory.getA() & beakMemory.getB());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeA1()
{
	//And C from A
	beakMemory.setA(beakMemory.getA() & beakMemory.getC());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeA2()
{
	//And D from A
	beakMemory.setA(beakMemory.getA() & beakMemory.getD());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeA3()
{
	//And E from A
	beakMemory.setA(beakMemory.getA() & beakMemory.getE());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeA4()
{
	//And H from A
	beakMemory.setA(beakMemory.getA() & beakMemory.getH());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeA5()
{
	//And L from A
	beakMemory.setA(beakMemory.getA() & beakMemory.getL());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeA6()
{
	//And (HL) from A
	beakMemory.setA(beakMemory.getA() & beakMemory.readMemory(beakMemory.getHL()));
	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeA7()
{
	//And A from A
	beakMemory.setA(beakMemory.getA() & beakMemory.getA());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeA8()
{
	//XOR B from A
	beakMemory.setA(beakMemory.getA() ^ beakMemory.getB());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeA9()
{
	//XOR C from A
	beakMemory.setA(beakMemory.getA() ^ beakMemory.getC());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeAA()
{
	//XOR D from A
	beakMemory.setA(beakMemory.getA() ^ beakMemory.getD());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeAB()
{
	//XOR E from A
	beakMemory.setA(beakMemory.getA() ^ beakMemory.getE());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeAC()
{
	//XOR H from A
	beakMemory.setA(beakMemory.getA() ^ beakMemory.getH());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeAD()
{
	//XOR L from A
	beakMemory.setA(beakMemory.getA() ^ beakMemory.getL());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeAE()
{
	//XOR data at HL from A
	beakMemory.setA(beakMemory.getA() ^ beakMemory.readMemory(beakMemory.getHL()));
	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeAF()
{
	//XOR A from A
	beakMemory.setA(beakMemory.getA() ^ beakMemory.getA());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeB0()
{
	//OR B from A
	beakMemory.setA(beakMemory.getA() | beakMemory.getB());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeB1()
{
	//OR C from A
	beakMemory.setA(beakMemory.getA() | beakMemory.getC());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeB2()
{
	//OR D from A
	beakMemory.setA(beakMemory.getA() | beakMemory.getD());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeB3()
{
	//OR E from A
	beakMemory.setA(beakMemory.getA() | beakMemory.getE());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeB4()
{
	//OR H from A
	beakMemory.setA(beakMemory.getA() | beakMemory.getH());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeB5()
{
	//OR L from A
	beakMemory.setA(beakMemory.getA() | beakMemory.getL());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeB6()
{
	//OR (HL) from A
	beakMemory.setA(beakMemory.getA() | beakMemory.readMemory(beakMemory.getHL()));
	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeB7()
{
	//OR A from A
	beakMemory.setA(beakMemory.getA() | beakMemory.getA());
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeB8()
{
	//Compare B with A
	//byte test = beakMemory.getA() - beakMemory.getB();
	mClock += 1;
	tClock += 4;
	/*
	beakMemory.setZFlag((test == 0) ? 1 : 0); //set if A == n?
	beakMemory.setNFlag(true);
	//flagH set if no borrow from bit 4
	beakMemory.setHFlag((test > beakMemory.getA())); //check this
	//flagC set if no borrow (Set if A < n)
	beakMemory.setCFlag((test < 0) ? 1 : 0); //check this
	*/

	beakMemory.setZFlag((beakMemory.getA() == beakMemory.getB()) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag(((beakMemory.getA() & 0x0F) < (beakMemory.getB() & 0x0F)) ? 1 : 0);
	beakMemory.setCFlag((beakMemory.getA() < beakMemory.getB()) ? 1 : 0);
}

void sharpCPU::opcodeB9()
{
	//Compare C with A
	int test = beakMemory.getA() - beakMemory.getC();
	mClock += 1;
	tClock += 4;

	beakMemory.setZFlag((beakMemory.getA() == beakMemory.getC()) ? 1 : 0);
	beakMemory.setNFlag(true);
	//beakMemory.setHFlag((beakMemory.getA() > beakMemory.getC()));
	beakMemory.setHFlag(((beakMemory.getA() & 0x0F) < (beakMemory.getC() & 0x0F)) ? 1 : 0);
	beakMemory.setCFlag((beakMemory.getA() < beakMemory.getC()) ? 1 : 0);
}

void sharpCPU::opcodeBA()
{
	//Compare D with A
	byte test = beakMemory.getA() - beakMemory.getD();
	mClock += 1;
	tClock += 4;

	/*
	beakMemory.setZFlag((test == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag((test > beakMemory.getA()));
	beakMemory.setCFlag((test < 0) ? 1 : 0);
	*/

	beakMemory.setZFlag((beakMemory.getA() == beakMemory.getD()) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag(((beakMemory.getA() & 0x0F) < (beakMemory.getD() & 0x0F)) ? 1 : 0);
	beakMemory.setCFlag((beakMemory.getA() < beakMemory.getD()) ? 1 : 0);
}

void sharpCPU::opcodeBB()
{
	//Compare E with A
	byte test = beakMemory.getA() - beakMemory.getE();
	mClock += 1;
	tClock += 4;
	/*
	beakMemory.setZFlag((test == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag((test > beakMemory.getA()));
	beakMemory.setCFlag((test < 0) ? 1 : 0);
	*/
	beakMemory.setZFlag((beakMemory.getA() == beakMemory.getE()) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag(((beakMemory.getA() & 0x0F) < (beakMemory.getE() & 0x0F)) ? 1 : 0);
	beakMemory.setCFlag((beakMemory.getA() < beakMemory.getE()) ? 1 : 0);
}

void sharpCPU::opcodeBC()
{
	//Compare H with A
	byte test = beakMemory.getA() - beakMemory.getH();
	mClock += 1;
	tClock += 4;
	/*
	beakMemory.setZFlag((test == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag((test > beakMemory.getA()));
	beakMemory.setCFlag((test < 0) ? 1 : 0);
	*/
	beakMemory.setZFlag((beakMemory.getA() == beakMemory.getH()) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag(((beakMemory.getA() & 0x0F) < (beakMemory.getH() & 0x0F)) ? 1 : 0);
	beakMemory.setCFlag((beakMemory.getA() < beakMemory.getH()) ? 1 : 0);
}

void sharpCPU::opcodeBD()
{
	//Compare L with A
	byte test = beakMemory.getA() - beakMemory.getL();
	mClock += 1;
	tClock += 4;

	//beakMemory.setZFlag((test == 0) ? 1 : 0);
	//beakMemory.setNFlag(true);
	//beakMemory.setHFlag((test > beakMemory.getA()));
	//beakMemory.setCFlag((test < 0) ? 1 : 0);

	beakMemory.setZFlag((beakMemory.getA() == beakMemory.getL()) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag(((beakMemory.getA() & 0x0F) < (beakMemory.getL() & 0x0F)) ? 1 : 0);
	beakMemory.setCFlag((beakMemory.getA() < beakMemory.getL()) ? 1 : 0);
}

void sharpCPU::opcodeBE()
{
	//Compare data at HL with A
	//short test = beakMemory.getA() - beakMemory.getHL();
	byte n = beakMemory.readMemory(beakMemory.getHL());
	mClock += 2;
	tClock += 8;

	//beakMemory.setZFlag((test == 0) ? 1 : 0);
	//beakMemory.setNFlag(true);
	//beakMemory.setHFlag((test > beakMemory.getA()));
	//beakMemory.setCFlag((test < 0) ? 1 : 0);

	beakMemory.setZFlag((beakMemory.getA() == n) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag(((beakMemory.getA() & 0x0F) < (n & 0x0F)) ? 1 : 0);
	beakMemory.setCFlag((beakMemory.getA() < n) ? 1 : 0);
}

void sharpCPU::opcodeBF()
{
	//Compare A with A
	//byte test = beakMemory.getA() - beakMemory.getA();
	mClock += 1;
	tClock += 4;

	//beakMemory.setZFlag((test == 0) ? 1 : 0);
	//beakMemory.setNFlag(true);
	//beakMemory.setHFlag((test > beakMemory.getA()));
	//beakMemory.setCFlag((test < 0) ? 1 : 0);

	beakMemory.setZFlag((beakMemory.getA() == beakMemory.getA()) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag(((beakMemory.getA() & 0x0F) < (beakMemory.getA() & 0x0F)) ? 1 : 0);
	beakMemory.setCFlag((beakMemory.getA() < beakMemory.getA()) ? 1 : 0);
}

void sharpCPU::opcodeC0()
{
	//RET if Not Zero
	if (!beakMemory.getZFlag())
	{
		memoryPointer = (beakMemory.readMemory(stackPointer + 1) << 8) | (beakMemory.readMemory(stackPointer));
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

void sharpCPU::opcodeC1()
{
	//POP into BC
	beakMemory.setBC((beakMemory.readMemory(stackPointer + 1) << 8) | (beakMemory.readMemory(stackPointer)));
	stackPointer += 2;
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeC2(short nn)
{
	//Jump if Not Zero
	if (!beakMemory.getZFlag())
	{
		memoryPointer = nn;
		mClock += 4;
		tClock += 16;
	}
	else
	{
		mClock += 3;
		tClock += 12;
	}
}

void sharpCPU::opcodeC3(short nn)
{
	//Jump to NNNN
	memoryPointer = nn;
	mClock += 4;
	tClock += 16;
}

void sharpCPU::opcodeC4(short nn)
{
	//Call nn if Not Zero
	if (!beakMemory.getZFlag())
	{
		stackPointer -= 2;
		beakMemory.writeMemory(stackPointer, memoryPointer);
		memoryPointer = nn;
		mClock += 6;
		tClock += 24;
	}
	else
	{
		mClock += 3;
		tClock += 12;
	}
}

void sharpCPU::opcodeC5()
{
	//Push BC
	stackPointer -= 2;
	beakMemory.writeMemory(stackPointer, beakMemory.getBC());
	mClock += 4;
	tClock += 16;
}

void sharpCPU::opcodeC6(byte n)
{
	//Add byte to A
	if ((beakMemory.getA() + n) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + n) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (n & 0x0F)) > 0x0F);
		//beakMemory.setHFlag((beakMemory.getA() <= 0x0F) && ((beakMemory.getA() + n) > 0x0F));
		beakMemory.setA(beakMemory.getA() + n);
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcodeC7()
{
	//Reset to 00
	stackPointer -= 2;
	beakMemory.writeMemory(stackPointer, memoryPointer);
	memoryPointer = 0x00;
	mClock += 4;
	tClock += 16;

}

void sharpCPU::opcodeC8()
{
	//Ret if Zero
	if (beakMemory.getZFlag())
	{
		memoryPointer = (beakMemory.readMemory(stackPointer + 1) << 8) | (beakMemory.readMemory(stackPointer));
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

void sharpCPU::opcodeC9()
{
	//Ret
	memoryPointer = (beakMemory.readMemory(stackPointer + 1) << 8) | (beakMemory.readMemory(stackPointer));
	stackPointer += 2;
	mClock += 4;
	tClock += 16;
}

void sharpCPU::opcodeCA(short nn)
{
	//Jump to nn if Zero
	if (beakMemory.getZFlag())
	{
		memoryPointer = nn;
		mClock += 4;
		tClock += 16;
	}
	else
	{
		mClock += 3;
		tClock += 12;
	}
}

void sharpCPU::opcodeCC(short nn)
{
	//Call nn if Zero
	if (beakMemory.getZFlag())
	{
		stackPointer -= 2;
		beakMemory.writeMemory(stackPointer, memoryPointer);
		memoryPointer = nn;
		mClock += 6;
		tClock += 24;
	}
	else
	{
		mClock += 3;
		tClock += 12;
	}
}

void sharpCPU::opcodeCD(short nn)
{
	//Call nn
	stackPointer -= 2;
	beakMemory.writeMemory(stackPointer, memoryPointer);
	memoryPointer = nn;
	mClock += 6;
	tClock += 24;
}

void sharpCPU::opcodeCE(byte n)
{
	//Add n and Carry flag to A
	//beakMemory.setA(beakMemory.getA() + n + beakMemory.getCFlag());
	if ((beakMemory.getA() + n + beakMemory.getCFlag()) > 0xFF)
	{
		beakMemory.setA((beakMemory.getA() + n + beakMemory.getCFlag()) - 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((beakMemory.getA() & 0x0F) + (n & 0x0F) + beakMemory.getCFlag()) > 0x0F);
		//beakMemory.setHFlag((beakMemory.getA() <= 0x0F) && ((beakMemory.getA() + n + beakMemory.getCFlag()) > 0x0F));
		beakMemory.setA(beakMemory.getA() + n + beakMemory.getCFlag());
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}
	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getA() == 0);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcodeCF()
{
	//Reset to 08
	stackPointer -= 2;
	beakMemory.writeMemory(stackPointer, memoryPointer);
	memoryPointer = 0x08;
	mClock += 4;
	tClock += 16;
}

void sharpCPU::opcodeD0()
{
	//Ret if not Carry
	if (!beakMemory.getCFlag())
	{
		memoryPointer = (beakMemory.readMemory(stackPointer + 1) << 8) | (beakMemory.readMemory(stackPointer));
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

void sharpCPU::opcodeD1()
{
	//POP DE
	beakMemory.setDE((beakMemory.readMemory(stackPointer + 1) << 8) | (beakMemory.readMemory(stackPointer)));
	stackPointer += 2;
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeD2(short nn)
{
	//Jump to nn if not Carry
	if (!beakMemory.getCFlag())
	{
		memoryPointer = nn;
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

void sharpCPU::opcodeD4(short nn)
{
	//Call nn if Not Carry
	if (!beakMemory.getCFlag())
	{
		stackPointer -= 2;
		beakMemory.writeMemory(stackPointer, memoryPointer);
		memoryPointer = nn;
		mClock += 6;
		tClock += 24;
	}
	else
	{
		mClock += 3;
		tClock += 12;
	}
}

void sharpCPU::opcodeD5()
{
	//Push DE
	stackPointer -= 2;
	beakMemory.writeMemory(stackPointer, beakMemory.getDE());
	mClock += 4;
	tClock += 16;
}

void sharpCPU::opcodeD6(byte n)
{
	//Subtract n from A

	if ((beakMemory.getA() - n) < 0x00)
	{
		beakMemory.setA((beakMemory.getA() - n) + 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag((beakMemory.getA() & 0x0F) < (n & 0x0F));
		beakMemory.setA(beakMemory.getA() - n);
		beakMemory.setCFlag(false);
	}

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);

}

void sharpCPU::opcodeD7()
{
	//Reset to 10
	stackPointer -= 2;
	beakMemory.writeMemory(stackPointer, memoryPointer);
	memoryPointer = 0x10;
	mClock += 4;
	tClock += 16;
}

void sharpCPU::opcodeD8()
{
	//Ret if Carry
	if (beakMemory.getCFlag())
	{
		memoryPointer = (beakMemory.readMemory(stackPointer + 1) << 8) | (beakMemory.readMemory(stackPointer));
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

void sharpCPU::opcodeD9()
{
	//Return and enable Interrupts
	memoryPointer = (beakMemory.readMemory(stackPointer + 1) << 8) | (beakMemory.readMemory(stackPointer));
	stackPointer += 2;
	interruptsEnabled = true;
	mClock += 4;
	tClock += 16;
}

void sharpCPU::opcodeDA(short nn)
{
	//Jump to nn if Carry
	if (beakMemory.getCFlag())
	{
		memoryPointer = nn;
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

void sharpCPU::opcodeDC(short nn)
{
	//Call nn if Carry
	if (beakMemory.getCFlag())
	{
		stackPointer -= 2;
		beakMemory.writeMemory(stackPointer, memoryPointer);
		memoryPointer = nn;
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

void sharpCPU::opcodeDE(byte n)
{
	//Sub n and Carry flag from A
	if ((beakMemory.getA() - (n + beakMemory.getCFlag())) < 0x00)
	{
		beakMemory.setA((beakMemory.getA() - (n + beakMemory.getCFlag())) + 256);//0xFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(beakMemory.getA() < (n + beakMemory.getCFlag()));
		//beakMemory.setHFlag((beakMemory.getA() > 0x0F) && (beakMemory.getA() - (n + beakMemory.getCFlag()) <= 0x0F));
		beakMemory.setA(beakMemory.getA() - (n + beakMemory.getCFlag()));
		//beakMemory.setHFlag((((beakMemory.getA()) & 0x0F) == 0xF) ? 1 : 0);
		beakMemory.setCFlag(false);
	}

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(true);
}

void sharpCPU::opcodeDF()
{
	//Reset to 18
	stackPointer -= 2;
	beakMemory.writeMemory(stackPointer, memoryPointer);
	memoryPointer = 0x18;
	mClock += 4;
	tClock += 16;
}

void sharpCPU::opcodeE0(byte n)
{
	//Load A into address at (FF00 + n)
	beakMemory.writeMemory(0xFF00 + n, beakMemory.getA());
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeE1()
{
	//Pop HL
	beakMemory.setHL((beakMemory.readMemory(stackPointer + 1) << 8) | (beakMemory.readMemory(stackPointer)));
	stackPointer += 2;
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeE2()
{
	//Load A into address at (FF00 + C)
	beakMemory.writeMemory(0xFF00 + beakMemory.getC(), beakMemory.getA());
	mClock += 2;
	tClock += 8;
}

//Opcode E3 does not exist?

//Opcode E4 does not exist?

void sharpCPU::opcodeE5()
{
	//Push HL
	stackPointer -= 2;
	beakMemory.writeMemory(stackPointer, beakMemory.getHL());
	mClock += 4;
	tClock += 16;
}

void sharpCPU::opcodeE6(byte n)
{
	//And n from A
	beakMemory.setA(beakMemory.getA() & n);
	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeE7()
{
	//Reset to 20
	stackPointer -= 2;
	beakMemory.writeMemory(stackPointer, memoryPointer);
	memoryPointer = 0x20;
	mClock += 4;
	tClock += 16;
}

void sharpCPU::opcodeE8(signed char n)
{
	//Add n to Stack Pointer

	if ((stackPointer + (signed char)n) > 0xFFFF)
	{
		beakMemory.setStackPointer((stackPointer + (signed char)n) - 65536);//0xFFFF);
		beakMemory.setHFlag(true);
		beakMemory.setCFlag(true);
	}
	else
	{
		beakMemory.setHFlag(((stackPointer & 0x0F) + ((signed char)n & 0x0F)) > 0x0F);
		beakMemory.setStackPointer(stackPointer + (signed char)n);
		//beakMemory.setHFlag((stackPointer & 0x00FF) == 0xF0);
		beakMemory.setCFlag(false);
	}
	mClock += 4;
	tClock += 16;

	//beakMemory.setZFlag(stackPointer > 0); //From tests in BGB this is not set
	beakMemory.setZFlag(false);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcodeE9()
{
	//Jump to HL
	memoryPointer = beakMemory.getHL();
	mClock += 1;
	tClock += 4;
}

void sharpCPU::opcodeEA(short nn)
{
	//Store A at short
	beakMemory.writeMemory(nn, beakMemory.getA());
	mClock += 4;
	tClock += 16;
}

//Opcode EB doesn't exist?

//Opcode EC doesn't exist?

//Opcode ED doesn't exist?

void sharpCPU::opcodeEE(byte n)
{
	//XOR byte with A
	beakMemory.setA(beakMemory.getA() ^ n);
	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeEF()
{
	//Reset to 28
	stackPointer -= 2;
	beakMemory.writeMemory(stackPointer, memoryPointer);
	memoryPointer = 0x28;
	mClock += 4;
	tClock += 16;
}

void sharpCPU::opcodeF0(byte n)
{
	//Load data at (FF00 + n) into A
	beakMemory.setA(beakMemory.readMemory(0xFF00 + n));
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeF1()
{
	//Pop AF
	beakMemory.setAF((beakMemory.readMemory(stackPointer + 1) << 8) | (beakMemory.readMemory(stackPointer)));
	stackPointer += 2;
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeF2()
{
	//Load data at (FF00 + C) into A
	beakMemory.setA(beakMemory.readMemory(0xFF00 + beakMemory.getC()));
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeF3()
{
	//Disable Interrupts
	interruptsEnabled = false;
	mClock += 1;
	tClock += 4;
}

//Opcode F4 doesn't exist?

void sharpCPU::opcodeF5()
{
	//Push AF
	stackPointer -= 2;
	beakMemory.writeMemory(stackPointer, beakMemory.getAF());
	mClock += 4;
	tClock += 16;
}

void sharpCPU::opcodeF6(byte n)
{
	//OR byte with A
	beakMemory.setA(beakMemory.getA() | n);
	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeF7()
{
	//Reset to 30
	stackPointer -= 2;
	beakMemory.writeMemory(stackPointer, memoryPointer);
	memoryPointer = 0x30;
	mClock += 4;
	tClock += 16;
}

void sharpCPU::opcodeF8(byte n)
{
	//Load SP + n into HL

	if ((stackPointer + n) > 0xFF)
	{
		beakMemory.setCFlag(true);
	}

	if (((stackPointer & 0x0F) + (n & 0x0F)) > 0x0F)
	{
		beakMemory.setHFlag(true);
	}

	beakMemory.setHL((short)(stackPointer + n));

	mClock += 3;
	tClock += 12;

	beakMemory.setZFlag(false);
	beakMemory.setNFlag(false);
}

void sharpCPU::opcodeF9()
{
	//Load SP into HL
	stackPointer = beakMemory.getHL();
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeFA(short nn)
{
	//Load data at short into A
	beakMemory.setA(beakMemory.readMemory(nn));
	mClock += 4;
	tClock += 16;
}

void sharpCPU::opcodeFB()
{
	//Enable Interrupts
	enableInterruptsNextCycle = true;
	//interruptsEnabled = true;
	mClock += 1;
	tClock += 4;
}
//Opcode FC doesn't exist?

//Opcode FD doesn't exist?

void sharpCPU::opcodeFE(byte n)
{
	//Compare n with A
	//byte test = beakMemory.getA() - n;
	mClock += 2;
	tClock += 8;

	//beakMemory.setZFlag((test == 0) ? 1 : 0);
	//beakMemory.setNFlag(true);
	//beakMemory.setHFlag((test > beakMemory.getA()));
	//beakMemory.setCFlag((test < 0) ? 1 : 0);

	beakMemory.setZFlag((beakMemory.getA() == n) ? 1 : 0);
	beakMemory.setNFlag(true);
	beakMemory.setHFlag(((beakMemory.getA() & 0x0F) < (n & 0x0F)) ? 1 : 0);
	beakMemory.setCFlag((beakMemory.getA() < n) ? 1 : 0);
}

void sharpCPU::opcodeFF()
{
	//Reset to 38
	//beakStack[--stackPointer] = memoryPointer;
	//beakMemory.writeMemory(--stackPointer, memoryPointer);
	stackPointer -= 2;
	beakMemory.writeMemory(stackPointer, memoryPointer);
	memoryPointer = 0x38;
	mClock += 4;
	tClock += 16;
}

void sharpCPU::opcodeCB00()
{
	//Rotate B Left, put previous bit 7 into Carry flag

	beakMemory.setB(rotateLeft(beakMemory.getB()));

	beakMemory.setCFlag(beakMemory.getB() & 0x01);
	beakMemory.setZFlag(beakMemory.getB() == 0);


	//beakMemory.setB (beakMemory.getB() << 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB01()
{
	//Rotate C Left, put previous bit 7 into Carry flag

	beakMemory.setC(rotateLeft(beakMemory.getC()));

	beakMemory.setCFlag(beakMemory.getC() & 0x01);
	beakMemory.setZFlag(beakMemory.getC() == 0);


	//beakMemory.setC(beakMemory.getC() << 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB02()
{
	//Rotate D Left, put previous bit 7 into Carry flag

	beakMemory.setD(rotateLeft(beakMemory.getD()));

	beakMemory.setCFlag(beakMemory.getD() & 0x01);
	beakMemory.setZFlag(beakMemory.getD() == 0);


	//beakMemory.setD(beakMemory.getD() << 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB03()
{
	//Rotate E Left, put previous bit 7 into Carry flag

	beakMemory.setE(rotateLeft(beakMemory.getE()));

	beakMemory.setCFlag(beakMemory.getE() & 0x01);
	beakMemory.setZFlag(beakMemory.getE() == 0);


	//beakMemory.setE(beakMemory.getE() << 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB04()
{
	//Rotate H Left, put previous bit 7 into Carry flag

	beakMemory.setH(rotateLeft(beakMemory.getH()));

	beakMemory.setCFlag(beakMemory.getH() & 0x01);
	beakMemory.setZFlag(beakMemory.getH() == 0);


	//beakMemory.setH(beakMemory.getH() << 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB05()
{
	//Rotate L Left, put previous bit 7 into Carry flag

	beakMemory.setL(rotateLeft(beakMemory.getL()));

	beakMemory.setCFlag(beakMemory.getL() & 0x01);
	beakMemory.setZFlag(beakMemory.getL() == 0);


	//beakMemory.setL(beakMemory.getL() << 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB06()
{
	//Rotate data in HL Left, put previous bit 7 into Carry flag

	beakMemory.writeMemory(beakMemory.getHL(), rotateLeft(beakMemory.readMemory(beakMemory.getHL())));

	beakMemory.setCFlag(beakMemory.readMemory(beakMemory.getHL()) & 0x01);
	beakMemory.setZFlag(beakMemory.readMemory(beakMemory.getHL()) == 0);


	//beakMemory.writeMemory(beakMemory.getHL(), (byte)(beakMemory.readMemory(beakMemory.getHL()) << 1));

	mClock += 3;
	tClock += 12;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB07()
{
	//Rotate A Left, put previous bit 7 into Carry flag

	beakMemory.setA(rotateLeft(beakMemory.getA()));

	beakMemory.setCFlag(beakMemory.getA() & 0x01);
	beakMemory.setZFlag(beakMemory.getA() == 0);


	//beakMemory.setA(beakMemory.getA() << 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB08()
{
	//Rotate B Right, put previous bit 0 into Carry flag

	beakMemory.setB(rotateRight(beakMemory.getB()));

	beakMemory.setCFlag(((beakMemory.getB() & 0x80) >> 7) > 0);
	beakMemory.setZFlag(beakMemory.getB() == 0);


	//beakMemory.setB(beakMemory.getB() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB09()
{
	//Rotate C Right, put previous bit 0 into Carry flag

	beakMemory.setC(rotateRight(beakMemory.getC()));

	beakMemory.setCFlag(((beakMemory.getC() & 0x80) >> 7) > 0);
	beakMemory.setZFlag(beakMemory.getC() == 0);


	//beakMemory.setC(beakMemory.getC() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB0A()
{
	//Rotate D Right, put previous bit 0 into Carry flag

	beakMemory.setD(rotateRight(beakMemory.getD()));

	beakMemory.setCFlag(((beakMemory.getD() & 0x80) >> 7) > 0);
	beakMemory.setZFlag(beakMemory.getD() == 0);

	//beakMemory.setD(beakMemory.getD() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB0B()
{
	//Rotate E Right, put previous bit 0 into Carry flag

	beakMemory.setE(rotateRight(beakMemory.getE()));

	beakMemory.setCFlag(((beakMemory.getE() & 0x80) >> 7) > 0);
	beakMemory.setZFlag(beakMemory.getE() == 0);


	//beakMemory.setE(beakMemory.getE() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB0C()
{
	//Rotate H Right, put previous bit 0 into Carry flag

	beakMemory.setH(rotateRight(beakMemory.getH()));

	beakMemory.setCFlag(((beakMemory.getH() & 0x80) >> 7) > 0);
	beakMemory.setZFlag(beakMemory.getH() == 0);

	//beakMemory.setH(beakMemory.getH() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB0D()
{
	//Rotate L Right, put previous bit 0 into Carry flag

	beakMemory.setL(rotateRight(beakMemory.getL()));

	beakMemory.setCFlag(((beakMemory.getL() & 0x80) >> 7) > 0);
	beakMemory.setZFlag(beakMemory.getL() == 0);


	//beakMemory.setL(beakMemory.getL() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB0E()
{
	//Rotate data at HL Right, put previous bit 0 into Carry flag

	beakMemory.writeMemory(beakMemory.getHL(), (byte)(rotateRight(beakMemory.readMemory(beakMemory.getHL()))));

	beakMemory.setB(rotateRight(beakMemory.getB()));
	beakMemory.setCFlag(((beakMemory.readMemory(beakMemory.getHL()) & 0x80) >> 7) > 0);
	beakMemory.setZFlag(beakMemory.readMemory(beakMemory.getHL()) == 0);


	//beakMemory.writeMemory(beakMemory.getHL(), (byte)(beakMemory.readMemory(beakMemory.getHL()) >> 1));

	mClock += 3;
	tClock += 12;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB0F()
{
	//Rotate A Right, put previous bit 0 into Carry flag (Does not Or C flag in)

	beakMemory.setA(rotateRight(beakMemory.getA()));

	beakMemory.setCFlag(((beakMemory.getA() & 0x80) >> 7) > 0);
	beakMemory.setZFlag(beakMemory.getA() == 0);


	//beakMemory.setA(beakMemory.getA() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB10()
{
	//Rotate B Left
	//beakMemory.setB(rotateLeft(beakMemory.getB()));

	byte oldBit = (beakMemory.getB() & 0x80) >> 7;
	beakMemory.setB((beakMemory.getB() << 1) | (byte)beakMemory.getCFlag());
	beakMemory.setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getB() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB11()
{
	//Rotate C Left
	//beakMemory.setC(rotateLeft(beakMemory.getC()));

	byte oldBit = (beakMemory.getC() & 0x80) >> 7;
	beakMemory.setC((beakMemory.getC() << 1) | (byte)beakMemory.getCFlag());
	beakMemory.setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getC() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB12()
{
	//Rotate D Left

	byte oldBit = (beakMemory.getD() & 0x80) >> 7;
	beakMemory.setD((beakMemory.getD() << 1) | (byte)beakMemory.getCFlag());
	beakMemory.setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getD() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB13()
{
	//Rotate E Left

	byte oldBit = (beakMemory.getE() & 0x80) >> 7;
	beakMemory.setE((beakMemory.getE() << 1) | (byte)beakMemory.getCFlag());
	beakMemory.setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getE() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB14()
{
	//Rotate H Left

	byte oldBit = (beakMemory.getH() & 0x80) >> 7;
	beakMemory.setH((beakMemory.getH() << 1) | (byte)beakMemory.getCFlag());
	beakMemory.setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getH() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB15()
{
	//Rotate L Left

	byte oldBit = (beakMemory.getL() & 0x80) >> 7;
	beakMemory.setL((beakMemory.getL() << 1) | (byte)beakMemory.getCFlag());
	beakMemory.setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getL() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB16()
{
	//Rotate data at HL Left

	byte oldBit = (beakMemory.readMemory(beakMemory.getHL()) & 0x8000) >> 0xF;
	beakMemory.writeMemory(beakMemory.getHL(), (byte)((beakMemory.readMemory(beakMemory.getHL()) << 1) | (byte)beakMemory.getCFlag()));
	beakMemory.setCFlag(oldBit > 0);

	mClock += 3;
	tClock += 12;

	beakMemory.setZFlag(beakMemory.readMemory(beakMemory.getHL()) == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB17()
{
	//Rotate A Left

	byte oldBit = (beakMemory.getA() & 0x80) >> 7;
	beakMemory.setA((beakMemory.getA() << 1) | (byte)beakMemory.getCFlag());
	beakMemory.setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getA() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB18()
{
	//Rotate B Right

	byte oldBit = (beakMemory.getB() & 0x01);
	beakMemory.setB((beakMemory.getB() >> 1) | (beakMemory.getCFlag() << 7));
	beakMemory.setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getB() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);

}

void sharpCPU::opcodeCB19()
{
	//Rotate C Right

	byte oldBit = (beakMemory.getC() & 0x01);
	beakMemory.setC((beakMemory.getC() >> 1) | (beakMemory.getCFlag() << 7));
	beakMemory.setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getC() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB1A()
{
	//Rotate D Right

	byte oldBit = (beakMemory.getD() & 0x01);
	beakMemory.setD((beakMemory.getD() >> 1) | (beakMemory.getCFlag() << 7));
	beakMemory.setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getD() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB1B()
{
	//Rotate E Right

	byte oldBit = (beakMemory.getE() & 0x01);
	beakMemory.setE((beakMemory.getE() >> 1) | (beakMemory.getCFlag() << 7));
	beakMemory.setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getE() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB1C()
{
	//Rotate H Right

	byte oldBit = (beakMemory.getH() & 0x01);
	beakMemory.setH((beakMemory.getH() >> 1) | (beakMemory.getCFlag() << 7));
	beakMemory.setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getH() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB1D()
{
	//Rotate L Right

	byte oldBit = (beakMemory.getL() & 0x01);
	beakMemory.setL((beakMemory.getL() >> 1) | (beakMemory.getCFlag() << 7));
	beakMemory.setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getL() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB1E()
{
	//Rotate/Shift HL Right

	byte oldBit = (beakMemory.readMemory(beakMemory.getHL()) & 0x01);
	beakMemory.writeMemory(beakMemory.getHL(), (byte)((beakMemory.readMemory(beakMemory.getHL()) >> 1) | (beakMemory.getCFlag() << 0xF)));
	beakMemory.setCFlag(oldBit > 0);

	mClock += 3;
	tClock += 12;

	beakMemory.setZFlag(beakMemory.readMemory(beakMemory.getHL()) == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB1F()
{
	//Rotate A Right

	byte oldBit = (beakMemory.getA() & 0x01);
	beakMemory.setA((beakMemory.getA() >> 1) | (beakMemory.getCFlag() << 7));
	beakMemory.setCFlag(oldBit > 0);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getA() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB20()
{
	//Shift B Left - Set Carry to old Bit 7

	beakMemory.setCFlag(((beakMemory.getB() & 0x80) >> 7) > 0);
	beakMemory.setB(beakMemory.getB() << 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getB() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB21()
{
	//Shift C Left - Set Carry to old Bit 7

	beakMemory.setCFlag(((beakMemory.getC() & 0x80) >> 7) > 0);
	beakMemory.setC(beakMemory.getC() << 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getC() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB22()
{
	//Shift D Left - Set Carry to old Bit 7

	beakMemory.setCFlag(((beakMemory.getD() & 0x80) >> 7) > 0);
	beakMemory.setD(beakMemory.getD() << 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getD() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB23()
{
	//Shift E Left - Set Carry to old Bit 7

	beakMemory.setCFlag(((beakMemory.getE() & 0x80) >> 7) > 0);
	beakMemory.setE(beakMemory.getE() << 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getE() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB24()
{
	//Shift H Left - Set Carry to old Bit 7

	beakMemory.setCFlag(((beakMemory.getH() & 0x80) >> 7) > 0);
	beakMemory.setH(beakMemory.getH() << 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getH() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB25()
{
	//Shift L Left - Set Carry to old Bit 7

	beakMemory.setCFlag(((beakMemory.getL() & 0x80) >> 7) > 0);
	beakMemory.setL(beakMemory.getL() << 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getL() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB26()
{
	//Shift data at HL Left - Set Carry to old Bit 7

	beakMemory.setCFlag(((beakMemory.readMemory(beakMemory.getHL()) & 0x8000) >> 0xF) > 0);
	beakMemory.writeMemory(beakMemory.getHL(), (byte)(beakMemory.readMemory(beakMemory.getHL()) << 1));

	mClock += 3;
	tClock += 12;

	beakMemory.setZFlag(beakMemory.readMemory(beakMemory.getHL()) == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB27()
{
	//Shift A Left - Set Carry to old Bit 7

	beakMemory.setCFlag(((beakMemory.getA() & 0x80) >> 7) > 0);
	beakMemory.setA(beakMemory.getA() << 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getA() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB28()
{
	//Shift B Right - Set Carry to old Bit 0

	beakMemory.setCFlag(beakMemory.getB() & 0x01);
	beakMemory.setB(beakMemory.getB() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getB() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB29()
{
	//Shift C Right - Set Carry to old Bit 0

	beakMemory.setCFlag(beakMemory.getC() & 0x01);
	beakMemory.setC(beakMemory.getC() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getC() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB2A()
{
	//Shift D Right - Set Carry to old Bit 0

	beakMemory.setCFlag(beakMemory.getD() & 0x01);
	beakMemory.setD(beakMemory.getD() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getD() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB2B()
{
	//Shift E Right - Set Carry to old Bit 0

	beakMemory.setCFlag(beakMemory.getE() & 0x01);
	beakMemory.setE(beakMemory.getE() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getE() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB2C()
{
	//Shift H Right - Set Carry to old Bit 0

	beakMemory.setCFlag(beakMemory.getH() & 0x01);
	beakMemory.setH(beakMemory.getH() >> 1);


	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getH() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB2D()
{
	//Shift L Right - Set Carry to old Bit 0

	beakMemory.setCFlag(beakMemory.getL() & 0x01);
	beakMemory.setL(beakMemory.getL() >> 1);


	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getL() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB2E()
{
	//Shift data at HL Right - Set Carry to old Bit 0

	beakMemory.setCFlag(beakMemory.readMemory(beakMemory.getHL()) & 0x01);
	beakMemory.writeMemory(beakMemory.getHL(), (byte)(beakMemory.readMemory(beakMemory.getHL()) >> 1));

	mClock += 3;
	tClock += 12;

	beakMemory.setZFlag(beakMemory.getHL() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB2F()
{
	//Shift A Right - Set Carry to old Bit 0

	beakMemory.setCFlag(beakMemory.getA() & 0x01);
	beakMemory.setA(beakMemory.getA() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getA() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB30()
{
	//Swap nibbles in B
	byte b = beakMemory.getB();
	b = ((b & 0x0F) << 4) | ((b & 0xF0) >> 4);
	beakMemory.setB(b);
	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getB() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeCB31()
{
	//Swap nibbles in C
	byte c = beakMemory.getC();
	c = ((c & 0x0F) << 4) | ((c & 0xF0) >> 4);
	beakMemory.setC(c);
	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getC() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeCB32()
{
	//Swap nibbles in D
	byte d = beakMemory.getD();
	d = ((d & 0x0F) << 4) | ((d & 0xF0) >> 4);
	beakMemory.setD(d);
	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getD() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeCB33()
{
	//Swap nibbles in E
	byte e = beakMemory.getC();
	e = ((e & 0x0F) << 4) | ((e & 0xF0) >> 4);
	beakMemory.setE(e);
	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getE() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeCB34()
{
	//Swap nibbles in H
	byte h = beakMemory.getH();
	h = ((h & 0x0F) << 4) | ((h & 0xF0) >> 4);
	beakMemory.setH(h);
	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getH() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeCB35()
{
	//Swap nibbles in L
	byte l = beakMemory.getL();
	l = ((l & 0x0F) << 4) | ((l & 0xF0) >> 4);
	beakMemory.setL(l);
	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getL() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}


void sharpCPU::opcodeCB36()
{
	//Swap nibbles in memory at HL
	short hl = beakMemory.getHL();
	byte hlData = beakMemory.readMemory(hl);
	hlData = ((hlData & 0x0F) << 4) | ((hlData & 0xF0) >> 4);
	beakMemory.writeMemory(hl, hlData);
	mClock += 3;
	tClock += 12;

	beakMemory.setZFlag((beakMemory.readMemory(hl) == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeCB37()
{
	//Swap nibbles in A
	byte a = beakMemory.getA();
	a = ((a & 0x0F) << 4) | ((a & 0xF0) >> 4);
	beakMemory.setA(a);
	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag((beakMemory.getA() == 0) ? 1 : 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
	beakMemory.setCFlag(false);
}

void sharpCPU::opcodeCB38()
{
	//Shift B Right
	beakMemory.setCFlag(beakMemory.getB() & 0x01);
	beakMemory.setB(beakMemory.getB() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getB() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB39()
{
	//Shift C Right
	beakMemory.setCFlag(beakMemory.getC() & 0x01);
	beakMemory.setC(beakMemory.getC() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getC() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB3A()
{
	//Shift D Right
	beakMemory.setCFlag(beakMemory.getD() & 0x01);
	beakMemory.setD(beakMemory.getD() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getD() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB3B()
{
	//Shift E Right
	beakMemory.setCFlag(beakMemory.getE() & 0x01);
	beakMemory.setE(beakMemory.getE() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getE() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB3C()
{
	//Shift H Right
	beakMemory.setCFlag(beakMemory.getH() & 0x01);
	beakMemory.setH(beakMemory.getH() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getH() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB3D()
{
	//Shift L Right
	beakMemory.setCFlag(beakMemory.getL() & 0x01);
	beakMemory.setL(beakMemory.getL() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getL() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB3E()
{
	//Shift data at HL Right
	beakMemory.setCFlag(beakMemory.readMemory(beakMemory.getHL()) & 0x01);
	beakMemory.writeMemory(beakMemory.getHL(), (byte)(beakMemory.readMemory(beakMemory.getHL()) >> 1));

	mClock += 3;
	tClock += 12;

	beakMemory.setZFlag(beakMemory.readMemory(beakMemory.getHL()) == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB3F()
{
	//Shift A Right
	beakMemory.setCFlag(beakMemory.getA() & 0x01);
	beakMemory.setA(beakMemory.getA() >> 1);

	mClock += 2;
	tClock += 8;

	beakMemory.setZFlag(beakMemory.getA() == 0);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(false);
}

void sharpCPU::opcodeCB40()
{
	//Test bit 0 in B
	beakMemory.setZFlag(((beakMemory.getB() & 0x01) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB41()
{
	//Test bit 0 in C
	beakMemory.setZFlag(((beakMemory.getC() & 0x01) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB42()
{
	//Test bit 0 in D
	beakMemory.setZFlag(((beakMemory.getD() & 0x01) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB43()
{
	//Test bit 0 in E
	beakMemory.setZFlag(((beakMemory.getE() & 0x01) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB44()
{
	//Test bit 0 in H
	beakMemory.setZFlag(((beakMemory.getH() & 0x01) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB45()
{
	//Test bit 0 in L
	beakMemory.setZFlag(((beakMemory.getL() & 0x01) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB46()
{
	//Test bit 0 in data at HL
	short hl = beakMemory.getHL();
	beakMemory.setZFlag(((beakMemory.readMemory(hl) & 0x01) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCB47()
{
	//Test bit 0 in A
	beakMemory.setZFlag(((beakMemory.getA() & 0x01) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB48()
{
	//Test bit 1 in B
	beakMemory.setZFlag((((beakMemory.getB() & 0x02) >> 1) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB49()
{
	//Test bit 1 in C
	beakMemory.setZFlag((((beakMemory.getC() & 0x02) >> 1) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB4A()
{
	//Test bit 1 in D
	beakMemory.setZFlag((((beakMemory.getD() & 0x02) >> 1) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB4B()
{
	//Test bit 1 in E
	beakMemory.setZFlag((((beakMemory.getE() & 0x02) >> 1) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB4C()
{
	//Test bit 1 in H
	beakMemory.setZFlag((((beakMemory.getH() & 0x02) >> 1) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB4D()
{
	//Test bit 1 in L
	beakMemory.setZFlag((((beakMemory.getL() & 0x02) >> 1) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB4E()
{
	//Test bit 1 in data at HL
	short hl = beakMemory.getHL();
	beakMemory.setZFlag((((beakMemory.readMemory(hl) & 0x02) >> 1) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCB4F()
{
	//Test bit 1 in A
	beakMemory.setZFlag((((beakMemory.getA() & 0x02) >> 1) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB50()
{
	//Test bit 2 in B
	beakMemory.setZFlag((((beakMemory.getB() & 0x04) >> 2) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB51()
{
	//Test bit 2 in C
	beakMemory.setZFlag((((beakMemory.getC() & 0x04) >> 2) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB52()
{
	//Test bit 2 in D
	beakMemory.setZFlag((((beakMemory.getD() & 0x04) >> 2) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB53()
{
	//Test bit 2 in E
	beakMemory.setZFlag((((beakMemory.getE() & 0x04) >> 2) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB54()
{
	//Test bit 2 in H
	beakMemory.setZFlag((((beakMemory.getH() & 0x04) >> 2) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB55()
{
	//Test bit 2 in L
	beakMemory.setZFlag((((beakMemory.getL() & 0x04) >> 2) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB56()
{
	//Test bit 2 in data at HL
	short hl = beakMemory.getHL();
	beakMemory.setZFlag((((beakMemory.readMemory(hl) & 0x04) >> 2) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCB57()
{
	//Test bit 2 in A
	beakMemory.setZFlag((((beakMemory.getA() & 0x04) >> 2) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB58()
{
	//Test bit 3 in B
	beakMemory.setZFlag((((beakMemory.getB() & 0x08) >> 3) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB59()
{
	//Test bit 3 in C
	beakMemory.setZFlag((((beakMemory.getC() & 0x08) >> 3) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB5A()
{
	//Test bit 3 in D
	beakMemory.setZFlag((((beakMemory.getD() & 0x08) >> 3) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB5B()
{
	//Test bit 3 in E
	beakMemory.setZFlag((((beakMemory.getE() & 0x08) >> 3) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB5C()
{
	//Test bit 3 in H
	beakMemory.setZFlag((((beakMemory.getH() & 0x08) >> 3) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB5D()
{
	//Test bit 3 in L
	beakMemory.setZFlag((((beakMemory.getL() & 0x08) >> 3) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB5E()
{
	//Test bit 3 in data at HL
	short hl = beakMemory.getHL();
	beakMemory.setZFlag((((beakMemory.readMemory(hl) & 0x08) >> 3) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCB5F()
{
	//Test bit 3 in A
	beakMemory.setZFlag((((beakMemory.getA() & 0x08) >> 3) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB60()
{
	//Test bit 4 in B
	beakMemory.setZFlag((((beakMemory.getB() & 0x10) >> 4) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB61()
{
	//Test bit 4 in C
	beakMemory.setZFlag((((beakMemory.getC() & 0x10) >> 4) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB62()
{
	//Test bit 4 in D
	beakMemory.setZFlag((((beakMemory.getD() & 0x10) >> 4) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB63()
{
	//Test bit 4 in E
	beakMemory.setZFlag((((beakMemory.getE() & 0x10) >> 4) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB64()
{
	//Test bit 4 in H
	beakMemory.setZFlag((((beakMemory.getH() & 0x10) >> 4) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB65()
{
	//Test bit 4 in L
	beakMemory.setZFlag((((beakMemory.getL() & 0x10) >> 4) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB66()
{
	//Test bit 4 in data at HL
	short hl = beakMemory.getHL();
	beakMemory.setZFlag((((beakMemory.readMemory(hl) & 0x10) >> 4) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCB67()
{
	//Test bit 4 in A
	beakMemory.setZFlag((((beakMemory.getA() & 0x10) >> 4) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB68()
{
	//Test bit 5 in B
	beakMemory.setZFlag((((beakMemory.getB() & 0x20) >> 5) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB69()
{
	//Test bit 5 in C
	beakMemory.setZFlag((((beakMemory.getC() & 0x20) >> 5) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB6A()
{
	//Test bit 5 in D
	beakMemory.setZFlag((((beakMemory.getD() & 0x20) >> 5) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB6B()
{
	//Test bit 5 in E
	beakMemory.setZFlag((((beakMemory.getE() & 0x20) >> 5) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB6C()
{
	//Test bit 5 in H
	beakMemory.setZFlag((((beakMemory.getH() & 0x20) >> 5) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB6D()
{
	//Test bit 5 in L
	beakMemory.setZFlag((((beakMemory.getL() & 0x20) >> 5) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB6E()
{
	//Test bit 5 in data at HL
	short hl = beakMemory.getHL();
	beakMemory.setZFlag((((beakMemory.readMemory(hl) & 0x20) >> 5) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCB6F()
{
	//Test bit 5 in A
	beakMemory.setZFlag((((beakMemory.getA() & 0x20) >> 5) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB70()
{
	//Test bit 6 in B
	beakMemory.setZFlag((((beakMemory.getB() & 0x40) >> 6) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB71()
{
	//Test bit 6 in C
	beakMemory.setZFlag((((beakMemory.getC() & 0x40) >> 6) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB72()
{
	//Test bit 6 in D
	beakMemory.setZFlag((((beakMemory.getD() & 0x40) >> 6) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB73()
{
	//Test bit 6 in E
	beakMemory.setZFlag((((beakMemory.getE() & 0x40) >> 6) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB74()
{
	//Test bit 6 in H
	beakMemory.setZFlag((((beakMemory.getH() & 0x40) >> 6) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB75()
{
	//Test bit 6 in L
	beakMemory.setZFlag((((beakMemory.getL() & 0x40) >> 6) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB76()
{
	//Test bit 6 in data at HL
	short hl = beakMemory.getHL();
	beakMemory.setZFlag((((beakMemory.readMemory(hl) & 0x40) >> 6) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCB77()
{
	//Test bit 6 in A
	beakMemory.setZFlag((((beakMemory.getA() & 0x40) >> 6) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB78()
{
	//Test bit 7 in B
	beakMemory.setZFlag((((beakMemory.getB() & 0x80) >> 7) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB79()
{
	//Test bit 7 in C
	beakMemory.setZFlag((((beakMemory.getC() & 0x80) >> 7) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB7A()
{
	//Test bit 7 in D
	beakMemory.setZFlag((((beakMemory.getD() & 0x80) >> 7) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB7B()
{
	//Test bit 7 in E
	beakMemory.setZFlag((((beakMemory.getE() & 0x80) >> 7) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB7C()
{
	//Test bit 7 in H
	beakMemory.setZFlag((((beakMemory.getH() & 0x80) >> 7) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB7D()
{
	//Test bit 7 in L
	beakMemory.setZFlag((((beakMemory.getL() & 0x80) >> 7) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB7E()
{
	//Test bit 7 in data at HL
	short hl = beakMemory.getHL();
	beakMemory.setZFlag((((beakMemory.readMemory(hl) & 0x80) >> 7) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCB7F()
{
	//Test bit 7 in A
	beakMemory.setZFlag((((beakMemory.getA() & 0x80) >> 7) == 0) ? true : false);
	beakMemory.setNFlag(false);
	beakMemory.setHFlag(true);

	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB80()
{
	//Reset bit 0 in B
	beakMemory.setB(beakMemory.getB() & 0xFE); //Masks off left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB81()
{
	//Reset bit 0 in C
	beakMemory.setC(beakMemory.getC() & 0xFE); //Masks off left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB82()
{
	//Reset bit 0 in D
	beakMemory.setD(beakMemory.getD() & 0xFE); //Masks off left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB83()
{
	//Reset bit 0 in E
	beakMemory.setE(beakMemory.getE() & 0xFE); //Masks off left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB84()
{
	//Reset bit 0 in H
	beakMemory.setH(beakMemory.getH() & 0xFE); //Masks off left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB85()
{
	//Reset bit 0 of data at L
	beakMemory.setL(beakMemory.getL() & 0xFE); //Masks off left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB86()
{
	//Reset bit 0 in HL
	short hl = beakMemory.getHL();
	beakMemory.writeMemory(hl, (byte)(beakMemory.readMemory(hl) & 0xFE)); //Masks off left most bit
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCB87()
{
	//Reset bit 0 of data at A
	beakMemory.setA(beakMemory.getA() & 0xFE); //Masks off left most bit
	mClock += 2;
	tClock += 8;
}


void sharpCPU::opcodeCB88()
{
	//Reset bit 1 in B
	beakMemory.setB(beakMemory.getB() & 0xFD); //Masks off second to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB89()
{
	//Reset bit 1 in C
	beakMemory.setC(beakMemory.getC() & 0xFD); //Masks off second to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB8A()
{
	//Reset bit 1 in D
	beakMemory.setD(beakMemory.getD() & 0xFD); //Masks off second to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB8B()
{
	//Reset bit 1 in E
	beakMemory.setE(beakMemory.getE() & 0xFD); //Masks off second to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB8C()
{
	//Reset bit 1 in H
	beakMemory.setH(beakMemory.getH() & 0xFD); //Masks off second to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB8D()
{
	//Reset bit 1 in L
	beakMemory.setL(beakMemory.getL() & 0xFD); //Masks off second to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB8E()
{
	//Reset bit 1 in HL
	short hl = beakMemory.getHL();
	beakMemory.writeMemory(hl, (byte)(beakMemory.readMemory(hl) & 0xFD)); //Masks off left most bit
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCB8F()
{
	//Reset bit 1 in A
	beakMemory.setA(beakMemory.getA() & 0xFD); //Masks off second to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB90()
{
	//Reset bit 2 in B
	beakMemory.setB(beakMemory.getB() & 0xFB); //Masks off third to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB91()
{
	//Reset bit 2 in C
	beakMemory.setC(beakMemory.getC() & 0xFB); //Masks off third to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB92()
{
	//Reset bit 2 in D
	beakMemory.setD(beakMemory.getD() & 0xFB); //Masks off third to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB93()
{
	//Reset bit 2 in E
	beakMemory.setE(beakMemory.getE() & 0xFB); //Masks off third to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB94()
{
	//Reset bit 2 in H
	beakMemory.setH(beakMemory.getH() & 0xFB); //Masks off third to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB95()
{
	//Reset bit 2 in L
	beakMemory.setL(beakMemory.getL() & 0xFB); //Masks off third to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB96()
{
	//Reset bit 2 in HL
	short hl = beakMemory.getHL();
	beakMemory.writeMemory(hl, (byte)(beakMemory.readMemory(hl) & 0xFB)); //Masks off left most bit
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCB97()
{
	//Reset bit 2 in A
	beakMemory.setA(beakMemory.getA() & 0xFB); //Masks off third to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB98()
{
	//Reset bit 3 in B
	beakMemory.setB(beakMemory.getB() & 0xF7); //Masks off fourth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB99()
{
	//Reset bit 3 in C
	beakMemory.setC(beakMemory.getC() & 0xF7); //Masks off fourth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB9A()
{
	//Reset bit 3 in D
	beakMemory.setD(beakMemory.getD() & 0xF7); //Masks off fourth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB9B()
{
	//Reset bit 3 in E
	beakMemory.setE(beakMemory.getE() & 0xF7); //Masks off fourth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB9C()
{
	//Reset bit 3 in H
	beakMemory.setH(beakMemory.getH() & 0xF7); //Masks off fourth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB9D()
{
	//Reset bit 3 in L
	beakMemory.setL(beakMemory.getL() & 0xF7); //Masks off fourth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCB9E()
{
	//Reset bit 3 in HL
	short hl = beakMemory.getHL();
	beakMemory.writeMemory(hl, (byte)(beakMemory.readMemory(hl) & 0xF7)); //Masks off left most bit
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCB9F()
{
	//Reset bit 3 in A
	beakMemory.setA(beakMemory.getA() & 0xF7); //Masks off fourth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBA0()
{
	//Reset bit 4 in B
	beakMemory.setB(beakMemory.getB() & 0xEF); //Masks off fifth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBA1()
{
	//Reset bit 4 in C
	beakMemory.setC(beakMemory.getC() & 0xEF); //Masks off fifth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBA2()
{
	//Reset bit 4 in D
	beakMemory.setD(beakMemory.getD() & 0xEF); //Masks off fifth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBA3()
{
	//Reset bit 4 in E
	beakMemory.setE(beakMemory.getE() & 0xEF); //Masks off fifth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBA4()
{
	//Reset bit 4 in H
	beakMemory.setH(beakMemory.getH() & 0xEF); //Masks off fifth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBA5()
{
	//Reset bit 4 in L
	beakMemory.setL(beakMemory.getL() & 0xEF); //Masks off fifth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBA6()
{
	//Reset bit 4 in HL
	short hl = beakMemory.getHL();
	beakMemory.writeMemory(hl, (byte)(beakMemory.readMemory(hl) & 0xEF)); //Masks off left most bit
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCBA7()
{
	//Reset bit 4 in A
	beakMemory.setA(beakMemory.getA() & 0xEF); //Masks off fifth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBA8()
{
	//Reset bit 5 in B
	beakMemory.setB(beakMemory.getB() & 0xDF); //Masks off sixth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBA9()
{
	//Reset bit 5 in C
	beakMemory.setC(beakMemory.getC() & 0xDF); //Masks off sixth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBAA()
{
	//Reset bit 5 in D
	beakMemory.setD(beakMemory.getD() & 0xDF); //Masks off sixth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBAB()
{
	//Reset bit 5 in E
	beakMemory.setE(beakMemory.getE() & 0xDF); //Masks off sixth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBAC()
{
	//Reset bit 5 in H
	beakMemory.setH(beakMemory.getH() & 0xDF); //Masks off sixth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBAD()
{
	//Reset bit 5 in L
	beakMemory.setL(beakMemory.getL() & 0xDF); //Masks off sixth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBAE()
{
	//Reset bit 5 in HL
	short hl = beakMemory.getHL();
	beakMemory.writeMemory(hl, (byte)(beakMemory.readMemory(hl) & 0xDF)); //Masks off left most bit
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCBAF()
{
	//Reset bit 5 in A
	beakMemory.setA(beakMemory.getA() & 0xDF); //Masks off sixth to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBB0()
{
	//Reset bit 6 in B
	beakMemory.setB(beakMemory.getB() & 0xBF); //Masks off seventh to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBB1()
{
	//Reset bit 6 in C
	beakMemory.setC(beakMemory.getC() & 0xBF); //Masks off seventh to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBB2()
{
	//Reset bit 6 in D
	beakMemory.setD(beakMemory.getD() & 0xBF); //Masks off seventh to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBB3()
{
	//Reset bit 6 in E
	beakMemory.setE(beakMemory.getE() & 0xBF); //Masks off seventh to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBB4()
{
	//Reset bit 6 in H
	beakMemory.setH(beakMemory.getH() & 0xBF); //Masks off seventh to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBB5()
{
	//Reset bit 6 in L
	beakMemory.setL(beakMemory.getL() & 0xBF); //Masks off seventh to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBB6()
{
	//Reset bit 6 in HL
	short hl = beakMemory.getHL();
	beakMemory.writeMemory(hl, (byte)(beakMemory.readMemory(hl) & 0xBF)); //Masks off left most bit
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCBB7()
{
	//Reset bit 6 in A
	beakMemory.setA(beakMemory.getA() & 0xBF); //Masks off seventh to left most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBB8()
{
	//Reset bit 7 in B
	beakMemory.setB(beakMemory.getB() & 0x7F); //Masks off right most bit
	mClock += 2;
	tClock += 8;
}
void sharpCPU::opcodeCBB9()
{
	//Reset bit 7 in C
	beakMemory.setC(beakMemory.getC() & 0x7F); //Masks off right most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBBA()
{
	//Reset bit 7 in D
	beakMemory.setD(beakMemory.getD() & 0x7F); //Masks off right most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBBB()
{
	//Reset bit 7 in E
	beakMemory.setE(beakMemory.getE() & 0x7F); //Masks off right most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBBC()
{
	//Reset bit 7 in H
	beakMemory.setH(beakMemory.getH() & 0x7F); //Masks off right most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBBD()
{
	//Reset bit 7 in L
	beakMemory.setL(beakMemory.getL() & 0x7F); //Masks off right most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBBE()
{
	//Reset bit 7 in HL
	short hl = beakMemory.getHL();
	beakMemory.writeMemory(hl, (byte)(beakMemory.readMemory(hl) & 0x7F)); //Masks off left most bit
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCBBF()
{
	//Reset bit 7 in A
	beakMemory.setA(beakMemory.getA() & 0x7F); //Masks off right most bit
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBC0()
{
	//Set Bit 0 of B
	beakMemory.setB(beakMemory.getB() | 0x01);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBC1()
{
	//Set Bit 0 of C
	beakMemory.setC(beakMemory.getC() | 0x01);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBC2()
{
	//Set Bit 0 of D
	beakMemory.setD(beakMemory.getD() | 0x01);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBC3()
{
	//Set Bit 0 of E
	beakMemory.setE(beakMemory.getE() | 0x01);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBC4()
{
	//Set Bit 0 of H
	beakMemory.setH(beakMemory.getH() | 0x01);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBC5()
{
	//Set Bit 0 of L
	beakMemory.setL(beakMemory.getL() | 0x01);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBC6()
{
	//Set Bit 0 of data at HL
	beakMemory.writeMemory(beakMemory.getHL(), (byte)(beakMemory.readMemory(beakMemory.getHL()) | 0x01));
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCBC7()
{
	//Set Bit 0 of A
	beakMemory.setA(beakMemory.getA() | 0x01);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBC8()
{
	//Set Bit 1 of B
	beakMemory.setB(beakMemory.getB() | 0x02);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBC9()
{
	//Set Bit 1 of C
	beakMemory.setC(beakMemory.getC() | 0x02);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBCA()
{
	//Set Bit 1 of D
	beakMemory.setD(beakMemory.getD() | 0x02);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBCB()
{
	//Set Bit 1 of E
	beakMemory.setE(beakMemory.getE() | 0x02);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBCC()
{
	//Set Bit 1 of H
	beakMemory.setH(beakMemory.getH() | 0x02);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBCD()
{
	//Set Bit 1 of L
	beakMemory.setL(beakMemory.getL() | 0x02);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBCE()
{
	//Set Bit 1 of data at HL
	short hl = beakMemory.getHL();
	beakMemory.writeMemory(hl, (byte)(beakMemory.readMemory(hl) | 0x02));
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCBCF()
{
	//Set Bit 1 of A
	beakMemory.setA(beakMemory.getA() | 0x02);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBD0()
{
	//Set Bit 2 of B
	beakMemory.setB(beakMemory.getB() | 0x04);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBD1()
{
	//Set Bit 2 of C
	beakMemory.setC(beakMemory.getC() | 0x04);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBD2()
{
	//Set Bit 2 of D
	beakMemory.setD(beakMemory.getD() | 0x04);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBD3()
{
	//Set Bit 2 of E
	beakMemory.setE(beakMemory.getE() | 0x04);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBD4()
{
	//Set Bit 2 of H
	beakMemory.setH(beakMemory.getH() | 0x04);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBD5()
{
	//Set Bit 2 of L
	beakMemory.setL(beakMemory.getL() | 0x04);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBD6()
{
	//Set Bit 2 of data at HL
	short hl = beakMemory.getHL();
	beakMemory.writeMemory(hl, (byte)(beakMemory.readMemory(hl) | 0x04));
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCBD7()
{
	//Set Bit 2 of A
	beakMemory.setA(beakMemory.getA() | 0x04); 
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBD8()
{
	//Set Bit 3 of B
	beakMemory.setB(beakMemory.getB() | 0x08);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBD9()
{
	//Set Bit 3 of C
	beakMemory.setC(beakMemory.getC() | 0x08); 
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBDA()
{
	//Set Bit 3 of D
	beakMemory.setD(beakMemory.getD() | 0x08);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBDB()
{
	//Set Bit 3 of E
	beakMemory.setE(beakMemory.getE() | 0x08);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBDC()
{
	//Set Bit 3 of H
	beakMemory.setH(beakMemory.getH() | 0x08); 
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBDD()
{
	//Set Bit 3 of L
	beakMemory.setL(beakMemory.getL() | 0x08);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBDE()
{
	//Set Bit 3 of data at HL
	short hl = beakMemory.getHL();
	beakMemory.writeMemory(hl, (byte)(beakMemory.readMemory(hl) | 0x08));
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCBDF()
{
	//Set Bit 3 of A
	beakMemory.setA(beakMemory.getA() | 0x08); 
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBE0()
{
	//Set Bit 4 of B
	beakMemory.setB(beakMemory.getB() | 0x10);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBE1()
{
	//Set Bit 4 of C
	beakMemory.setC(beakMemory.getC() | 0x10); 
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBE2()
{
	//Set Bit 4 of D
	beakMemory.setD(beakMemory.getD() | 0x10);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBE3()
{
	//Set Bit 4 of E
	beakMemory.setE(beakMemory.getE() | 0x10);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBE4()
{
	//Set Bit 4 of H
	beakMemory.setH(beakMemory.getH() | 0x10);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBE5()
{
	//Set Bit 4 of L
	beakMemory.setL(beakMemory.getL() | 0x10);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBE6()
{
	//Set Bit 4 of data at HL
	short hl = beakMemory.getHL();
	beakMemory.writeMemory(hl, (byte)(beakMemory.readMemory(hl) | 0x10));
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCBE7()
{
	//Set Bit 4 of A
	beakMemory.setA(beakMemory.getA() | 0x10);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBE8()
{
	//Set Bit 5 of B
	beakMemory.setB(beakMemory.getB() | 0x20);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBE9()
{
	//Set Bit 5 of C
	beakMemory.setC(beakMemory.getC() | 0x20);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBEA()
{
	//Set Bit 5 of D
	beakMemory.setD(beakMemory.getD() | 0x20);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBEB()
{
	//Set Bit 5 of E
	beakMemory.setE(beakMemory.getE() | 0x20);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBEC()
{
	//Set Bit 5 of H
	beakMemory.setH(beakMemory.getH() | 0x20);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBED()
{
	//Set Bit 5 of L
	beakMemory.setL(beakMemory.getL() | 0x20);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBEE()
{
	//Set Bit 5 of data at HL
	short hl = beakMemory.getHL();
	beakMemory.writeMemory(hl, (byte)(beakMemory.readMemory(hl) | 0x20));
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCBEF()
{
	//Set Bit 5 of A
	beakMemory.setA(beakMemory.getA() | 0x20);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBF0()
{
	//Set Bit 6 of B
	beakMemory.setB(beakMemory.getB() | 0x40);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBF1()
{
	//Set Bit 6 of C
	beakMemory.setC(beakMemory.getC() | 0x40);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBF2()
{
	//Set Bit 6 of D
	beakMemory.setD(beakMemory.getD() | 0x40);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBF3()
{
	//Set Bit 6 of E
	beakMemory.setE(beakMemory.getE() | 0x40); 
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBF4()
{
	//Set Bit 6 of H
	beakMemory.setH(beakMemory.getH() | 0x40);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBF5()
{
	//Set Bit 6 of L
	beakMemory.setL(beakMemory.getL() | 0x40);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBF6()
{
	//Set Bit 6 of data at HL
	short hl = beakMemory.getHL();
	beakMemory.writeMemory(hl, (byte)(beakMemory.readMemory(hl) | 0x40));
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCBF7()
{
	//Set Bit 6 of A
	beakMemory.setA(beakMemory.getA() | 0x40);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBF8()
{
	//Set Bit 7 of B
	beakMemory.setB(beakMemory.getB() | 0x80);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBF9()
{
	//Set Bit 7 of C
	beakMemory.setC(beakMemory.getC() | 0x80);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBFA()
{
	//Set Bit 7 of D
	beakMemory.setD(beakMemory.getD() | 0x80);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBFB()
{
	//Set Bit 7 of E
	beakMemory.setE(beakMemory.getE() | 0x80);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBFC()
{
	//Set Bit 7 of H
	beakMemory.setH(beakMemory.getH() | 0x80);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBFD()
{
	//Set Bit 7 of L
	beakMemory.setL(beakMemory.getL() | 0x80);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::opcodeCBFE()
{
	//Set Bit 7 of data at HL
	short hl = beakMemory.getHL();
	beakMemory.writeMemory(hl, (byte)(beakMemory.readMemory(hl) | 0x80));
	mClock += 3;
	tClock += 12;
}

void sharpCPU::opcodeCBFF()
{
	//Set Bit 7 of A
	beakMemory.setA(beakMemory.getA() | 0x80);
	mClock += 2;
	tClock += 8;
}

void sharpCPU::updateTIMA(int curClocks, int& clocksSinceLastTIMAUpdate, int& clocksSinceLastDIVUpdate)
{
	/*
	Purpose: Checks each loop cycle if enough cycles have passed to increment the timers.
	If so, it writes the incremented value to the timer register and requests an interrupt if it overflows.
	*/

	bool timerEnabled = ((beakMemory.readMemory(0xFF07) & 0x04) > 0);

	if (timerEnabled)
	{

		byte timerFrequency = beakMemory.readMemory(0xFF07) & 0x03;
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
			byte tima = beakMemory.readMemory(0xFF05);
			if (tima == 0xFF)
			{
				//Set Timer Overflow Interrupt Flag
				beakMemory.writeMemory((short)0xFF0F, (byte)(beakMemory.readMemory(0xFF0F) | 0x4));

				//Reset TIMA Value
				beakMemory.writeMemory((short)0xFF05, (byte)0);
			}
			else
			{
				beakMemory.writeMemory((short)0xFF05, (byte)(tima + 1));
			}
		}
	}

	if ((curClocks - clocksSinceLastDIVUpdate) >= 256) //16386 hz
	{
		beakMemory.writeMemory((short)0xFF04, (byte)(beakMemory.readMemory(0xFF04) + 1));
		clocksSinceLastDIVUpdate = curClocks;
	}
}

bool sharpCPU::checkForInterrupt()
{
	/*
	Purpose: Checks if there are any interrupts pending so that they can be serviced later. The intention is to be able to check with
	minimal effort and not having any functionality related to servicing the interrupt itself.
	*/

	byte IE = beakMemory.readMemory(0xFFFF);
	byte IF = beakMemory.readMemory(0xFF0F);

	for (int i = 0; i < 8; i++)
	{
		if ((IE & 0x01) == 1 && (IF & 0x01) == 1)
		{
			return true;
		}
		else
		{
			IE >>= 1;
			IF >>= 1;
		}
	}

	return false;
}

void sharpCPU::executeInterrupt()
{
	/*
	Purpose: Services any interrupts active in the IE and IF registers. If both IE and IF contain a matching bit, the current stack pointer
	is stored before jumping to the interrupt vector that corresponds to those enabled bits.
	*/

	byte IE = beakMemory.readMemory(0xFFFF);
	byte IF = beakMemory.readMemory(0xFF0F);

	stackPointer -= 2;
	beakMemory.writeMemory(stackPointer, memoryPointer);

	interruptsEnabled = false;

	//If there are several interrupts, VBLANK takes highest priority and goes down
	if (((IF & 0x01) == 1) && ((IE & 0x01) == 1))
	{
		//VBLANK
		memoryPointer = 0x0040;
		beakMemory.writeMemory(0xFF0F, (byte)(IF & 0xFE)); //Clear bit in IF
	}
	else if (((((IF & 0x02) >> 1) == 1) && ((IE & 0x02) >> 1 == 1)))
	{
		//LCD
		memoryPointer = 0x0048;
		beakMemory.writeMemory(0xFF0F, (byte)(IF & 0xFD)); //Clear bit in IF
	}
	else if (((((IF & 0x04) >> 2) == 1) && ((IE & 0x04) >> 2 == 1)))
	{
		//Timer Overflow
		memoryPointer = 0x0050;
		beakMemory.writeMemory(0xFF0F, (byte)(IF & 0xFB)); //Clear bit in IF
	}
	else if (((((IF & 0x08) >> 3) == 1) && ((IE & 0x08) >> 3 == 1)))
	{
		//Serial
		memoryPointer = 0x0058;
		beakMemory.writeMemory(0xFF0F, (byte)(IF & 0xF7)); //Clear bit in IF
	}
	else if (((((IF & 0x10) >> 4) == 1) && ((IE & 0x10) >> 4 == 1)))
	{
		//Joypad
		memoryPointer = 0x0060;
		beakMemory.writeMemory(0xFF0F, (byte)(IF & 0xEF)); //Clear bit in IF
	}

	mClock += 5;
	tClock += 20;
}

bool sharpCPU::checkForHaltOrInterrupt()
{
	/*
	Purpose: Allows interrupts or halts to be serviced if they are active.
	Otherwise, it will return false and the next assembly instruction will be executed as normal.
	*/

	if (interruptsEnabled) //IME
	{
		if (checkForInterrupt())
		{
			//End halt mode
			if (halt)
			{
				halt = false;
				mClock += 1;
				tClock += 4;
			}

			executeInterrupt();
			return true; //Temporary? This allows the opcode it is jumped to to be logged/shown in debugger instead of appearing skipped. Could cause a side effect by skipping a loop?
		}
		else if(halt)
		{
			return true;
		}
	}
	else
	{
		
		if (halt)
		{
			halt = false; 
			mClock += 1;
			tClock += 4;

			return true; //BGB and No$GB never escape DI+Halt
		}
		
	}

	return false;

	//write interrupt function. If flag in IE and IME are both set, push PC into stack, (disable interrupts?)
	//then jump to interrupt starting address per interrupt type
	//0040: Vertical Blankl Interrupt Start Address
	//0048:LCDC Status Interrupt Start Address
	//0050:Timer Overflow Interrupt Start Address
	//0058 Serial Transfer Completion Interrupt
	//0060 High to Low P10-P13 Interrupt Start Address
}


int sharpCPU::returnTClock()
{
	return tClock;
}

int sharpCPU::returnMClock()
{
	return mClock;
}

bool sharpCPU::returnHalt()
{
	return halt;
}

bool sharpCPU::returnInterrupt()
{
	return interrupt;
}

bool sharpCPU::returnIME()
{
	return interruptsEnabled;
}

bool sharpCPU::returnRepeat()
{
	return repeat;
}

void sharpCPU::setTClock(int newTClock)
{
	tClock = newTClock;
}

void sharpCPU::setmClock(int newMClock)
{
	mClock = newMClock;
}

void sharpCPU::setHalt(bool newHalt)
{
	halt = newHalt;
}

void sharpCPU::setIME(bool ime)
{
	interruptsEnabled = ime;
}

void sharpCPU::setInterrupt(bool newInterrupt)
{
	interrupt = newInterrupt;
}
void sharpCPU::setRepeat(bool newRepeat)
{
	repeat = newRepeat;
}
