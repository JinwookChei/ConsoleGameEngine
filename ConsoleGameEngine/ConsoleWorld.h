#pragma once
#include "Coordinate.h"
#include "LinkedList.h"
#include "Level.h"

class Level;
class Actor;
class ConsoleRenderer;


class ConsoleWorld
{
public:
	ConsoleWorld();
	~ConsoleWorld();

	bool Initialize();

	void Update(ConsoleRenderer* renderer) const;

	template<typename T>
	T* SpawnActor(unsigned int CoordX, unsigned int CoordY) const;

	template<typename T>
	T* SpawnActor(Coord coord) const;

	Level* GetLevel() const;

	template<typename T>
	bool ChangeLevel();

private:
	void OnBeginPlay() const;

private:
	Level* level_;
	
};

template<typename T>
inline T* ConsoleWorld::SpawnActor(unsigned int coordX, unsigned int coordY) const
{
	Actor* actor = new T{ coordX, coordY };
	if (nullptr == actor)
	{
		DEBUG_BREAK();
		return nullptr;
	}
	
	level_->GetActors()->PushFront(actor);

	return actor;
}

template<typename T>
inline T* ConsoleWorld::SpawnActor(Coord coord) const
{
	Actor* actor = new T{ coord };
	if (nullptr == actor)
	{
		DEBUG_BREAK();
		return nullptr;
	}

	level_->GetActors()->PushFront(actor);

	return actor;
}

template<typename T>
bool ConsoleWorld::ChangeLevel()
{
	if (nullptr != level_)
	{
		delete level_;
	}

	level_ = new T;

	if (nullptr == level_)
	{
		DEBUG_BREAK();
		return false;
	}

	if (false == level_->Initilize(this))
	{
		DEBUG_BREAK();
		return false;
	}

	OnBeginPlay();

	return true;
}