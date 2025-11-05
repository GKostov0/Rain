#include "Level/GameLevelOne.h"

#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Enemy/HexagonStage.h"
#include "Enemy/UFOStage.h"

#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include "framework/World.h"

#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"

#include "Player/PlayerSpaceship.h"
#include "Player/PlayerManager.h"

namespace rn
{
	GameLevelOne::GameLevelOne(Application* owner)
		: World{owner}
	{
	}

	void GameLevelOne::BeginPlay()
	{
		Player newPlayer = PlayerManager::Get().CreateNewPlayer();
		_playerSpaceship = newPlayer.SpawnSpaceship(this);
		_playerSpaceship.lock()->onActorDestroy.BindAction(GetWeakReference(), &GameLevelOne::PlayerSpaceshipDestroyed);
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<WaitStage>{ new WaitStage{ this, 2.0f } });
		AddStage(shared<VanguardStage>{ new VanguardStage{ this } });		// Vanguards

		AddStage(shared<WaitStage>{ new WaitStage{ this, 2.0f } });
		AddStage(shared<TwinBladeStage>{ new TwinBladeStage{ this } });		// Twin Blades

		AddStage(shared<WaitStage>{ new WaitStage{ this, 2.0f } });
		AddStage(shared<HexagonStage>{ new HexagonStage{ this } });			// Hexagons

		AddStage(shared<WaitStage>{ new WaitStage{ this, 2.0f } });
		AddStage(shared<UFOStage>{ new UFOStage{ this } });					// UFOs

		AddStage(shared<WaitStage>{ new WaitStage{ this, 2.0f } });
	}

	void GameLevelOne::PlayerSpaceshipDestroyed(Actor* destroyedSpaceship)
	{
		_playerSpaceship = PlayerManager::Get().GetPlayer()->SpawnSpaceship(this);
		if (!_playerSpaceship.expired())
		{
			_playerSpaceship.lock()->onActorDestroy.BindAction(GetWeakReference(), &GameLevelOne::PlayerSpaceshipDestroyed);
		}
		else
		{
			GameOver();
		}
	}

	void GameLevelOne::GameOver()
	{
		LOG("=== GAME OVER!!! ===");
	}
}