#include "Macros.h"

#include "ConsoleWorld.h"
#include "ConsoleRenderer.h"
#include "Actor.h"
#include "Level.h"
#include "StartLevel.h"

ConsoleWorld::ConsoleWorld()
{
	level_ = new StartLevel();
}

ConsoleWorld::~ConsoleWorld()
{
	if (nullptr != level_)
	{
		delete level_;
		level_ = nullptr;
	}
}

bool ConsoleWorld::Initialize()
{
	if (nullptr == level_)
	{
		return false;
	}

	return true;
}

void ConsoleWorld::OnRender(ConsoleRenderer* renderer) const
{
	if (nullptr == renderer)
	{
		DEBUG_BREAK();
		return;
	}

	renderer->Renderlevel(level_);
}

bool ConsoleWorld::SpawnActor(Actor* actor) const
{
	return false;
}

Level* ConsoleWorld::GetLevel() const
{
	if (nullptr == level_)
	{
		return nullptr;
	}
	
	return level_;
}

bool ConsoleWorld::ChangeLevel(Level* level)
{
	if (nullptr == level)
	{
		return false;
	}

	level_ = level;
	return true;
}
