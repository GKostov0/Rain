#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "Player/PlayerSpaceShip.h"
#include "framework/AssetManager.h"
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
		AssetManager::Get().SetAssetRootDirectory(GetResourceDirectory());

		weak<World> newWorld = LoadWorld<World>();
		_playerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceShip>();
		_playerSpaceship.lock()->SetActorLocation({ 300, 490 });
		_playerSpaceship.lock()->SetActorRotation(-90.0f);

		weak<SpaceShip> testSpaceship = newWorld.lock()->SpawnActor<SpaceShip>();
		testSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
		testSpaceship.lock()->SetActorLocation(sf::Vector2f{ 100.0f, 50.0f });
		testSpaceship.lock()->SetTeamID(2);
		_counter = 0;
	}

	void GameApplication::Tick(float deltaTime)
	{
		/*_counter += deltaTime;

		if (_counter > 10.0f)
		{
			if (!_playerSpaceship.expired())
			{
				_playerSpaceship.lock()->Destroy();
			}
		}*/
	}
}