#include "Player.h"
#include "Coordinate.h"


Player::Player()
	: Actor()
{
	mesh_ = L'P';
}

Player::Player(Coord coord)
	: Actor(coord)
{
	mesh_ = L'P';
}

Player::Player(unsigned int X, unsigned int Y)
	: Actor(X, Y)
{
	mesh_ = L'P';
}

Player::~Player()
{
}

void Player::BeginPlay()
{
}

void Player::Tick()
{
}
