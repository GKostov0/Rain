#pragma once

#include "Enemy/EnemySpaceship.h"

namespace rn
{
	class BulletShooter;

	class UFO : public EnemySpaceship
	{
	public:
		UFO(World* owner, const sf::Vector2f& velocity, 
			const std::string& texturePath = "SpaceShooterRedux/PNG/ufoRed.png",
			float rotationSpeed = 40.0f);

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