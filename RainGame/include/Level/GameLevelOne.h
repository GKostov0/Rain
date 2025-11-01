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
		void TimerCallbackTest();

	private:
		weak<PlayerSpaceship> _playerSpaceship;

		TimerHandle _timerHandle_test;
	};
}