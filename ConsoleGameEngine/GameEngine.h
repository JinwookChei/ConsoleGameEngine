#pragma once


class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	bool Initialize();

	void GameLoop();
protected:
	void CleanUp();

private:
	class ConsoleRenderer* renderer_;
	class ConsoleWorld* world_;
};

extern GameEngine* GEngine;