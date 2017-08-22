#pragma once

using namespace std;

#ifndef COLORH
#define COLORH

class Color
{
public:
	static Color Black;

	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	int getInt();

	Color();
	Color(unsigned char r, unsigned char g, unsigned char b);
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	bool operator!=(Color& operand);
	void operator*=(Color& operand);
	bool operator==(Color& operand);

	friend Color operator*(Color& lhs, Color& rhs)
	{
		return Color(lhs.r * rhs.r, rhs.g * rhs.g, lhs.b * rhs.b);
	}

};

#endif