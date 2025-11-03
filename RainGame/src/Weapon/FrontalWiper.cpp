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
		_shooter4{ new BulletShooter{ owner, cooldownTime, {localOffset.x, localOffset.y + width / 2.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"} }
	{

	}

	void FrontalWiper::ShooterImpl()
	{
		_shooter1->Shoot();
		_shooter2->Shoot();
		_shooter3->Shoot();
		_shooter4->Shoot();
	}
}