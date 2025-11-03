#pragma once

#include "SpaceShip/Spaceship.h"

namespace rn
{
	class Shooter;

	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* owner, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_blue.png");

		virtual void Tick(float deltaTime) override;

		void SetSpeed(float speed) { _speed = speed; }
		float GetSpeed() const { return _speed; }

		virtual void Shoot() override;

		void SetShooter(unique<Shooter>&& newShooter);

	private:
		void HandleInput();
		void ConsumeInput(float deltaTime);
		void NormalizeInput();
		void ClampInputOnEdge();

	private:
		sf::Vector2f _moveInput;
		float _speed;

		unique<Shooter> _shooter;
	};
}