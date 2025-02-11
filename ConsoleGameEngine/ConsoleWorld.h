#pragma once

class Level;
class Actor;
class ConsoleRenderer;

class ConsoleWorld
{
public:
	ConsoleWorld();
	~ConsoleWorld();

	bool Initialize();

	void OnRender(ConsoleRenderer* renderer) const;

	bool SpawnActor(Actor* actor) const;
	//
	//void changeLevel

	Level* GetLevel() const;
	bool ChangeLevel(Level* level);

private:
	Level* level_;
	
};