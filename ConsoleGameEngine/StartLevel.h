#pragma once
#include "Level.h"

class StartLevel : public Level
{
public:
	StartLevel();
	virtual ~StartLevel();

	void BeginPlay() override;
	void Tick() override;
};