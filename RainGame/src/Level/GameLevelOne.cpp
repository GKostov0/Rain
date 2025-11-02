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

namespace rn
{
	GameLevelOne::GameLevelOne(Application* owner)
		: World{owner}
	{
		_playerSpaceship = SpawnActor<PlayerSpaceship>();
		_playerSpaceship.lock()->SetActorLocation({ 300, 490 });
		_playerSpaceship.lock()->SetActorRotation(-90.0f);
	}

	void GameLevelOne::BeginPlay()
	{
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
}