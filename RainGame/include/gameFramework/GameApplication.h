#pragma once
#include<framework/Application.h>
#include<framework/Core.h>

namespace rn
{
	class Actor;
	class PlayerSpaceShip;

	class GameApplication : public Application
	{
	public:
		GameApplication();

		virtual void Tick(float deltaTime) override;

	private:
		float _counter;
		weak<PlayerSpaceShip> _playerSpaceship;
	};
}