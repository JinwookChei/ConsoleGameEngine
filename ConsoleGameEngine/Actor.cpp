#include "Actor.h"

Actor::Actor()
	: mesh_(L'A'),
	coord_()
{
}

Actor::Actor(Coord coord)
	: mesh_(L'A'),
	coord_(coord)
{
}

Actor::Actor(unsigned int X, unsigned int Y)
	: mesh_(L'A'),
	coord_(X, Y)
{
}

Actor::~Actor()
{
}

void Actor::BeginPlay()
{
}

void Actor::Tick()
{
}


Coord Actor::GetCoord() const
{
	return coord_;
}

wchar_t Actor::GetMesh() const
{
	return mesh_;
}
