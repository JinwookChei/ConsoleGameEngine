#pragma once


class ConsoleGameEngine
{
public:
	ConsoleGameEngine();
	~ConsoleGameEngine();

	bool Initialize();

	void GameLoop();
protected:
	void CleanUp();

private:
	class ConsoleRenderer* renderer_;
	class ConsoleWorld* world_;
};

extern ConsoleGameEngine* GEngine;