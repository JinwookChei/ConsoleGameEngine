#include "Macros.h"


#include "GameEngine.h"
#include "ConsoleRenderer.h"
#include "ConsoleWorld.h"



GameEngine::GameEngine()
	: renderer_(nullptr),
	world_(nullptr)
{
}

GameEngine::~GameEngine()
{
	CleanUp();
}

void GameEngine::CleanUp()
{
	if (nullptr != renderer_)
	{
		delete renderer_;
		renderer_ = nullptr;
	}

	if (nullptr != world_)
	{
		delete world_;
		world_ = nullptr;
	}
}

bool GameEngine::Initialize()
{
	renderer_ = new ConsoleRenderer;
	if (nullptr == renderer_)
	{
		DEBUG_BREAK();
		return false;	
	}

	if (false == renderer_->Initialize())
	{
		DEBUG_BREAK();
		return false;
	}


	world_ = new ConsoleWorld;
	if (nullptr == world_)
	{
		DEBUG_BREAK();
		return false;
	}

	if (false == world_->Initialize())
	{
		DEBUG_BREAK();
		return false;
	}


	return true;
}

void GameEngine::GameLoop()
{
	while(1)
	{
		renderer_->ModifyRendererSizeFromConsoleSize();
		world_->Update(renderer_);
		renderer_->Render();
	}
}


