#pragma once


class Actor;

template<typename T>
class LinkedList;

class Level
{
public:
	Level();
	virtual ~Level();

	// Temp
	LinkedList<Actor>* actors_;
	//Actor* actor_;
};