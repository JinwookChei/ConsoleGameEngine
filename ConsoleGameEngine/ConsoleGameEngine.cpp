#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif  // _DEBUG


#ifdef DEBUG
#define DEBUG_BREAK() __debugbreak()
#else
#define DEBUG_BREAK()
#endif


#include "ConsoleGameEngine.h"
#include "ConsoleRenderer.h"


ConsoleGameEngine::ConsoleGameEngine()
	: renderer_(nullptr)
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

	return true;
}

void ConsoleGameEngine::GameLoop()
{
	while(1)
	{
		renderer_->Render();
	}

}


