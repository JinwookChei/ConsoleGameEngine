#include "Macros.h"

#include "ConsoleRenderer.h"
#include "ConsoleWorld.h"
#include "Level.h"
#include "Actor.h"
#include "LinkedList.h"

#include <Windows.h>
#include <locale.h>
#include <wchar.h>
#include <stdio.h>

ConsoleRenderer::ConsoleRenderer()
	: consoleHandle_(nullptr),
	bufferWidth_(100),
	bufferHeight_(100),
	buffer_(nullptr),
	bufferBlock_(L'□')
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

	if (false == GetConsoleSize(bufferWidth_, bufferHeight_))
	{
		DEBUG_BREAK();
		return false;
	}

	buffer_ = new wchar_t[bufferWidth_ * bufferHeight_];
	wmemset(buffer_, bufferBlock_, bufferWidth_ * bufferHeight_);

	return true;
}

void ConsoleRenderer::Renderlevel(Level* level)
{
	if (nullptr == level)
	{
		DEBUG_BREAK();
		return;
	}

	LINK_ITEM<Actor>* pCur = level->actors_->head_;

	while (pCur)
	{
		Coord actorCoord = pCur->item_->GetCoord();
		wchar_t actorMesh = pCur->item_->GetMesh();

		buffer_[actorCoord.X_ + actorCoord.Y_ * bufferWidth_] = actorMesh;
	}

	// TODO : 코드 수정 (임시 테스트 코드임)
	
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

void ConsoleRenderer::ModifyRendererSizeFromConsoleSize()
{
	unsigned int consoleWidth;
	unsigned int consoleHeight;

	if (false == GetConsoleSize(consoleWidth, consoleHeight))
	{
		DEBUG_BREAK();
		return;
	}

	if (bufferWidth_ != consoleWidth || bufferHeight_ != consoleHeight)
	{
		bufferWidth_ = consoleWidth;
		bufferHeight_ = consoleHeight;

		delete[] buffer_;

		buffer_ = new wchar_t[bufferWidth_ * bufferHeight_];
		wmemset(buffer_, bufferBlock_, bufferWidth_ * bufferHeight_);

		return;
	}
}


void ConsoleRenderer::CleanUp()
{
	if (nullptr != buffer_)
	{
		delete[] buffer_;
		buffer_ = nullptr;
	}
}


bool ConsoleRenderer::GetConsoleSize(unsigned int& outConsoleWidth, unsigned int& outConsoleHeight) const
{
	CONSOLE_SCREEN_BUFFER_INFO csbi = { 0 };
	if (FALSE == GetConsoleScreenBufferInfo(consoleHandle_, &csbi)) {
		DEBUG_BREAK();
		return false;
	}

	outConsoleWidth = csbi.dwSize.X;
	outConsoleHeight = csbi.dwSize.Y;

	return true;
}

