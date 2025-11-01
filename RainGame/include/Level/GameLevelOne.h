#pragma once

#include "framework/World.h"

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

		unsigned int _timerIndex_test;
	};
}