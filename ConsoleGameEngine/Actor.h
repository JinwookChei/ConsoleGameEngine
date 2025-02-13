#pragma once
#include "Coordinate.h"
#include "LinkedList.h"


class Actor
{
public:
	Actor();
	Actor(Coord coord);
	Actor(unsigned int X, unsigned int Y);
	virtual ~Actor();

	virtual void BeginPlay();

	virtual void Tick();

	Coord GetCoord() const;

	wchar_t GetMesh() const;

	void* spawnedlinkItem_;

protected:
	Coord coord_;

	// mesh
	wchar_t mesh_;
};