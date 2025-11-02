#include "Enemy/TwinBlade.h"
#include "Weapon/BulletShooter.h"

namespace rn
{
	TwinBlade::TwinBlade(World* owner, const std::string& texturePath, const sf::Vector2f velocity)
		: EnemySpaceship{ owner, texturePath },
		_shooterLeft{ new BulletShooter{this, 1.0f, {50.0f, -20.0f}} },
		_shooterRight{ new BulletShooter{this, 1.0f, {50.0f, 20.0f}} }
	{
		SetVelocity(velocity);
		SetActorRotation(90.0f);
	}

	void TwinBlade::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}

	void TwinBlade::Shoot()
	{
		_shooterLeft->Shoot();
		_shooterRight->Shoot();
	}
}