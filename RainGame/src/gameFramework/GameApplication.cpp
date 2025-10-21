#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "config.h"

rn::Application* GetApplication()
{
	return new rn::GameApplication();
}

namespace rn
{
	GameApplication::GameApplication()
		: Application{600, 980, "Rain", sf::Style::Titlebar | sf::Style::Close}
	{
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>();
		_destoryThis = newWorld.lock()->SpawnActor<Actor>();
		_destoryThis.lock()->SetTexture(GetResourceDirectory() + "SpaceShooterRedux/PNG/playerShip2_blue.png");
		_counter = 0;
	}

	void GameApplication::Tick(float deltaTime)
	{
		_counter += deltaTime;

		if (_counter > 2.0f)
		{
			if (!_destoryThis.expired())
			{
				_destoryThis.lock()->Destroy();
			}
		}
	}
}