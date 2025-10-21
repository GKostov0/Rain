#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

rn::Application* GetApplication()
{
	return new rn::GameApplication();
}

namespace rn
{
	GameApplication::GameApplication()
	{
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>();
	}
}