#include "Debugger.h"
#include "Main.h"
#include "Memory.h"


tuple<string, int> disassembleInstruction(short address)
{
	byte opcode = beakMemory.readMemory(address);
	string opcodeString;
	int bytesRead;

	stringstream ss;

	switch (opcode & 0xF0)
	{
	case 0x00:
	{
		switch (opcode & 0x0F)
		{
		case 0:
		{
			opcodeString = "00 nop";
			bytesRead = 1;
			break;
		}
		case 1:
		{
			short argument = ((beakMemory.readMemory(address + 1)) | (beakMemory.readMemory(address + 2) << 8));
			ss << hex << argument;
			opcodeString = "01 " + ss.str() + " ld bc, " + ss.str();
			bytesRead = 3;
			ss.str("");
			break;
		}
		case 2:
		{
			short argument = ((beakMemory.readMemory(address + 1)) | (beakMemory.readMemory(address + 2) << 8));
			ss << hex << argument;
			opcodeString = "02 " + ss.str() + " ld (bc), " + ss.str();
			bytesRead = 3;
			ss.str("");
			break;
		}
		case 3:
		{
			opcodeString = "03 inc BC";
			bytesRead = 1;
			break;
		}
		case 4:
		{
			opcodeString = "04 inc B";
			bytesRead = 1;
			break;
		}
		case 5:
		{
			opcodeString = "05 dec B";
			bytesRead = 1;
			break;
		}
		case 6:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "06 " + ss.str() + " ld b, " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 7:
		{
			opcodeString = "07 rlca";
			bytesRead = 1;
			break;
		}
		case 8:
		{
			short argument = ((beakMemory.readMemory(address + 1)) | (beakMemory.readMemory(address + 2) << 8));
			ss << hex << argument;
			opcodeString = "08 " + ss.str() + " ld (" + ss.str() + "), sp";
			bytesRead = 3;
			ss.str("");
			break;
		}
		case 9:
		{
			opcodeString = "09 add hl, bc";
			bytesRead = 1;
			break;
		}
		case 0xA:
		{
			opcodeString = "0A ld, a, (bc)";
			bytesRead = 1;
			break;
		}
		case 0xB:
		{
			opcodeString = "0B dec bc";
			bytesRead = 1;
			break;
		}
		case 0xC:
		{
			opcodeString = "0C inc c";
			bytesRead = 1;
			break;
		}
		case 0xD:
		{
			opcodeString = "0D dec c";
			bytesRead = 1;
			break;
		}
		case 0xE:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "0E " + ss.str() + " ld c, " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 0xF:
		{
			opcodeString = "0F rrca";
			bytesRead = 1;
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
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "10 " + ss.str() + " stop ";
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 1:
		{
			short argument = ((beakMemory.readMemory(address + 1)) | (beakMemory.readMemory(address + 2) << 8));
			ss << hex << argument;
			opcodeString = "11 " + ss.str() + " ld de, " + ss.str();
			bytesRead = 3;
			ss.str("");
			break;
		}
		case 2:
		{
			opcodeString = "12 ld (de), a";
			bytesRead = 1;
			break;
		}
		case 3:
		{
			opcodeString = "13 inc de";
			bytesRead = 1;
			break;
		}
		case 4:
		{
			opcodeString = "14 inc d";
			bytesRead = 1;
			break;
		}
		case 5:
		{
			opcodeString = "15 dec d";
			bytesRead = 1;
			break;
		}
		case 6:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "16 " + ss.str() + " ld d, " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 7:
		{
			opcodeString = "17 rla";
			bytesRead = 1;
			break;
		}
		case 8:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			string hexArgument = ss.str();
			ss.str("");
			ss << hex << ((signed char)argument + address + 2);
			string jumpAddress = ss.str().substr(ss.str().length() - 2, 2);
			opcodeString = "18 " + hexArgument + " jr " + jumpAddress;
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 9:
		{
			opcodeString = "19 add hl, de";
			bytesRead = 1;
			break;
		}
		case 0xA:
		{
			opcodeString = "1A ld a, (de)";
			bytesRead = 1;
			break;
		}
		case 0xB:
		{
			opcodeString = "1B dec de";
			bytesRead = 1;
			break;
		}
		case 0xC:
		{
			opcodeString = "1C inc e";
			bytesRead = 1;
			break;
		}
		case 0xD:
		{
			opcodeString = "1D dec e";
			bytesRead = 1;
			break;
		}
		case 0xE:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "1E " + ss.str() + " ld e, " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 0xF:
		{
			opcodeString = "1F rra";
			bytesRead = 1;
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
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			string hexArgument = ss.str();
			ss.str("");
			ss << hex << ((signed char)argument + address + 2);
			string jumpAddress = ss.str();
			opcodeString = "20 " + hexArgument + " jr nz, " + jumpAddress;
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 1:
		{
			short argument1 = beakMemory.readMemory(address + 1);
			short argument2 = beakMemory.readMemory(address + 2);
			ss << hex << argument1;
			string byte1 = ss.str();
			ss.str("");
			ss << hex << argument2;
			string byte2 = ss.str();
			opcodeString = "21 " + byte1 + " " + byte2 + " ld hl, " + byte2 + byte1;
			bytesRead = 3;
			ss.str("");
			break;
		}
		case 2:
		{
			opcodeString = "22 ldi (hl), a";
			bytesRead = 1;
			break;
		}
		case 3:
		{
			opcodeString = "23 inc hl";
			bytesRead = 1;
			break;
		}
		case 4:
		{
			opcodeString = "24 inc h";
			bytesRead = 1;
			break;
		}
		case 5:
		{
			opcodeString = "25 dec h";
			bytesRead = 1;
			break;
		}
		case 6:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "26 " + ss.str() + " ld h, " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 7:
		{
			opcodeString = "27 daa";
			bytesRead = 1;
			break;
		}
		case 8:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			string hexArgument = ss.str();
			ss.str("");
			ss << hex << ((signed char)argument + address + 2);
			string jumpAddress = ss.str();
			opcodeString = "28 " + hexArgument + " jr z, " + jumpAddress;
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 9:
		{
			opcodeString = "29 add hl, hl";
			bytesRead = 1;
			break;
		}
		case 0xA:
		{
			opcodeString = "2A ldi a, (hl)";
			bytesRead = 1;
			break;
		}
		case 0xB:
		{
			opcodeString = "2B dec hl";
			bytesRead = 1;
			break;
		}
		case 0xC:
		{
			opcodeString = "2C inc l";
			bytesRead = 1;
			break;
		}
		case 0xD:
		{
			opcodeString = "2D dec l";
			bytesRead = 1;
			break;
		}
		case 0xE:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "2E " + ss.str() + " ld l, " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 0xF:
		{
			opcodeString = "2F cpl";
			bytesRead = 1;
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
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			string hexArgument = ss.str();
			ss.str("");
			ss << hex << ((signed char)argument + address + 2);
			string jumpAddress = ss.str();
			opcodeString = "30 " + hexArgument + " jr nc, " + jumpAddress;
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 1:
		{
			short argument = ((beakMemory.readMemory(address + 1)) | (beakMemory.readMemory(address + 2) << 8));
			ss << hex << argument;
			opcodeString = "31 " + ss.str() + " ld sp, " + ss.str();
			bytesRead = 3;
			ss.str("");
			break;
		}
		case 2:
		{
			opcodeString = "32 ldd (hl), a";
			bytesRead = 1;
			break;
		}
		case 3:
		{
			opcodeString = "33 inc sp";
			bytesRead = 1;
			break;
		}
		case 4:
		{
			opcodeString = "34 inc (hl)";
			bytesRead = 1;
			break;
		}
		case 5:
		{
			opcodeString = "35 dec (hl)";
			bytesRead = 1;
			break;
		}
		case 6:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "36 " + ss.str() + " ld (hl), " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 7:
		{
			opcodeString = "37 scf";
			bytesRead = 1;
			break;
		}
		case 8:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			string hexArgument = ss.str();
			ss.str("");
			ss << hex << ((signed char)argument + address + 2);
			string jumpAddress = ss.str();
			opcodeString = "38 " + hexArgument + " jr c, " + jumpAddress;
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 9:
		{
			opcodeString = "39 add hl, sp";
			bytesRead = 1;
			break;
		}
		case 0xA:
		{
			opcodeString = "3A ldd a, (hl)";
			bytesRead = 1;
			break;
		}
		case 0xB:
		{
			opcodeString = "3B dec sp";
			bytesRead = 1;
			break;
		}
		case 0xC:
		{
			opcodeString = "3C inc a";
			bytesRead = 1;
			break;
		}
		case 0xD:
		{
			opcodeString = "3D dec a";
			bytesRead = 1;
			break;
		}
		case 0xE:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "3E " + ss.str() + " ld a, " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 0xF:
		{
			opcodeString = "3F ccf";
			bytesRead = 1;
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
			opcodeString = "40 ld b, b";
			bytesRead = 1;
			break;
		}
		case 1:
		{
			opcodeString = "41 ld b, c";
			bytesRead = 1;
			break;
		}
		case 2:
		{
			opcodeString = "42 ld b, d";
			bytesRead = 1;
			break;
		}
		case 3:
		{
			opcodeString = "43 ld b, e";
			bytesRead = 1;
			break;
		}
		case 4:
		{
			opcodeString = "44 ld b, h";
			bytesRead = 1;
			break;
		}
		case 5:
		{
			opcodeString = "45 ld b, l";
			bytesRead = 1;
			break;
		}
		case 6:
		{
			opcodeString = "46 ld b, (hl)";
			bytesRead = 1;
			break;
		}
		case 7:
		{
			opcodeString = "47 ld b, a";
			bytesRead = 1;
			break;
		}
		case 8:
		{
			opcodeString = "48 ld c, b";
			bytesRead = 1;
			break;
		}
		case 9:
		{
			opcodeString = "49 ld c, c";
			bytesRead = 1;
			break;
		}
		case 0xA:
		{
			opcodeString = "4A ld c, d";
			bytesRead = 1;
			break;
		}
		case 0xB:
		{
			opcodeString = "4B ld c, e";
			bytesRead = 1;
			break;
		}
		case 0xC:
		{
			opcodeString = "4C ld c, h";
			bytesRead = 1;
			break;
		}
		case 0xD:
		{
			opcodeString = "4D ld c, l";
			bytesRead = 1;
			break;
		}
		case 0xE:
		{
			opcodeString = "4E ld c, (hl)";
			bytesRead = 1;
			break;
		}
		case 0xF:
		{
			opcodeString = "4F ld c, a";
			bytesRead = 1;
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
			opcodeString = "50 ld d, b";
			bytesRead = 1;
			break;
		}
		case 1:
		{
			opcodeString = "51 ld d, c";
			bytesRead = 1;
			break;
		}
		case 2:
		{
			opcodeString = "52 ld d, d";
			bytesRead = 1;
			break;
		}
		case 3:
		{
			opcodeString = "53 ld d, e";
			bytesRead = 1;
			break;
		}
		case 4:
		{
			opcodeString = "54 ld d, h";
			bytesRead = 1;
			break;
		}
		case 5:
		{
			opcodeString = "55 ld d, l";
			bytesRead = 1;
			break;
		}
		case 6:
		{
			opcodeString = "56 ld d, (hl)";
			bytesRead = 1;
			break;
		}
		case 7:
		{
			opcodeString = "56 ld d, a";
			bytesRead = 1;
			break;
		}
		case 8:
		{
			opcodeString = "58 ld e, b";
			bytesRead = 1;
			break;
		}
		case 9:
		{
			opcodeString = "59 ld e, c";
			bytesRead = 1;
			break;
		}
		case 0xA:
		{
			opcodeString = "5A ld e, d";
			bytesRead = 1;
			break;
		}
		case 0xB:
		{
			opcodeString = "5B ld e, e";
			bytesRead = 1;
			break;
		}
		case 0xC:
		{
			opcodeString = "5C ld e, h";
			bytesRead = 1;
			break;
		}
		case 0xD:
		{
			opcodeString = "5D ld e, l";
			bytesRead = 1;
			break;
		}
		case 0xE:
		{
			opcodeString = "5E ld e, (hl)";
			bytesRead = 1;
			break;
		}
		case 0xF:
		{
			opcodeString = "5F ld e, a";
			bytesRead = 1;
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
			opcodeString = "60 ld h, b";
			bytesRead = 1;
			break;
		}
		case 1:
		{
			opcodeString = "61 ld h, c";
			bytesRead = 1;
			break;
		}
		case 2:
		{
			opcodeString = "62 ld h, d";
			bytesRead = 1;
			break;
		}
		case 3:
		{
			opcodeString = "63 ld h, e";
			bytesRead = 1;
			break;
		}
		case 4:
		{
			opcodeString = "64 ld h, h";
			bytesRead = 1;
			break;
		}
		case 5:
		{
			opcodeString = "65 ld h, l";
			bytesRead = 1;
			break;
		}
		case 6:
		{
			opcodeString = "66 ld h, (hl)";
			bytesRead = 1;
			break;
		}
		case 7:
		{
			opcodeString = "67 ld h, a";
			bytesRead = 1;
			break;
		}
		case 8:
		{
			opcodeString = "68 ld l, b";
			bytesRead = 1;
			break;
		}
		case 9:
		{
			opcodeString = "69 ld l, c";
			bytesRead = 1;
			break;
		}
		case 0xA:
		{
			opcodeString = "6A ld l, d";
			bytesRead = 1;
			break;
		}
		case 0xB:
		{
			opcodeString = "6B ld l, e";
			bytesRead = 1;
			break;
		}
		case 0xC:
		{
			opcodeString = "6C ld l, h";
			bytesRead = 1;
			break;
		}
		case 0xD:
		{
			opcodeString = "6D ld l, l";
			bytesRead = 1;
			break;
		}
		case 0xE:
		{
			opcodeString = "6E ld l, (hl)";
			bytesRead = 1;
			break;
		}
		case 0xF:
		{
			opcodeString = "6F ld l, a";
			bytesRead = 1;
			break;
		}
		}
		break;
	}
	case 0x70:
	{
		switch (opcode & 0x0F)
		{
		case 0:
		{
			opcodeString = "70 ld (hl), b";
			bytesRead = 1;
			break;
		}
		case 1:
		{
			opcodeString = "71 ld (hl), c";
			bytesRead = 1;
			break;
		}
		case 2:
		{
			opcodeString = "72 ld (hl), d";
			bytesRead = 1;
			break;
		}
		case 3:
		{
			opcodeString = "73 ld (hl), e";
			bytesRead = 1;
			break;
		}
		case 4:
		{
			opcodeString = "74 ld (hl), h";
			bytesRead = 1;
			break;
		}
		case 5:
		{
			opcodeString = "75 ld (hl), l";
			bytesRead = 1;
			break;
		}
		case 6:
		{
			opcodeString = "76 halt";
			bytesRead = 1;
			break;
		}
		case 7:
		{
			opcodeString = "77 ld (hl), a";
			bytesRead = 1;
			break;
		}
		case 8:
		{
			opcodeString = "78 ld a, b";
			bytesRead = 1;
			break;
		}
		case 9:
		{
			opcodeString = "79 ld a, c";
			bytesRead = 1;
			break;
		}
		case 0xA:
		{
			opcodeString = "7A ld a, d";
			bytesRead = 1;
			break;
		}
		case 0xB:
		{
			opcodeString = "7B ld a, e";
			bytesRead = 1;
			break;
		}
		case 0xC:
		{
			opcodeString = "7C ld a, h";
			bytesRead = 1;
			break;
		}
		case 0xD:
		{
			opcodeString = "7D ld a, l";
			bytesRead = 1;
			break;
		}
		case 0xE:
		{
			opcodeString = "7E ld a, (hl)";
			bytesRead = 1;
			break;
		}
		case 0xF:
		{
			opcodeString = "7F ld a, a";
			bytesRead = 1;
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
			opcodeString = "80 add b";
			bytesRead = 1;
			break;
		}
		case 1:
		{
			opcodeString = "81 add c";
			bytesRead = 1;
			break;
		}
		case 2:
		{
			opcodeString = "82 add d";
			bytesRead = 1;
			break;
		}
		case 3:
		{
			opcodeString = "83 add e";
			bytesRead = 1;
			break;
		}
		case 4:
		{
			opcodeString = "84 add h";
			bytesRead = 1;
			break;
		}
		case 5:
		{
			opcodeString = "85 add l";
			bytesRead = 1;
			break;
		}
		case 6:
		{
			opcodeString = "86 add (hl)";
			bytesRead = 1;
			break;
		}
		case 7:
		{
			opcodeString = "87 add a";
			bytesRead = 1;
			break;
		}
		case 8:
		{
			opcodeString = "88 adc b";
			bytesRead = 1;
			break;
		}
		case 9:
		{
			opcodeString = "89 adc c";
			bytesRead = 1;
			break;
		}
		case 0xA:
		{
			opcodeString = "8A adc d";
			bytesRead = 1;
			break;
		}
		case 0xB:
		{
			opcodeString = "8B adc e";
			bytesRead = 1;
			break;
		}
		case 0xC:
		{
			opcodeString = "8C adc h";
			bytesRead = 1;
			break;
		}
		case 0xD:
		{
			opcodeString = "8D adc l";
			bytesRead = 1;
			break;
		}
		case 0xE:
		{
			opcodeString = "8E adc (hl)";
			bytesRead = 1;
			break;
		}
		case 0xF:
		{
			opcodeString = "8F adc a";
			bytesRead = 1;
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
			opcodeString = "90 sub b";
			bytesRead = 1;
			break;
		}
		case 1:
		{
			opcodeString = "91 sub c";
			bytesRead = 1;
			break;
		}
		case 2:
		{
			opcodeString = "92 sub d";
			bytesRead = 1;
			break;
		}
		case 3:
		{
			opcodeString = "93 sub e";
			bytesRead = 1;
			break;
		}
		case 4:
		{
			opcodeString = "94 sub h";
			bytesRead = 1;
			break;
		}
		case 5:
		{
			opcodeString = "95 sub l";
			bytesRead = 1;
			break;
		}
		case 6:
		{
			opcodeString = "96 sub (hl)";
			bytesRead = 1;
			break;
		}
		case 7:
		{
			opcodeString = "97 sub a";
			bytesRead = 1;
			break;
		}
		case 8:
		{
			opcodeString = "98 sbc b";
			bytesRead = 1;
			break;
		}
		case 9:
		{
			opcodeString = "99 sbc c";
			bytesRead = 1;
			break;
		}
		case 0xA:
		{
			opcodeString = "9A sbc d";
			bytesRead = 1;
			break;
		}
		case 0xB:
		{
			opcodeString = "9B sbc e";
			bytesRead = 1;
			break;
		}
		case 0xC:
		{
			opcodeString = "9C sbc h";
			bytesRead = 1;
			break;
		}
		case 0xD:
		{
			opcodeString = "9D sbc l";
			bytesRead = 1;
			break;
		}
		case 0xE:
		{
			opcodeString = "9E sbc (hl)";
			bytesRead = 1;
			break;
		}
		case 0xF:
		{
			opcodeString = "9F sbc a";
			bytesRead = 1;
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
			opcodeString = "A0 and b";
			bytesRead = 1;
			break;
		}
		case 1:
		{
			opcodeString = "A1 and c";
			bytesRead = 1;
			break;
		}
		case 2:
		{
			opcodeString = "A2 and d";
			bytesRead = 1;
			break;
		}
		case 3:
		{
			opcodeString = "A3 and e";
			bytesRead = 1;
			break;
		}
		case 4:
		{
			opcodeString = "A4 and h";
			bytesRead = 1;
			break;
		}
		case 5:
		{
			opcodeString = "A5 and l";
			bytesRead = 1;
			break;
		}
		case 6:
		{
			opcodeString = "A6 and (hl)";
			bytesRead = 1;
			break;
		}
		case 7:
		{
			opcodeString = "A7 and a";
			bytesRead = 1;
			break;
		}
		case 8:
		{
			opcodeString = "A8 xor b";
			bytesRead = 1;
			break;
		}
		case 9:
		{
			opcodeString = "A9 xor c";
			bytesRead = 1;
			break;
		}
		case 0xA:
		{
			opcodeString = "AA xor d";
			bytesRead = 1;
			break;
		}
		case 0xB:
		{
			opcodeString = "AB xor e";
			bytesRead = 1;
			break;
		}
		case 0xC:
		{
			opcodeString = "AC xor h";
			bytesRead = 1;
			break;
		}
		case 0xD:
		{
			opcodeString = "AD xor l";
			bytesRead = 1;
			break;
		}
		case 0xE:
		{
			opcodeString = "AE xor (hl)";
			bytesRead = 1;
			break;
		}
		case 0xF:
		{
			opcodeString = "AF xor a";
			bytesRead = 1;
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
			opcodeString = "B0 or b";
			bytesRead = 1;
			break;
		}
		case 1:
		{
			opcodeString = "B1 or c";
			bytesRead = 1;
			break;
		}
		case 2:
		{
			opcodeString = "B2 or d";
			bytesRead = 1;
			break;
		}
		case 3:
		{
			opcodeString = "B3 or e";
			bytesRead = 1;
			break;
		}
		case 4:
		{
			opcodeString = "B4 or h";
			bytesRead = 1;
			break;
		}
		case 5:
		{
			opcodeString = "B5 or l";
			bytesRead = 1;
			break;
		}
		case 6:
		{
			opcodeString = "B6 or (hl)";
			bytesRead = 1;
			break;
		}
		case 7:
		{
			opcodeString = "B7 or a";
			bytesRead = 1;
			break;
		}
		case 8:
		{
			opcodeString = "B8 cp b";
			bytesRead = 1;
			break;
		}
		case 9:
		{
			opcodeString = "B9 cp c";
			bytesRead = 1;
			break;
		}
		case 0xA:
		{
			opcodeString = "BA cp d";
			bytesRead = 1;
			break;
		}
		case 0xB:
		{
			opcodeString = "BB cp e";
			bytesRead = 1;
			break;
		}
		case 0xC:
		{
			opcodeString = "BC cp h";
			bytesRead = 1;
			break;
		}
		case 0xD:
		{
			opcodeString = "BD cp l";
			bytesRead = 1;
			break;
		}
		case 0xE:
		{
			opcodeString = "BE cp (hl)";
			bytesRead = 1;
			break;
		}
		case 0xF:
		{
			opcodeString = "BF cp a";
			bytesRead = 1;
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
			opcodeString = "C0 ret nz";
			bytesRead = 1;
			break;
		}
		case 0x01:
		{
			opcodeString = "C1 pop bc";
			bytesRead = 1;
			break;
		}
		case 0x02:
		{
			short argument = ((beakMemory.readMemory(address + 1)) | (beakMemory.readMemory(address + 2) << 8));
			ss << hex << argument;
			string hexArgument = ss.str();
			opcodeString = "C2 " + hexArgument + " jp nz, " + hexArgument;
			bytesRead = 3;
			ss.str("");
			break;
		}
		case 0x03:
		{
			short argument = ((beakMemory.readMemory(address + 1)) | (beakMemory.readMemory(address + 2) << 8));
			ss << hex << argument;
			string hexArgument = ss.str();
			opcodeString = "C3 " + hexArgument + " jp " + hexArgument;
			bytesRead = 3;
			ss.str("");
			break;
		}
		case 0x04:
		{
			short argument = ((beakMemory.readMemory(address + 1)) | (beakMemory.readMemory(address + 2) << 8));
			ss << hex << argument;
			string hexArgument = ss.str();
			opcodeString = "C4 " + hexArgument + " call nz, " + hexArgument;
			bytesRead = 3;
			ss.str("");
			break;
		}
		case 0x05:
		{
			opcodeString = "C5 push bc";
			bytesRead = 1;
			break;
		}
		case 0x06:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "C6 " + ss.str() + " add a, " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 0x07:
		{
			opcodeString = "C7 rst 00";
			bytesRead = 1;
			break;
		}
		case 0x08:
		{
			opcodeString = "C8 ret z";
			bytesRead = 1;
			break;
		}
		case 0x09:
		{
			opcodeString = "C9 ret";
			bytesRead = 1;
			break;
		}
		case 0x0A:
		{
			short argument = ((beakMemory.readMemory(address + 1)) | (beakMemory.readMemory(address + 2) << 8));
			ss << hex << argument;
			string hexArgument = ss.str();
			ss.str("");
			opcodeString = "C4 " + hexArgument + " jp z, " + hexArgument;
			bytesRead = 3;
			break;
		}
		case 0x0B:
		{
			switch (beakMemory.readMemory(address + 1))
			{

			case 0x00: { opcodeString = "CB 00 rlc b"; bytesRead = 2; break; }
			case 0x01: { opcodeString = "CB 01 rlc c"; bytesRead = 2; break; }
			case 0x02: { opcodeString = "CB 02 rlc d"; bytesRead = 2; break; }
			case 0x03: { opcodeString = "CB 03 rlc e"; bytesRead = 2; break; }
			case 0x04: { opcodeString = "CB 04 rlc h"; bytesRead = 2; break; }
			case 0x05: { opcodeString = "CB 05 rlc l"; bytesRead = 2; break; }
			case 0x06: { opcodeString = "CB 06 rlc (hl)"; bytesRead = 2; break; }
			case 0x07: { opcodeString = "CB 07 rlc a"; bytesRead = 2; break; }
			case 0x08: { opcodeString = "CB 08 rrc b"; bytesRead = 2; break; }
			case 0x09: { opcodeString = "CB 09 rrc c"; bytesRead = 2; break; }
			case 0x0A: { opcodeString = "CB 0A rrc d"; bytesRead = 2; break; }
			case 0x0B: { opcodeString = "CB 0B rrc e"; bytesRead = 2; break; }
			case 0x0C: { opcodeString = "CB 0C rrc h"; bytesRead = 2; break; }
			case 0x0D: { opcodeString = "CB 0D rrc l"; bytesRead = 2; break; }
			case 0x0E: { opcodeString = "CB 0E rrc (hl)"; bytesRead = 2; break; }
			case 0x0F: { opcodeString = "CB 0F rrc a"; bytesRead = 2; break; }
			case 0x10: { opcodeString = "CB 10 rl b"; bytesRead = 2; break; }
			case 0x11: { opcodeString = "CB 11 rl c"; bytesRead = 2; break; }
			case 0x12: { opcodeString = "CB 12 rl d"; bytesRead = 2; break; }
			case 0x13: { opcodeString = "CB 13 rl e"; bytesRead = 2; break; }
			case 0x14: { opcodeString = "CB 14 rl h"; bytesRead = 2; break; }
			case 0x15: { opcodeString = "CB 15 rl l"; bytesRead = 2; break; }
			case 0x16: { opcodeString = "CB 16 rl (hl)"; bytesRead = 2; break; }
			case 0x17: { opcodeString = "CB 17 rl a"; bytesRead = 2; break; }
			case 0x18: { opcodeString = "CB 18 rr b"; bytesRead = 2; break; }
			case 0x19: { opcodeString = "CB 19 rr c"; bytesRead = 2; break; }
			case 0x1A: { opcodeString = "CB 1A rr d"; bytesRead = 2; break; }
			case 0x1B: { opcodeString = "CB 1B rr e"; bytesRead = 2; break; }
			case 0x1C: { opcodeString = "CB 1C rr h"; bytesRead = 2; break; }
			case 0x1D: { opcodeString = "CB 1D rr l"; bytesRead = 2; break; }
			case 0x1E: { opcodeString = "CB 1E rr (hl)"; bytesRead = 2; break; }
			case 0x1F: { opcodeString = "CB 1F rr a"; bytesRead = 2; break; }
			case 0x20: { opcodeString = "CB 20 sla b"; bytesRead = 2; break; }
			case 0x21: { opcodeString = "CB 21 sla c"; bytesRead = 2; break; }
			case 0x22: { opcodeString = "CB 22 sla d"; bytesRead = 2; break; }
			case 0x23: { opcodeString = "CB 23 sla e"; bytesRead = 2; break; }
			case 0x24: { opcodeString = "CB 24 sla h"; bytesRead = 2; break; }
			case 0x25: { opcodeString = "CB 25 sla l"; bytesRead = 2; break; }
			case 0x26: { opcodeString = "CB 26 sla (hl)"; bytesRead = 2; break; }
			case 0x27: { opcodeString = "CB 27 sla a"; bytesRead = 2; break; }
			case 0x28: { opcodeString = "CB 28 sra b"; bytesRead = 2; break; }
			case 0x29: { opcodeString = "CB 29 sra c"; bytesRead = 2; break; }
			case 0x2A: { opcodeString = "CB 2A sra d"; bytesRead = 2; break; }
			case 0x2B: { opcodeString = "CB 2B sra e"; bytesRead = 2; break; }
			case 0x2C: { opcodeString = "CB 2C sra h"; bytesRead = 2; break; }
			case 0x2D: { opcodeString = "CB 2D sra l"; bytesRead = 2; break; }
			case 0x2E: { opcodeString = "CB 2E sra (hl)"; bytesRead = 2; break; }
			case 0x2F: { opcodeString = "CB 2F sra a"; bytesRead = 2; break; }
			case 0x30: { opcodeString = "CB 30 swap b"; bytesRead = 2; break; }
			case 0x31: { opcodeString = "CB 31 swap c"; bytesRead = 2; break; }
			case 0x32: { opcodeString = "CB 32 swap d"; bytesRead = 2; break; }
			case 0x33: { opcodeString = "CB 33 swap e"; bytesRead = 2; break; }
			case 0x34: { opcodeString = "CB 34 swap h"; bytesRead = 2; break; }
			case 0x35: { opcodeString = "CB 35 swap l"; bytesRead = 2; break; }
			case 0x36: { opcodeString = "CB 36 swap (hl)"; bytesRead = 2; break; }
			case 0x37: { opcodeString = "CB 37 swap a"; bytesRead = 2; break; }
			case 0x38: { opcodeString = "CB 38 srl b"; bytesRead = 2; break; }
			case 0x39: { opcodeString = "CB 39 srl c"; bytesRead = 2; break; }
			case 0x3A: { opcodeString = "CB 3A srl d"; bytesRead = 2; break; }
			case 0x3B: { opcodeString = "CB 3B srl e"; bytesRead = 2; break; }
			case 0x3C: { opcodeString = "CB 3C srl h"; bytesRead = 2; break; }
			case 0x3D: { opcodeString = "CB 3D srl l"; bytesRead = 2; break; }
			case 0x3E: { opcodeString = "CB 3E srl (hl)"; bytesRead = 2; break; }
			case 0x3F: { opcodeString = "CB 3F srl a"; bytesRead = 2; break; }
			case 0x40: { opcodeString = "CB 40 bit 0, b"; bytesRead = 2; break; }
			case 0x41: { opcodeString = "CB 41 bit 0, c"; bytesRead = 2; break; }
			case 0x42: { opcodeString = "CB 42 bit 0, d"; bytesRead = 2; break; }
			case 0x43: { opcodeString = "CB 43 bit 0, e"; bytesRead = 2; break; }
			case 0x44: { opcodeString = "CB 44 bit 0, h"; bytesRead = 2; break; }
			case 0x45: { opcodeString = "CB 45 bit 0, l"; bytesRead = 2; break; }
			case 0x46: { opcodeString = "CB 46 bit 0, (hl)"; bytesRead = 2; break; }
			case 0x47: { opcodeString = "CB 47 bit 0, a"; bytesRead = 2; break; }
			case 0x48: { opcodeString = "CB 48 bit 1, b"; bytesRead = 2; break; }
			case 0x49: { opcodeString = "CB 49 bit 1, c"; bytesRead = 2; break; }
			case 0x4A: { opcodeString = "CB 4A bit 1, d"; bytesRead = 2; break; }
			case 0x4B: { opcodeString = "CB 4B bit 1, e"; bytesRead = 2; break; }
			case 0x4C: { opcodeString = "CB 4C bit 1, h"; bytesRead = 2; break; }
			case 0x4D: { opcodeString = "CB 4D bit 1, l"; bytesRead = 2; break; }
			case 0x4E: { opcodeString = "CB 4E bit 1, (hl)"; bytesRead = 2; break; }
			case 0x4F: { opcodeString = "CB 4F bit 1, a"; bytesRead = 2; break; }
			case 0x50: { opcodeString = "CB 50 bit 2, b"; bytesRead = 2; break; }
			case 0x51: { opcodeString = "CB 51 bit 2, c"; bytesRead = 2; break; }
			case 0x52: { opcodeString = "CB 52 bit 2, d"; bytesRead = 2; break; }
			case 0x53: { opcodeString = "CB 53 bit 2, e"; bytesRead = 2; break; }
			case 0x54: { opcodeString = "CB 54 bit 2, h"; bytesRead = 2; break; }
			case 0x55: { opcodeString = "CB 55 bit 2, l"; bytesRead = 2; break; }
			case 0x56: { opcodeString = "CB 56 bit 2, (hl)"; bytesRead = 2; break; }
			case 0x57: { opcodeString = "CB 57 bit 2, a"; bytesRead = 2; break; }
			case 0x58: { opcodeString = "CB 58 bit 3, b"; bytesRead = 2; break; }
			case 0x59: { opcodeString = "CB 59 bit 3, c"; bytesRead = 2; break; }
			case 0x5A: { opcodeString = "CB 5A bit 3, d"; bytesRead = 2; break; }
			case 0x5B: { opcodeString = "CB 5B bit 3, e"; bytesRead = 2; break; }
			case 0x5C: { opcodeString = "CB 5C bit 3, h"; bytesRead = 2; break; }
			case 0x5D: { opcodeString = "CB 5D bit 3, l"; bytesRead = 2; break; }
			case 0x5E: { opcodeString = "CB 5E bit 3, (hl)"; bytesRead = 2; break; }
			case 0x5F: { opcodeString = "CB 5F bit 3, a"; bytesRead = 2; break; }
			case 0x60: { opcodeString = "CB 60 bit 4, b"; bytesRead = 2; break; }
			case 0x61: { opcodeString = "CB 61 bit 4, c"; bytesRead = 2; break; }
			case 0x62: { opcodeString = "CB 62 bit 4, d"; bytesRead = 2; break; }
			case 0x63: { opcodeString = "CB 63 bit 4, e"; bytesRead = 2; break; }
			case 0x64: { opcodeString = "CB 64 bit 4, h"; bytesRead = 2; break; }
			case 0x65: { opcodeString = "CB 65 bit 4, l"; bytesRead = 2; break; }
			case 0x66: { opcodeString = "CB 66 bit 4, (hl)"; bytesRead = 2; break; }
			case 0x67: { opcodeString = "CB 67 bit 4, a"; bytesRead = 2; break; }
			case 0x68: { opcodeString = "CB 68 bit 5, b"; bytesRead = 2; break; }
			case 0x69: { opcodeString = "CB 69 bit 5, c"; bytesRead = 2; break; }
			case 0x6A: { opcodeString = "CB 6A bit 5, d"; bytesRead = 2; break; }
			case 0x6B: { opcodeString = "CB 6B bit 5, e"; bytesRead = 2; break; }
			case 0x6C: { opcodeString = "CB 6C bit 5, h"; bytesRead = 2; break; }
			case 0x6D: { opcodeString = "CB 6D bit 5, l"; bytesRead = 2; break; }
			case 0x6E: { opcodeString = "CB 6E bit 5, (hl)"; bytesRead = 2; break; }
			case 0x6F: { opcodeString = "CB 6F bit 5, a"; bytesRead = 2; break; }
			case 0x70: { opcodeString = "CB 70 bit 6, b"; bytesRead = 2; break; }
			case 0x71: { opcodeString = "CB 71 bit 6, c"; bytesRead = 2; break; }
			case 0x72: { opcodeString = "CB 72 bit 6, d"; bytesRead = 2; break; }
			case 0x73: { opcodeString = "CB 73 bit 6, e"; bytesRead = 2; break; }
			case 0x74: { opcodeString = "CB 74 bit 6, h"; bytesRead = 2; break; }
			case 0x75: { opcodeString = "CB 75 bit 6, l"; bytesRead = 2; break; }
			case 0x76: { opcodeString = "CB 76 bit 6, (hl)"; bytesRead = 2; break; }
			case 0x77: { opcodeString = "CB 77 bit 6, a"; bytesRead = 2; break; }
			case 0x78: { opcodeString = "CB 78 bit 7, b"; bytesRead = 2; break; }
			case 0x79: { opcodeString = "CB 79 bit 7, c"; bytesRead = 2; break; }
			case 0x7A: { opcodeString = "CB 7A bit 7, d"; bytesRead = 2; break; }
			case 0x7B: { opcodeString = "CB 7B bit 7, e"; bytesRead = 2; break; }
			case 0x7C: { opcodeString = "CB 7C bit 7, h"; bytesRead = 2; break; }
			case 0x7D: { opcodeString = "CB 7D bit 7, l"; bytesRead = 2; break; }
			case 0x7E: { opcodeString = "CB 7E bit 7, (hl)"; bytesRead = 2; break; }
			case 0x7F: { opcodeString = "CB 7F bit 7, a"; bytesRead = 2; break; }
			case 0x80: { opcodeString = "CB 80 res 0, b"; bytesRead = 2; break; }
			case 0x81: { opcodeString = "CB 81 res 0, c"; bytesRead = 2; break; }
			case 0x82: { opcodeString = "CB 82 res 0, d"; bytesRead = 2; break; }
			case 0x83: { opcodeString = "CB 83 res 0, e"; bytesRead = 2; break; }
			case 0x84: { opcodeString = "CB 84 res 0, h"; bytesRead = 2; break; }
			case 0x85: { opcodeString = "CB 85 res 0, l"; bytesRead = 2; break; }
			case 0x86: { opcodeString = "CB 86 res 0, (hl)"; bytesRead = 2; break; }
			case 0x87: { opcodeString = "CB 87 res 0, a"; bytesRead = 2; break; }
			case 0x88: { opcodeString = "CB 88 res 1, b"; bytesRead = 2; break; }
			case 0x89: { opcodeString = "CB 89 res 1, c"; bytesRead = 2; break; }
			case 0x8A: { opcodeString = "CB 8A res 1, d"; bytesRead = 2; break; }
			case 0x8B: { opcodeString = "CB 8B res 1, e"; bytesRead = 2; break; }
			case 0x8C: { opcodeString = "CB 8C res 1, h"; bytesRead = 2; break; }
			case 0x8D: { opcodeString = "CB 8D res 1, l"; bytesRead = 2; break; }
			case 0x8E: { opcodeString = "CB 8E res 1, (hl)"; bytesRead = 2; break; }
			case 0x8F: { opcodeString = "CB 8F res 1, a"; bytesRead = 2; break; }
			case 0x90: { opcodeString = "CB 90 res 2, b"; bytesRead = 2; break; }
			case 0x91: { opcodeString = "CB 91 res 2, c"; bytesRead = 2; break; }
			case 0x92: { opcodeString = "CB 92 res 2, d"; bytesRead = 2; break; }
			case 0x93: { opcodeString = "CB 93 res 2, e"; bytesRead = 2; break; }
			case 0x94: { opcodeString = "CB 94 res 2, h"; bytesRead = 2; break; }
			case 0x95: { opcodeString = "CB 95 res 2, l"; bytesRead = 2; break; }
			case 0x96: { opcodeString = "CB 96 res 2, (hl)"; bytesRead = 2; break; }
			case 0x97: { opcodeString = "CB 97 res 2, a"; bytesRead = 2; break; }
			case 0x98: { opcodeString = "CB 98 res 3, b"; bytesRead = 2; break; }
			case 0x99: { opcodeString = "CB 99 res 3, c"; bytesRead = 2; break; }
			case 0x9A: { opcodeString = "CB 9A res 3, d"; bytesRead = 2; break; }
			case 0x9B: { opcodeString = "CB 9B res 3, e"; bytesRead = 2; break; }
			case 0x9C: { opcodeString = "CB 9C res 3, h"; bytesRead = 2; break; }
			case 0x9D: { opcodeString = "CB 9D res 3, l"; bytesRead = 2; break; }
			case 0x9E: { opcodeString = "CB 9E res 3, (hl)"; bytesRead = 2; break; }
			case 0x9F: { opcodeString = "CB 9F res 3, a"; bytesRead = 2; break; }
			case 0xA0: { opcodeString = "CB A0 res 4, b"; bytesRead = 2; break; }
			case 0xA1: { opcodeString = "CB A1 res 4, c"; bytesRead = 2; break; }
			case 0xA2: { opcodeString = "CB A2 res 4, d"; bytesRead = 2; break; }
			case 0xA3: { opcodeString = "CB A3 res 4, e"; bytesRead = 2; break; }
			case 0xA4: { opcodeString = "CB A4 res 4, h"; bytesRead = 2; break; }
			case 0xA5: { opcodeString = "CB A5 res 4, l"; bytesRead = 2; break; }
			case 0xA6: { opcodeString = "CB A6 res 4, (hl)"; bytesRead = 2; break; }
			case 0xA7: { opcodeString = "CB A7 res 4, a"; bytesRead = 2; break; }
			case 0xA8: { opcodeString = "CB A8 res 5, b"; bytesRead = 2; break; }
			case 0xA9: { opcodeString = "CB A9 res 5, c"; bytesRead = 2; break; }
			case 0xAA: { opcodeString = "CB AA res 5, d"; bytesRead = 2; break; }
			case 0xAB: { opcodeString = "CB AB res 5, e"; bytesRead = 2; break; }
			case 0xAC: { opcodeString = "CB AC res 5, h"; bytesRead = 2; break; }
			case 0xAD: { opcodeString = "CB AD res 5, l"; bytesRead = 2; break; }
			case 0xAE: { opcodeString = "CB AE res 5, (hl)"; bytesRead = 2; break; }
			case 0xAF: { opcodeString = "CB AF res 5, a"; bytesRead = 2; break; }
			case 0xB0: { opcodeString = "CB B0 res 6, b"; bytesRead = 2; break; }
			case 0xB1: { opcodeString = "CB B1 res 6, c"; bytesRead = 2; break; }
			case 0xB2: { opcodeString = "CB B2 res 6, d"; bytesRead = 2; break; }
			case 0xB3: { opcodeString = "CB B3 res 6, e"; bytesRead = 2; break; }
			case 0xB4: { opcodeString = "CB B4 res 6, h"; bytesRead = 2; break; }
			case 0xB5: { opcodeString = "CB B5 res 6, l"; bytesRead = 2; break; }
			case 0xB6: { opcodeString = "CB B6 res 6, (hl)"; bytesRead = 2; break; }
			case 0xB7: { opcodeString = "CB B7 res 6, a"; bytesRead = 2; break; }
			case 0xB8: { opcodeString = "CB B8 res 7, b"; bytesRead = 2; break; }
			case 0xB9: { opcodeString = "CB B9 res 7, c"; bytesRead = 2; break; }
			case 0xBA: { opcodeString = "CB BA res 7, d"; bytesRead = 2; break; }
			case 0xBB: { opcodeString = "CB BB res 7, e"; bytesRead = 2; break; }
			case 0xBC: { opcodeString = "CB BC res 7, h"; bytesRead = 2; break; }
			case 0xBD: { opcodeString = "CB BD res 7, l"; bytesRead = 2; break; }
			case 0xBE: { opcodeString = "CB BE res 7, (hl)"; bytesRead = 2; break; }
			case 0xBF: { opcodeString = "CB BF res 7, a"; bytesRead = 2; break; }
			case 0xC0: { opcodeString = "CB C0 set 0, b"; bytesRead = 2; break; }
			case 0xC1: { opcodeString = "CB C1 set 0, c"; bytesRead = 2; break; }
			case 0xC2: { opcodeString = "CB C2 set 0, d"; bytesRead = 2; break; }
			case 0xC3: { opcodeString = "CB C3 set 0, e"; bytesRead = 2; break; }
			case 0xC4: { opcodeString = "CB C4 set 0, h"; bytesRead = 2; break; }
			case 0xC5: { opcodeString = "CB C5 set 0, l"; bytesRead = 2; break; }
			case 0xC6: { opcodeString = "CB C6 set 0, (hl)"; bytesRead = 2; break; }
			case 0xC7: { opcodeString = "CB C7 set 0, a"; bytesRead = 2; break; }
			case 0xC8: { opcodeString = "CB C8 set 1, b"; bytesRead = 2; break; }
			case 0xC9: { opcodeString = "CB C9 set 1, c"; bytesRead = 2; break; }
			case 0xCA: { opcodeString = "CB CA set 1, d"; bytesRead = 2; break; }
			case 0xCB: { opcodeString = "CB CB set 1, e"; bytesRead = 2; break; }
			case 0xCC: { opcodeString = "CB CC set 1, h"; bytesRead = 2; break; }
			case 0xCD: { opcodeString = "CB CD set 1, l"; bytesRead = 2; break; }
			case 0xCE: { opcodeString = "CB CE set 1, (hl)"; bytesRead = 2; break; }
			case 0xCF: { opcodeString = "CB CF set 1, a"; bytesRead = 2; break; }
			case 0xD0: { opcodeString = "CB D0 set 2, b"; bytesRead = 2; break; }
			case 0xD1: { opcodeString = "CB D1 set 2, c"; bytesRead = 2; break; }
			case 0xD2: { opcodeString = "CB D2 set 2, d"; bytesRead = 2; break; }
			case 0xD3: { opcodeString = "CB D3 set 2, e"; bytesRead = 2; break; }
			case 0xD4: { opcodeString = "CB D4 set 2, h"; bytesRead = 2; break; }
			case 0xD5: { opcodeString = "CB D5 set 2, l"; bytesRead = 2; break; }
			case 0xD6: { opcodeString = "CB D6 set 2, (hl)"; bytesRead = 2; break; }
			case 0xD7: { opcodeString = "CB D7 set 2, a"; bytesRead = 2; break; }
			case 0xD8: { opcodeString = "CB D8 set 3, b"; bytesRead = 2; break; }
			case 0xD9: { opcodeString = "CB D9 set 3, c"; bytesRead = 2; break; }
			case 0xDA: { opcodeString = "CB DA set 3, d"; bytesRead = 2; break; }
			case 0xDB: { opcodeString = "CB DB set 3, e"; bytesRead = 2; break; }
			case 0xDC: { opcodeString = "CB DC set 3, h"; bytesRead = 2; break; }
			case 0xDD: { opcodeString = "CB DD set 3, l"; bytesRead = 2; break; }
			case 0xDE: { opcodeString = "CB DE set 3, (hl)"; bytesRead = 2; break; }
			case 0xDF: { opcodeString = "CB DF set 3, a"; bytesRead = 2; break; }
			case 0xE0: { opcodeString = "CB E0 set 4, b"; bytesRead = 2; break; }
			case 0xE1: { opcodeString = "CB E1 set 4, c"; bytesRead = 2; break; }
			case 0xE2: { opcodeString = "CB E2 set 4, d"; bytesRead = 2; break; }
			case 0xE3: { opcodeString = "CB E3 set 4, e"; bytesRead = 2; break; }
			case 0xE4: { opcodeString = "CB E4 set 4, h"; bytesRead = 2; break; }
			case 0xE5: { opcodeString = "CB E5 set 4, l"; bytesRead = 2; break; }
			case 0xE6: { opcodeString = "CB E6 set 4, (hl)"; bytesRead = 2; break; }
			case 0xE7: { opcodeString = "CB E7 set 4, a"; bytesRead = 2; break; }
			case 0xE8: { opcodeString = "CB E8 set 5, b"; bytesRead = 2; break; }
			case 0xE9: { opcodeString = "CB E9 set 5, c"; bytesRead = 2; break; }
			case 0xEA: { opcodeString = "CB EA set 5, d"; bytesRead = 2; break; }
			case 0xEB: { opcodeString = "CB EB set 5, e"; bytesRead = 2; break; }
			case 0xEC: { opcodeString = "CC EC set 5, h"; bytesRead = 2; break; }
			case 0xED: { opcodeString = "CB ED set 5, l"; bytesRead = 2; break; }
			case 0xEE: { opcodeString = "CB EE set 5, (hl)"; bytesRead = 2; break; }
			case 0xEF: { opcodeString = "CB EF set 5, a"; bytesRead = 2; break; }
			case 0xF0: { opcodeString = "CB F0 set 6, b"; bytesRead = 2; break; }
			case 0xF1: { opcodeString = "CB F1 set 6, c"; bytesRead = 2; break; }
			case 0xF2: { opcodeString = "CB F2 set 6, d"; bytesRead = 2; break; }
			case 0xF3: { opcodeString = "CB F3 set 6, e"; bytesRead = 2; break; }
			case 0xF4: { opcodeString = "CB F4 set 6, h"; bytesRead = 2; break; }
			case 0xF5: { opcodeString = "CB F5 set 6, l"; bytesRead = 2; break; }
			case 0xF6: { opcodeString = "CB F6 set 6, (hl)"; bytesRead = 2; break; }
			case 0xF7: { opcodeString = "CB F7 set 6, a"; bytesRead = 2; break; }
			case 0xF8: { opcodeString = "CB F8 set 7, b"; bytesRead = 2; break; }
			case 0xF9: { opcodeString = "CB F9 set 7, c"; bytesRead = 2; break; }
			case 0xFA: { opcodeString = "CB FA set 7, d"; bytesRead = 2; break; }
			case 0xFB: { opcodeString = "CB FB set 7, e"; bytesRead = 2; break; }
			case 0xFC: { opcodeString = "CB FC set 7, h"; bytesRead = 2; break; }
			case 0xFD: { opcodeString = "CB FD set 7, l"; bytesRead = 2; break; }
			case 0xFE: { opcodeString = "CB FE set 7, (hl)"; bytesRead = 2; break; }
			case 0xFF: { opcodeString = "CB FF set 7, a"; bytesRead = 2; break; }

			}
			break;
		}
		case 0x0C:
		{
			short argument = ((beakMemory.readMemory(address + 1)) | (beakMemory.readMemory(address + 2) << 8));
			ss << hex << argument;
			string hexArgument = ss.str();
			opcodeString = "CC " + hexArgument + " call z, " + hexArgument;
			bytesRead = 3;
			ss.str("");
			break;
		}
		case 0x0D:
		{
			short argument = ((beakMemory.readMemory(address + 1)) | (beakMemory.readMemory(address + 2) << 8));
			ss << hex << argument;
			string hexArgument = ss.str();
			opcodeString = "CD " + hexArgument + " call " + hexArgument;
			bytesRead = 3;
			ss.str("");
			break;
		}
		case 0x0E:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "CE " + ss.str() + " adc a, " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 0x0F:
		{
			opcodeString = "CF res 08";
			bytesRead = 1;
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
			opcodeString = "D0 ret nc";
			bytesRead = 1;
			break;
		}
		case 1:
		{
			opcodeString = "D1 pop de";
			bytesRead = 1;
			break;
		}
		case 2:
		{
			short argument = ((beakMemory.readMemory(address + 1)) | (beakMemory.readMemory(address + 2) << 8));
			ss << hex << argument;
			string hexArgument = ss.str();
			opcodeString = "D2 " + hexArgument + " jp nc, " + hexArgument;
			bytesRead = 3;
			ss.str("");
			break;
		}
		case 3:
		{
			//D3 not implemented
			opcodeString = "D3 UNDEFINED";
			bytesRead = 1;
			break;
		}
		case 4:
		{
			short argument = ((beakMemory.readMemory(address + 1)) | (beakMemory.readMemory(address + 2) << 8));
			ss << hex << argument;
			string hexArgument = ss.str();
			opcodeString = "D4 " + hexArgument + " call nc, " + hexArgument;
			bytesRead = 3;
			ss.str("");
			break;
		}
		case 5:
		{
			opcodeString = "D5 push de";
			bytesRead = 1;
			break;
		}
		case 6:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "D6 " + ss.str() + " sub a, " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 7:
		{
			opcodeString = "D7 rst 10";
			bytesRead = 1;
			break;
		}
		case 8:
		{
			opcodeString = "D8 ret c";
			bytesRead = 1;
			break;
		}
		case 9:
		{
			opcodeString = "D9 reti";
			bytesRead = 1;
			break;
		}
		case 0xA:
		{
			short argument = ((beakMemory.readMemory(address + 1)) | (beakMemory.readMemory(address + 2) << 8));
			ss << hex << argument;
			string hexArgument = ss.str();
			opcodeString = "DA " + hexArgument + " jp c, " + hexArgument;
			bytesRead = 3;
			ss.str("");
			break;
		}
		case 0xB:
		{
			//DB not implemented
			opcodeString = "DB UNDEFINED";
			bytesRead = 1;
			break;
		}
		case 0xC:
		{
			short argument = ((beakMemory.readMemory(address + 1)) | (beakMemory.readMemory(address + 2) << 8));
			ss << hex << argument;
			string hexArgument = ss.str();
			opcodeString = "DC " + hexArgument + " call c, " + hexArgument;
			bytesRead = 3;
			ss.str("");
			break;
		}
		case 0xD:
		{
			//DD not implemented
			opcodeString = "DD UNDEFINED";
			bytesRead = 1;
			break;
		}
		case 0xE:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "DE " + ss.str() + " sbc a, " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 0xF:
		{
			opcodeString = "DF rst 18";
			bytesRead = 1;
			break;
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
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "E0 " + ss.str() + " ld (ff00 + " + ss.str() + "), a";
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 1:
		{
			opcodeString = "E1 pop hl";
			bytesRead = 1;
			break;
		}
		case 2:
		{
			opcodeString = "E2 ld (ff00 + c), a";
			bytesRead = 1;
			break;
		}
		case 3:
		{
			//E3 not implemented
			opcodeString = "E3 UNDEFINED";
			bytesRead = 1;
			break;
		}
		case 4:
		{
			//E4 not implemented
			opcodeString = "E4 UNDEFINED";
			bytesRead = 1;
			break;
		}
		case 5:
		{
			opcodeString = "E5 push hl";
			bytesRead = 1;
			break;
		}
		case 6:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "E6 " + ss.str() + " and a, " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 7:
		{
			opcodeString = "E7 rst 20";
			bytesRead = 1;
			break;
		}
		case 8:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "E8 " + ss.str() + " add sp, " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 9:
		{
			opcodeString = "E9 jp hl";
			bytesRead = 1;
			break;
		}
		case 0xA:
		{
			short argument = ((beakMemory.readMemory(address + 1)) | (beakMemory.readMemory(address + 2) << 8));
			ss << hex << argument;
			opcodeString = "EA " + ss.str() + " ld (" + ss.str() + "), a";
			bytesRead = 3;
			ss.str("");
			break;
		}
		case 0xB:
		{
			//EB not implemented
			opcodeString = "EB UNDEFINED";
			bytesRead = 1;
			break;
		}
		case 0xC:
		{
			//EC not implemented
			opcodeString = "EC UNDEFINED";
			bytesRead = 1;
			break;
		}
		case 0xD:
		{
			//ED not implemented
			opcodeString = "ED UNDEFINED";
			bytesRead = 1;
			break;
		}
		case 0xE:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "EE " + ss.str() + " xor a, " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 0xF:
		{
			opcodeString = "EF rst 28";
			bytesRead = 1;
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
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "F0 " + ss.str() + " ld a, (ff00 + " + ss.str() + ")";
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 1:
		{
			opcodeString = "F1 pop af";
			bytesRead = 1;
			break;
		}
		case 2:
		{
			opcodeString = "F2 ld a, (ff00 + c)";
			bytesRead = 1;
			break;
		}
		case 3:
		{
			opcodeString = "F3 di";
			bytesRead = 1;
			break;
		}
		case 4:
		{
			//F4 not implemented
			opcodeString = "F4 UNDEFINED";
			bytesRead = 1;
			break;
		}
		case 5:
		{
			opcodeString = "F5 push af";
			bytesRead = 1;
			break;
		}
		case 6:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "F6 " + ss.str() + " or a, " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 7:
		{
			opcodeString = "F7 rst 30";
			bytesRead = 1;
			break;
		}
		case 8:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "F8 " + ss.str() + " hl, sp + " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 9:
		{
			opcodeString = "F9 sp, hl";
			bytesRead = 1;
			break;
		}
		case 0xA:
		{
			short argument1 = beakMemory.readMemory(address + 2);
			short argument2 = beakMemory.readMemory(address + 1);
			ss << hex << argument1;
			string byte1 = ss.str();
			ss.str("");
			ss << hex << argument2;
			string byte2 = ss.str();
			opcodeString = "FA " + byte1 + " " + byte2 + " ld a, (" + byte2 + byte1 + ")";
			bytesRead = 3;
			ss.str("");
			break;
		}
		case 0xB:
		{
			//Enable Interrupts
			opcodeString = "FB ei";
			bytesRead = 1;
			break;
		}
		case 0xC:
		{
			//FC not implemented
			opcodeString = "FC UNDEFINED";
			bytesRead = 1;
			break;
		}
		case 0xD:
		{
			//FD not implemented
			opcodeString = "FD UNDEFINED";
			bytesRead = 1;
			break;
		}
		case 0xE:
		{
			short argument = beakMemory.readMemory(address + 1);
			ss << hex << argument;
			opcodeString = "FE " + ss.str() + " cp a, " + ss.str();
			bytesRead = 2;
			ss.str("");
			break;
		}
		case 0xF:
		{
			opcodeString = "FF rst 38";
			bytesRead = 1;
			break;
		}
		}
		break;
	}


	}

	ss << hex << address;
	opcodeString = ss.str() + ":\t" + opcodeString;

	return tuple<string, int>(opcodeString, bytesRead);
}

bool checkForWriteBreakpoint(bool &writeBreakpoint, bool &writeBreakpointValue, byte &breakpointValue, short &writeBreakpointAddress)
{

	if (writeBreakpoint)
	{
		switch (beakMemory.readMemory(memoryPointer))
		{
		case 0x02:
		{
			if (beakMemory.getBC() == writeBreakpointAddress)
			{
				if (writeBreakpointValue)
				{
					if (((beakMemory.readMemory(memoryPointer + 2) << 4) | beakMemory.readMemory(memoryPointer + 1)) == breakpointValue)
					{
						return true;
					}

				}
				else
				{
					return true;
				}
			}
			break;
		}
		case 0x08:
		{
			if (((beakMemory.readMemory(memoryPointer + 2) << 4) | beakMemory.readMemory(memoryPointer + 1)) == writeBreakpointAddress)
			{
				if (writeBreakpointValue)
				{
					if (beakMemory.getA() == breakpointValue)
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
			break;
		}
		case 0x12:
		{
			if (beakMemory.getDE() == writeBreakpointAddress)
			{
				if (writeBreakpointValue)
				{
					if (beakMemory.getA() == breakpointValue)
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
		}
		case 0x36:
		{
			if (beakMemory.getHL() == writeBreakpointAddress)
			{
				if (writeBreakpointValue)
				{
					if (beakMemory.readMemory(memoryPointer + 1) == breakpointValue)
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
			break;
		}
		case 0x22:
		case 0x32:
		case 0x77:
		{
			if (beakMemory.getHL() == writeBreakpointAddress)
			{
				if (writeBreakpointValue)
				{
					if (beakMemory.getA() == breakpointValue)
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
			break;
		}
		case 0x70:
		{
			if (beakMemory.getHL() == writeBreakpointAddress)
			{
				if (writeBreakpointValue)
				{
					if (beakMemory.getB() == breakpointValue)
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
			break;
		}
		case 0x71:
		{
			if (beakMemory.getHL() == writeBreakpointAddress)
			{
				if (writeBreakpointValue)
				{
					if (beakMemory.getC() == breakpointValue)
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
			break;
		}
		case 0x72:
		{
			if (beakMemory.getHL() == writeBreakpointAddress)
			{
				if (writeBreakpointValue)
				{
					if (beakMemory.getD() == breakpointValue)
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
			break;
		}
		case 0x73:
		{
			if (beakMemory.getHL() == writeBreakpointAddress)
			{
				if (writeBreakpointValue)
				{
					if (beakMemory.getE() == breakpointValue)
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
			break;
		}
		case 0x74:
		{
			if (beakMemory.getHL() == writeBreakpointAddress)
			{
				if (writeBreakpointValue)
				{
					if (beakMemory.getH() == breakpointValue)
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
			break;
		}
		case 0x75:
		{
			if (beakMemory.getHL() == writeBreakpointAddress)
			{
				if (writeBreakpointValue)
				{
					if (beakMemory.getL() == breakpointValue)
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
			break;
		}
		case 0x34:
		{
			if (beakMemory.getHL() == writeBreakpointAddress)
			{
				if (writeBreakpointValue)
				{
					if ((beakMemory.readMemory(beakMemory.getHL()) - 1) == breakpointValue)
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}

			break;
		}
		case 0x35:
		{
			if (beakMemory.getHL() == writeBreakpointAddress)
			{
				if (writeBreakpointValue)
				{
					if ((beakMemory.readMemory(beakMemory.getHL()) + 1) == breakpointValue)
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
			break;
		}
		case 0xCB:
		{

			//Currently ignores breakpoint write value for CB functions
			switch (beakMemory.readMemory(memoryPointer + 1))
			{
			case 0x0E:
			case 0x16:
			case 0x26:
			case 0x2E:
			case 0x36:
			case 0x3E:
			case 0xC6:
			case 0xCE:
			case 0xD6:
			case 0xDE:
			case 0xE6:
			case 0xEE:
			case 0xF6:
			case 0xFE:
			{
				if (beakMemory.getHL() == writeBreakpointAddress)
				{
					if (!writeBreakpointValue)
					{
						return true;
					}
				}

				break;
			}
			}
			break;
		}
		case 0xA6:
		{
			if (beakMemory.getHL() == writeBreakpointAddress)
			{
				if (writeBreakpointValue)
				{
					if ((beakMemory.readMemory(beakMemory.getHL()) & beakMemory.getA()) == breakpointValue)
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
			break;
		}
		case 0xAE:
		{
			if (beakMemory.getHL() == writeBreakpointAddress)
			{
				if (writeBreakpointValue)
				{
					if ((beakMemory.readMemory(beakMemory.getHL()) ^ beakMemory.getA()) == breakpointValue)
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
			break;
		}
		case 0xB6:
		{
			if (beakMemory.getHL() == writeBreakpointAddress)
			{
				if (writeBreakpointValue)
				{
					if ((beakMemory.readMemory(beakMemory.getHL()) | beakMemory.getA()) == breakpointValue)
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
			break;
		}

		}

	}

	return false;
}
