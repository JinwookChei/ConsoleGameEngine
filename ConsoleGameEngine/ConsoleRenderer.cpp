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


#include "ConsoleRenderer.h"

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

void ConsoleRenderer::CleanUp()
{
	if (nullptr != buffer_)
	{
		delete[] buffer_;
		buffer_ = nullptr;
	}
}

