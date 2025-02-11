#include "Macros.h"

#include "Level.h"
#include "Actor.h"

Level::Level()
{
	actor_ = new Actor();
}

Level::~Level()
{
	if(nullptr != actor_)
	{
		delete actor_;
		actor_ = nullptr;
	}
}
