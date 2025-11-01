#include "Level/GameLevelOne.h"
#include "Enemy/Vanguard.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include "framework/World.h"

#include "Player/PlayerSpaceship.h"

namespace rn
{
	GameLevelOne::GameLevelOne(Application* owner)
		: World{owner}
	{
		_playerSpaceship = SpawnActor<PlayerSpaceship>();
		_playerSpaceship.lock()->SetActorLocation({ 300, 490 });
		_playerSpaceship.lock()->SetActorRotation(-90.0f);

		weak<Vanguard> enemySpaceship = SpawnActor<Vanguard>();
		enemySpaceship.lock()->SetActorLocation(sf::Vector2f{ 100.0f, 50.0f });	
	}

	void GameLevelOne::BeginPlay()
	{
		TimerManager::Get().SetTimer(GetWeakReference(), &GameLevelOne::TimerCallbackTest, 5.0f);
	}

	void GameLevelOne::TimerCallbackTest()
	{
	}
}