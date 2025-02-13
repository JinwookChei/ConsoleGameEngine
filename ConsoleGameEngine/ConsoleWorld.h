#pragma once
#include <iostream>
#include "Coordinate.h"
#include "LinkedList.h"
#include "Level.h"

//class Level;
class Actor;
class ConsoleRenderer;


class ConsoleWorld
{
public:
	ConsoleWorld();
	~ConsoleWorld();

	bool Initialize();

	void Update(ConsoleRenderer* renderer) const;

	template <typename T, typename std::enable_if<std::is_base_of<Actor, T>::value>::type* = nullptr>
	T* SpawnActor(unsigned int CoordX, unsigned int CoordY) const;

	template <typename T, typename std::enable_if<std::is_base_of<Actor, T>::value>::type* = nullptr>
	T* SpawnActor(Coord coord) const;
	
	template <typename T, typename std::enable_if<std::is_base_of<Actor, T>::value>::type* = nullptr>
	bool DestroyActor(T* destroyActor) const;

	Level* GetLevel() const;

	template<typename T>
	bool ChangeLevel();

private:
	void OnBeginPlay() const;

private:
	Level* level_;

};


template <typename T, typename std::enable_if<std::is_base_of<Actor, T>::value>::type*>
inline T* ConsoleWorld::SpawnActor(unsigned int coordX, unsigned int coordY) const
{
	LINK_ITEM<T>* actorLinkItem = new LINK_ITEM<T>(coordX, coordY);
	if (nullptr == actorLinkItem)
	{
		DEBUG_BREAK();
		return nullptr;
	}

	actorLinkItem->item_->spawnedlinkItem_ = actorLinkItem;

	if (!level_->GetActors()->PushFront((LINK_ITEM<Actor>*)actorLinkItem))
	{
		DEBUG_BREAK();
		return nullptr;
	}

	return actorLinkItem->item_;
}


template <typename T, typename std::enable_if<std::is_base_of<Actor, T>::value>::type*>
inline T* ConsoleWorld::SpawnActor(Coord coord) const
{
	LINK_ITEM<T>* actorLinkItem = new LINK_ITEM<T>(coord);
	if (nullptr == actorLinkItem)
	{
		DEBUG_BREAK();
		return nullptr;
	}

	actorLinkItem->item_->spawnedlinkItem_ = actorLinkItem;

	if (!level_->GetActors()->PushFront((LINK_ITEM<Actor>*)actorLinkItem))
	{
		DEBUG_BREAK();
		return nullptr;
	}

	return actorLinkItem->item_;
}

template <typename T, typename std::enable_if<std::is_base_of<Actor, T>::value>::type*>
inline bool ConsoleWorld::DestroyActor(T* destroyActor) const
{
	LINK_ITEM<Actor>* destroyActorLinkItem = (LINK_ITEM<Actor>*)(Actor*)destroyActor->spawnedlinkItem_;
	if (nullptr == destroyActor)
	{
		DEBUG_BREAK();
		return false;
	}

	return level_->GetActors()->PopItem(destroyActorLinkItem);
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