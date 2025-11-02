#include "Enemy/UFO.h"
#include "Weapon/BulletShooter.h"

namespace rn
{
	UFO::UFO(World* owner, const sf::Vector2f& velocity, 
				const std::string& texturePath, float rotationSpeed)
		: EnemySpaceship{owner, texturePath},
		_shooter1{ new BulletShooter{this, 0.5f, sf::Vector2f{0.0f, 0.0f}, -60.0f} },
		_shooter2{ new BulletShooter{this, 0.5f, sf::Vector2f{0.0f, 0.0f},  60.0f} },
		_shooter3{ new BulletShooter{this, 0.5f, sf::Vector2f{0.0f, 0.0f}, 180.0f} },
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