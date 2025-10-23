#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "SpaceShip/SpaceShip.h"
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
		_playerSpaceship = newWorld.lock()->SpawnActor<SpaceShip>();
		_playerSpaceship.lock()->SetTexture(GetResourceDirectory() + "SpaceShooterRedux/PNG/playerShip2_blue.png");
		_playerSpaceship.lock()->SetActorLocation({ 300, 490 });
		_playerSpaceship.lock()->SetActorRotation(-90.0f);
		_playerSpaceship.lock()->SetVelocity(sf::Vector2f{0, -200});
		_counter = 0;
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