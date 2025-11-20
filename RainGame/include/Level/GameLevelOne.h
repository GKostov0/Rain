#pragma once

#include "framework/World.h"
#include "framework/TimerManager.h"

namespace rn
{
	class PlayerSpaceship;
	class GameplayHUD;

	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owner);

	private:
		virtual void BeginPlay() override;
		virtual void InitGameStages() override;
		virtual void AllGameStageFinished() override;

		void PlayerSpaceshipDestroyed(Actor* destroyedSpaceship);

		void SpawnCosmetics();

		void RestartGame();
		void GameOver();
		void QuitGame();

	private:
		weak<PlayerSpaceship> _playerSpaceship;
		weak<GameplayHUD> _gameplayHUD;
	};
}