#pragma once

class ConsoleWorld;
class Actor;

template<typename T>
class LinkedList;

class Level
{
public:
	Level();
	virtual ~Level();

	bool Initilize(const ConsoleWorld* worldRef);

	virtual void BeginPlay();

	virtual void Tick();
	
	LinkedList<Actor>* GetActors() const;

	const ConsoleWorld* GetWorld() const;

private:
	const ConsoleWorld* world_;

	LinkedList<Actor>* actors_;

	// TODO : actor pool ¸¸µé±â
	LinkedList<Actor>* actorsPool;
};