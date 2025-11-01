#pragma once

#include "Enemy/EnemySpaceship.h"

namespace rn
{
	class BulletShooter;

	class Vanguard : public EnemySpaceship
	{
	public:
		Vanguard(World* owner, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlue3.png",
					const sf::Vector2f velocity = {0.0f, 50.0f});
		
		virtual void Tick(float deltaTime) override;

	private:
		virtual void Shoot() override;

	private:
		unique<BulletShooter> _shooter;
	};
}