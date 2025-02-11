#include "Macros.h"

#include "ConsoleRenderer.h"
#include "ConsoleWorld.h"
#include "Level.h"
#include "Actor.h"

#include <Windows.h>
#include <locale.h>
#include <wchar.h>
#include <stdio.h>

ConsoleRenderer::ConsoleRenderer()
	: consoleHandle_(nullptr),
	bufferWidth_(100),
	bufferHeight_(100),
	buffer_(nullptr),
	bufferBlock_(L'бр')
{

}

ConsoleRenderer::ConsoleRenderer(unsigned int bufferWidth, unsigned int bufferHeight, wchar_t baseBlock)
	: consoleHandle_(nullptr),
	bufferWidth_(bufferWidth),
	bufferHeight_(bufferHeight),
	buffer_(nullptr),
	bufferBlock_(baseBlock)
{

}

ConsoleRenderer::~ConsoleRenderer()
{
	CleanUp();
}

bool ConsoleRenderer::Initialize()
{
	setlocale(LC_ALL, "KOR");

	consoleHandle_ = GetStdHandle(STD_OUTPUT_HANDLE);

	if (nullptr == consoleHandle_)
	{
		DEBUG_BREAK();
		return false;
	}

	buffer_ = new wchar_t[bufferWidth_ * bufferHeight_];
	wmemset(buffer_, bufferBlock_, bufferWidth_ * bufferHeight_);
}

void ConsoleRenderer::Render()
{
	if (nullptr == consoleHandle_ || nullptr == buffer_) {
		DEBUG_BREAK();
		return;
	}

	DWORD lenOut = 0;
	COORD pos = { 0 };
	WriteConsoleOutputCharacter(consoleHandle_, buffer_, bufferWidth_ * bufferHeight_, pos, &lenOut);
}


void ConsoleRenderer::Renderlevel(Level* level)
{
	if (nullptr == level)
	{
		DEBUG_BREAK();
		return;
	}

	unsigned int PosX = level->actor_->X;
	unsigned int PosY = level->actor_->Y;
	wchar_t actor = level->actor_->mesh;

	buffer_[PosX + PosY * bufferWidth_] = actor;
}

void ConsoleRenderer::CleanUp()
{
	if (nullptr != buffer_)
	{
		delete[] buffer_;
		buffer_ = nullptr;
	}
}

