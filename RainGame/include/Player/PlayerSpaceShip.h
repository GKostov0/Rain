#pragma once

#include "SpaceShip/Spaceship.h"
#include "framework/TimerManager.h"

namespace rn
{
	class Shooter;

	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* owner, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_blue.png");

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;
		virtual void ApplyDamage(float amount) override;
		virtual void Shoot() override;

		void SetSpeed(float speed) { _speed = speed; }
		float GetSpeed() const { return _speed; }

		void SetShooter(unique<Shooter>&& newShooter);

	private:
		void HandleInput();
		void ConsumeInput(float deltaTime);
		void NormalizeInput();
		void ClampInputOnEdge();

		void StopInvulnerable();
		void UpdateInvulnerable(float deltaTime);

	private:
		sf::Vector2f _moveInput;
		float _speed;

		float _invulnerableTime;
		float _invulnerableFlashInterval;
		float _invulnerableFlashTimer;
		float _invulnerableFlashDirection; // Ping pong the color for a flashing effect

		bool _isInvulnerable;

		TimerHandle _invulnerableTimer;

		unique<Shooter> _shooter;
	};
}