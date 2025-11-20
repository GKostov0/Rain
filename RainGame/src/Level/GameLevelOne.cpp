#include "Level/GameLevelOne.h"

#include "framework/Actor.h"
#include "framework/Application.h"
#include "framework/AssetManager.h"
#include "framework/BackdropActor.h"
#include "framework/BackgroundLayer.h"
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
		AddStage(shared<VanguardStage>{ new VanguardStage{ this } });		// Vanguards

		AddStage(shared<WaitStage>{ new WaitStage{ this, 2.0f } });
		AddStage(shared<TwinBladeStage>{ new TwinBladeStage{ this } });		// Twin Blades

		AddStage(shared<WaitStage>{ new WaitStage{ this, 2.0f } });
		AddStage(shared<HexagonStage>{ new HexagonStage{ this } });			// Hexagons

		AddStage(shared<WaitStage>{ new WaitStage{ this, 2.0f } });
		AddStage(shared<UFOStage>{ new UFOStage{ this } });					// UFOs

		AddStage(shared<WaitStage>{ new WaitStage{ this, 2.0f } });
		AddStage(shared<ChaosStage>{ new ChaosStage{ this } });				// Chaos

		AddStage(shared<WaitStage>{ new WaitStage{ this, 2.0f } });
		AddStage(shared<BossStage>{ new BossStage{ this } });				// Boss

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
		weak<BackgroundLayer> planets = SpawnActor<BackgroundLayer>();
		planets.lock()->SetAssets
		(
			{
				"SpaceShooterRedux/PNG/Planets/Planet1.png",
				"SpaceShooterRedux/PNG/Planets/Planet2.png",
				"SpaceShooterRedux/PNG/Planets/Planet3.png",
				"SpaceShooterRedux/PNG/Planets/Planet4.png",
				"SpaceShooterRedux/PNG/Planets/Planet5.png",
				"SpaceShooterRedux/PNG/Planets/Planet6.png",
				"SpaceShooterRedux/PNG/Planets/Planet7.png"
			}
		);

		planets.lock()->SetSpriteCount(1);
		planets.lock()->SetSizes(1.0f, 1.5f);
		planets.lock()->SetVelocities({ 0.0f, 30.0f }, {0.0f, 80.0f});

		weak<BackgroundLayer> meteors = SpawnActor<BackgroundLayer>();
		meteors.lock()->SetAssets
		(
			{
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big4.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_med1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_med3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_small1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_small2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big4.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_med1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_med2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_small1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_small2.png"
			}
		);

		meteors.lock()->SetSpriteCount(20);
		meteors.lock()->SetSizes(0.2f, 0.5f);
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