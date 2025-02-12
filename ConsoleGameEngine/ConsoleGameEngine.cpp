#include "Macros.h"


#include "ConsoleGameEngine.h"
#include "ConsoleRenderer.h"
#include "ConsoleWorld.h"



ConsoleGameEngine::ConsoleGameEngine()
	: renderer_(nullptr),
	world_(nullptr)
{
}

ConsoleGameEngine::~ConsoleGameEngine()
{
	CleanUp();
}

void ConsoleGameEngine::CleanUp()
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

bool ConsoleGameEngine::Initialize()
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

void ConsoleGameEngine::GameLoop()
{
	while(1)
	{
		renderer_->ModifyRendererSizeFromConsoleSize();
		world_->Update(renderer_);
		renderer_->Render();
	}
}


