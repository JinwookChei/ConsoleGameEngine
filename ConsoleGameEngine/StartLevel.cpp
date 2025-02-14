#include "Macros.h"
#include "StartLevel.h"
#include "ConsoleWorld.h"
#include "Actor.h"
#include "Player.h"

StartLevel::StartLevel()
	: Level()
{
}

StartLevel::~StartLevel()
{
}

void StartLevel::BeginPlay()
{
	Player* player = GetWorld()->SpawnActor<Player>({10,10});
	Actor* actor1 = GetWorld()->SpawnActor<Actor>({0,1});
	Actor* actor2 = GetWorld()->SpawnActor<Actor>(1,0);

	GetWorld()->DestroyActor(player);
	GetWorld()->DestroyActor(actor1);

	//GetActors()->PopAll();
	//GetActors()->PopAll();
}

void StartLevel::Tick()
{
}
