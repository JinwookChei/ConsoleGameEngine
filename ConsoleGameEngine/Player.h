#pragma once

#include "Coordinate.h"
#include "Actor.h"


class Player : public Actor
{
public:
	Player();
	Player(Coord coord);
	Player(unsigned int X, unsigned int Y);

	~Player() override;

	void BeginPlay() override;

	void Tick() override;

private:

};
