#pragma once

#include "framework/World.h"
#include "framework/TimerManager.h"

namespace rn
{
	class PlayerSpaceship;

	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owner);

	private:
		virtual void BeginPlay() override;
		virtual void InitGameStages() override;
		void PlayerSpaceshipDestroyed(Actor* destroyedSpaceship);
		void GameOver();

	private:
		weak<PlayerSpaceship> _playerSpaceship;
	};
}