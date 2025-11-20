#include "Level/GameLevelOne.h"

#include "framework/Actor.h"
#include "framework/Application.h"
#include "framework/AssetManager.h"
#include "framework/BackdropActor.h"
#include "framework/TimerManager.h"
#include "framework/World.h"

#include "Enemy/ChaosStage.h"
#include "Enemy/BossStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/HexagonStage.h"
#include "Enemy/UFOStage.h"

#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"

#include "Player/PlayerSpaceship.h"
#include "Player/PlayerManager.h"

#include "widgets/GameplayHUD.h"

namespace rn
{
	GameLevelOne::GameLevelOne(Application* owner)
		: World{owner}
	{
	}

	void GameLevelOne::BeginPlay()
	{
		SpawnCosmetics();

		Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
		_playerSpaceship = newPlayer.SpawnSpaceship(this);
		_playerSpaceship.lock()->onActorDestroy.BindAction(GetWeakReference(), &GameLevelOne::PlayerSpaceshipDestroyed);
		_gameplayHUD = SpawnHUD<GameplayHUD>();

		_gameplayHUD.lock()->onRestartButtonClicked.BindAction(GetWeakReference(), &GameLevelOne::RestartGame);
		_gameplayHUD.lock()->onQuitButtonClicked.BindAction(GetWeakReference(), &GameLevelOne::QuitGame);
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<WaitStage>{ new WaitStage{ this, 2.0f } });
		AddStage(shared<BossStage>{ new BossStage{ this } });				// Boss

		AddStage(shared<WaitStage>{ new WaitStage{ this, 2.0f } });
		AddStage(shared<ChaosStage>{ new ChaosStage{ this } });				// Chaos

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

	void GameLevelOne::AllGameStageFinished()
	{
		_gameplayHUD.lock()->GameFinished(true);
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

	void GameLevelOne::SpawnCosmetics()
	{
		weak<BackdropActor> backdrop = SpawnActor<BackdropActor>("SpaceShooterRedux/Backgrounds/darkPurple.png");
	}

	void GameLevelOne::RestartGame()
	{
		PlayerManager::Get().Reset();
		GetApplication()->LoadWorld<GameLevelOne>();
	}

	void GameLevelOne::GameOver()
	{
		LOG("=== GAME OVER!!! ===");
		_gameplayHUD.lock()->GameFinished(false);
	}

	void GameLevelOne::QuitGame()
	{
		GetApplication()->QuitApplication();
	}
}