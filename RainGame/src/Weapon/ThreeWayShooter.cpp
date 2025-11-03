#include "Weapon/ThreeWayShooter.h"

namespace rn
{
	ThreeWayShooter::ThreeWayShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset)
		: Shooter{owner},
		_shooterLeft{ new BulletShooter{ owner, cooldownTime, localOffset, -12.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		_shooterMiddle{ new BulletShooter{ owner, cooldownTime, localOffset} },
		_shooterRight{ new BulletShooter{ owner, cooldownTime, localOffset, 12.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} }
	{
		
	}

	void ThreeWayShooter::ShooterImpl()
	{
		_shooterLeft->Shoot();
		_shooterMiddle->Shoot();
		_shooterRight->Shoot();
	}
}