#pragma once

class Level;

class ConsoleRenderer
{
public:
	ConsoleRenderer();
	ConsoleRenderer(unsigned int bufferWidth, unsigned int bufferHeight, wchar_t baseBlock);

	virtual ~ConsoleRenderer();

	bool Initialize();

	void Render();

	// TODO : Function Name Change
	void Renderlevel(Level* level);

protected:
	void CleanUp();

	
private:
	void* consoleHandle_;

	unsigned int bufferWidth_;

	unsigned int bufferHeight_;

	wchar_t* buffer_;  // ¸Ê

	wchar_t bufferBlock_;  // ¸ÊÀÇ ±âº» ÇüÅÂ
};
