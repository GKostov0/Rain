#pragma once

#include "Enemy/EnemySpaceship.h"

namespace rn
{
	class BulletShooter;

	class TwinBlade : public EnemySpaceship
	{
	public:
		TwinBlade(World* owner, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlack1.png",
			const sf::Vector2f velocity = { 0.0f, 120.0f });

		virtual void Tick(float deltaTime) override;
		virtual void Shoot() override;

	private:
		unique<BulletShooter> _shooterLeft;
		unique<BulletShooter> _shooterRight;

	};
}