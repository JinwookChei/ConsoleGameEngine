#pragma once

class Level;

class ConsoleRenderer
{
public:
	ConsoleRenderer();
	ConsoleRenderer(unsigned int bufferWidth, unsigned int bufferHeight, wchar_t baseBlock);

	virtual ~ConsoleRenderer();

	bool Initialize();

	// TODO : Function Name Change
	void UpdateBuffer(Level* level);

	void Render();

	void ModifyRendererSizeFromConsoleSize();

	

protected:
	void CleanUp();
private: 
	bool GetConsoleSize(unsigned int& outConsoleWidth, unsigned int& outConsoleHeight) const;

	
private:
	void* consoleHandle_;

	unsigned int bufferWidth_;

	unsigned int bufferHeight_;

	wchar_t* buffer_;  // ¸Ê

	wchar_t bufferBlock_;  // ¸ÊÀÇ ±âº» ÇüÅÂ
};
