#pragma once
#include "Coordinate.h"

class Actor	
{
public:
	Actor();
	Actor(Coord coord);
	Actor(unsigned int X, unsigned int Y);
	virtual ~Actor();

	Coord GetCoord() const;

	wchar_t GetMesh() const;

private:
	// TODO : Change Struct
	Coord coord_;

	// mesh
	wchar_t mesh_;

	// getWorld -> 월드에서 스폰 가능. 레벨의 getWOrld를 통해접근.
	// Level
	
};