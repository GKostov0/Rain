#include "Level/GameLevelOne.h"

#include "Enemy/Vanguard.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"

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
		AddStage(shared<VanguardStage>{ new VanguardStage{ this } });
		AddStage(shared<WaitStage>{ new WaitStage{ this, 2.0f } });
		AddStage(shared<TwinBladeStage>{ new TwinBladeStage{ this } });
		AddStage(shared<WaitStage>{ new WaitStage{ this, 2.0f } });
	}
}