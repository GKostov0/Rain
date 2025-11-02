#include "Enemy/Hexagon.h"

#include "Weapon/BulletShooter.h"

namespace rn
{
	Hexagon::Hexagon(World* owner, const std::string& texturePath, const sf::Vector2f velocity)
		: EnemySpaceship{ owner, texturePath },
		_shooter1{ new BulletShooter{this, 1.f, sf::Vector2f{20.f, 50.f}, 30.f} },
		_shooter2{ new BulletShooter{this, 1.f, sf::Vector2f{20.f, -50.f}, -30.f} },
		_shooter3{ new BulletShooter{this, 1.f, sf::Vector2f{50.f, 0.0f}} },
		_shooter4{ new BulletShooter{this, 1.f, sf::Vector2f{-50.f, 0.0f}, -180.f} },
		_shooter5{ new BulletShooter{this, 1.f, sf::Vector2f{-20.f, 50.0f}, 120.f} },
		_shooter6{ new BulletShooter{this, 1.f, sf::Vector2f{-20.f, -50.0f},-120.f} }
	{
		SetVelocity(velocity);
		SetActorRotation(90.0f);
	}

	void Hexagon::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);

		Shoot();
	}

	void Hexagon::Shoot()
	{
		_shooter1->Shoot();
		_shooter2->Shoot();
		_shooter3->Shoot();

		_shooter4->Shoot();
		_shooter5->Shoot();
		_shooter6->Shoot();
	}
}