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
		newWorld.lock()->SpawnActor<Actor>();
		_playerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceShip>();
		_playerSpaceship.lock()->SetActorLocation({ 300, 490 });
		_playerSpaceship.lock()->SetActorRotation(0.0f);
	}

	void GameApplication::Tick(float deltaTime)
	{
		//_counter += deltaTime;

		//if (_counter > 2.0f)
		//{
		//	if (!_playerSpaceship.expired())
		//	{
		//		_playerSpaceship.lock()->Destroy();
		//	}
		//}
	}
}