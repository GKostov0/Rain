#include "Enemy/UFO.h"
#include "Weapon/BulletShooter.h"

namespace rn
{
	UFO::UFO(World* owner, const std::string& texturePath,
			const sf::Vector2f& velocity, float rotationSpeed)
		: EnemySpaceship{owner, texturePath},
		_shooter1{ new BulletShooter{this, 1.0f, sf::Vector2f{0.0f, 0.0f}, -60.0f} },
		_shooter2{ new BulletShooter{this, 1.0f, sf::Vector2f{0.0f, 0.0f},  60.0f} },
		_shooter3{ new BulletShooter{this, 1.0f, sf::Vector2f{0.0f, 0.0f}, 180.0f} },
		_rotationSpeed{ rotationSpeed }
	{
		SetVelocity(velocity);
		SetActorRotation(90.0f);
	}

	void UFO::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
		AddActorRotationOffset(_rotationSpeed * deltaTime);
	}

	void UFO::Shoot()
	{
		_shooter1->Shoot();
		_shooter2->Shoot();
		_shooter3->Shoot();
	}
}