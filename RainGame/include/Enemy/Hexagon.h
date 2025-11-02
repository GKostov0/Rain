#pragma once

#include "Enemy/EnemySpaceship.h"

namespace rn
{
	class BulletShooter;

	class Hexagon : public EnemySpaceship
	{
	public:
		Hexagon(World* owner, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyGreen4.png",
			const sf::Vector2f velocity = { 0.0f, 100.0f });

		virtual void Tick(float deltaTime) override;
	
	private:
		virtual void Shoot() override;

	private:
		unique<BulletShooter> _shooter1;
		unique<BulletShooter> _shooter2;
		unique<BulletShooter> _shooter3;

		unique<BulletShooter> _shooter4;
		unique<BulletShooter> _shooter5;
		unique<BulletShooter> _shooter6;

	};
}