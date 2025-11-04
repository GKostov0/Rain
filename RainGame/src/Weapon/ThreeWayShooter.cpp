#include "Weapon/ThreeWayShooter.h"

namespace rn
{
	ThreeWayShooter::ThreeWayShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset)
		: Shooter{owner},
		_shooterLeft{ new BulletShooter{ owner, cooldownTime, localOffset, -12.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		_shooterMiddle{ new BulletShooter{ owner, cooldownTime, localOffset} },
		_shooterRight{ new BulletShooter{ owner, cooldownTime, localOffset, 12.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		_shooterLeftTopLevel{ new BulletShooter{ owner, cooldownTime, localOffset, -7.0f, "SpaceShooterRedux/PNG/Lasers/laserBlue01.png"} },
		_shooterRightTopLevel{ new BulletShooter{ owner, cooldownTime, localOffset, 7.0f, "SpaceShooterRedux/PNG/Lasers/laserBlue01.png"} }
	{
		
	}

	void ThreeWayShooter::IncrementLevel(int amount)
	{
		Shooter::IncrementLevel(amount);

		_shooterLeft->IncrementLevel(amount);
		_shooterMiddle->IncrementLevel(amount);
		_shooterRight->IncrementLevel(amount);

		_shooterLeftTopLevel->IncrementLevel(amount);
		_shooterRightTopLevel->IncrementLevel(amount);
	}

	void ThreeWayShooter::ShooterImpl()
	{
		_shooterLeft->Shoot();
		_shooterMiddle->Shoot();
		_shooterRight->Shoot();

		if (GetCurrentLevel() >= GetMaxLevel())
		{
			_shooterLeftTopLevel->Shoot();
			_shooterRightTopLevel->Shoot();
		}
	}
}