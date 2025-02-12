#include "Macros.h"
#include "StartLevel.h"
#include "ConsoleWorld.h"
#include "Actor.h"

StartLevel::StartLevel()
	: Level()
{
}

StartLevel::~StartLevel()
{
}

void StartLevel::BeginPlay()
{
	Actor* actor1 = GetWorld()->SpawnActor<Actor>({10,10});
	Actor* actor2 = GetWorld()->SpawnActor<Actor>({0,1});
	Actor* actor3 = GetWorld()->SpawnActor<Actor>({1,0});
}

void StartLevel::Tick()
{
}
