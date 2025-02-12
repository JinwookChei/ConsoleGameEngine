#include "Macros.h"

#include "ConsoleWorld.h"
#include "ConsoleRenderer.h"
#include "Actor.h"
#include "Level.h"
#include "StartLevel.h"
#include "LinkedList.h"

ConsoleWorld::ConsoleWorld()
	: level_(nullptr)
{
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
	if (false == ChangeLevel<StartLevel>())
	{
		return false;
	}

	return true;
}

void ConsoleWorld::Update(ConsoleRenderer* renderer) const
{
	if (nullptr == renderer)
	{
		DEBUG_BREAK();
		return;
	}
	
	renderer->UpdateBuffer(level_);
}


Level* ConsoleWorld::GetLevel() const
{
	if (nullptr == level_)
	{
		return nullptr;
	}
	
	return level_;
}

void ConsoleWorld::OnBeginPlay() const
{
	level_->BeginPlay();
}
