#include "Weapon/FrontalWiper.h"

namespace rn
{
	FrontalWiper::FrontalWiper(Actor* owner, float cooldownTime,
								const sf::Vector2f& localOffset, float width)
		: Shooter{ owner },
		_width{width},
		_shooter1{ new BulletShooter{ owner, cooldownTime, {localOffset.x, localOffset.y  - width / 2.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"} },
		_shooter2{ new BulletShooter{ owner, cooldownTime, {localOffset.x, localOffset.y - width / 6.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		_shooter3{ new BulletShooter{ owner, cooldownTime, {localOffset.x, localOffset.y + width / 6.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		_shooter4{ new BulletShooter{ owner, cooldownTime, {localOffset.x, localOffset.y + width / 2.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"} },
		_shooter5{ new BulletShooter{ owner, 0.1f, {localOffset.x, localOffset.y + width / 1.5f}, 2.0f, "SpaceShooterRedux/PNG/Lasers/laserBlue01.png"} },
		_shooter6{ new BulletShooter{ owner, 0.1f, {localOffset.x, localOffset.y - width / 1.5f}, -2.0f, "SpaceShooterRedux/PNG/Lasers/laserBlue01.png"} }
	{

	}

	void FrontalWiper::IncrementLevel(int amount)
	{
		Shooter::IncrementLevel(amount);

		_shooter1->IncrementLevel(amount);
		_shooter2->IncrementLevel(amount);
		_shooter3->IncrementLevel(amount);
		_shooter4->IncrementLevel(amount);

		_shooter5->IncrementLevel(amount);
		_shooter6->IncrementLevel(amount);
	}

	void FrontalWiper::SetCurrentLevel(int level)
	{
		Shooter::SetCurrentLevel(level);

		_shooter1->SetCurrentLevel(level);
		_shooter2->SetCurrentLevel(level);
		_shooter3->SetCurrentLevel(level);
		_shooter4->SetCurrentLevel(level);
	}

	void FrontalWiper::ShooterImpl()
	{
		_shooter1->Shoot();
		_shooter2->Shoot();
		_shooter3->Shoot();
		_shooter4->Shoot();

		if (GetCurrentLevel() >= GetMaxLevel())
		{
			_shooter5->Shoot();
			_shooter6->Shoot();
		}
	}
}