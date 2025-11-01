#include "Enemy/Vanguard.h"
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
		_playerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
		_playerSpaceship.lock()->SetActorLocation({ 300, 490 });
		_playerSpaceship.lock()->SetActorRotation(-90.0f);

		weak<Vanguard> enemySpaceship = newWorld.lock()->SpawnActor<Vanguard>();
		enemySpaceship.lock()->SetActorLocation(sf::Vector2f{ 100.0f, 50.0f });
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