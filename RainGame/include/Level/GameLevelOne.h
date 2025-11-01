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
		weak<PlayerSpaceship> _playerSpaceship;
	};
}