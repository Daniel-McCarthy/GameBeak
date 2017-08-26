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
	Color(unsigned char newR, unsigned char newG, unsigned char newB);
	Color(unsigned char newR, unsigned char newG, unsigned char newB, unsigned char newA);

	bool operator!=(Color& operand);
	void operator*=(Color& operand);
	bool operator==(Color& operand);

	friend Color operator*(Color& lhs, Color& rhs)
	{
		return Color(lhs.r * rhs.r, rhs.g * rhs.g, lhs.b * rhs.b);
	}

};

#endif