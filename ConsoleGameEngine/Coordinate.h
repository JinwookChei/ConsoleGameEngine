#pragma once

struct Coord
{
public:
	Coord();
	Coord(unsigned int X, unsigned int Y);
	~Coord();

	
	unsigned int X_;
	unsigned int Y_;
};