#pragma once

#include "Enemy/EnemySpaceship.h"

namespace rn
{
	class BulletShooter;

	class UFO : EnemySpaceship
	{
	public:
		UFO(World* owner, const std::string& texturePath = "SpaceShooterRedux/PNG/ufoRed.png",
			const sf::Vector2f& velocity = {0.0f, 100.0f}, float rotationSpeed = 40.0f);

		virtual void Tick(float deltaTime) override;

	private:
		virtual void Shoot() override;

	private:
		unique<BulletShooter> _shooter1;
		unique<BulletShooter> _shooter2;
		unique<BulletShooter> _shooter3;

		float _rotationSpeed;
	};
}