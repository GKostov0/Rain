#pragma once

#include "SpaceShip/SpaceShip.h"

namespace rn
{
	class PlayerSpaceShip : public SpaceShip
	{
	public:
		PlayerSpaceShip(World* owner, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_blue.png");

		virtual void Tick(float deltaTime) override;

		void SetSpeed(float speed) { _speed = speed; }
		float GetSpeed() const { return _speed; }

	private:
		void HandleInput();
		void ConsumeInput(float deltaTime);
		sf::Vector2f _moveInput;
		float _speed;
	};
}