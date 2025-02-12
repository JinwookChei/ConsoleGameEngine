#include "Macros.h"

#include "LinkedList.h"
#include "Level.h"
#include "Actor.h"

Level::Level()
	: world_(nullptr),
	actors_(new LinkedList<Actor>)
{
}

Level::~Level()
{
	if (nullptr != actors_)
	{
		delete actors_;
		actors_ = nullptr;
	}
}

bool Level::Initilize(const ConsoleWorld* worldRef)
{
	if (nullptr == worldRef)
	{
		DEBUG_BREAK();
		return false;
	}

	world_ = worldRef;
	return true;
}

void Level::BeginPlay()
{
}

void Level::Tick()
{
}

LinkedList<Actor>* Level::GetActors() const
{
	return actors_;
}

const ConsoleWorld* Level::GetWorld() const
{
	if (nullptr == world_)
	{
		DEBUG_BREAK();
		return nullptr;
	}

	return world_;
}



