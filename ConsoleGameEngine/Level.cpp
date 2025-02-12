#include "Macros.h"

#include "LinkedList.h"
#include "Level.h"
#include "Actor.h"

Level::Level()
	: actors_(new LinkedList<Actor>)
{
	// TODO : World-> Spawn Actor �Լ� ��������.
}

Level::~Level()
{
	if(nullptr != actors_)
	{
		delete actors_;
		actors_ = nullptr;
	}
}
