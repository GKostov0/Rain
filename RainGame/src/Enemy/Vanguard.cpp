#include "Enemy/Vanguard.h"
#include "Weapon/BulletShooter.h"

namespace rn
{
	Vanguard::Vanguard(World* owner, const std::string& texturePath, const sf::Vector2f velocity)
		: EnemySpaceship{ owner, texturePath }, _shooter{ new BulletShooter{this, 1.0f, {50.0f, 0.0f}} }
	{
		SetVelocity(velocity);
		SetActorRotation(90.0f);
	}

	void Vanguard::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);

		Shoot();
	}

	void Vanguard::Shoot()
	{
		_shooter->Shoot();
	}
}