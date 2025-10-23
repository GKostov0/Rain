#include "Weapon/Shooter.h"

namespace rn
{
	void Shooter::Shoot()
	{
		if (CanShoot() && !IsOnCooldown())
		{
			ShooterImpl();
		}
	}

	Shooter::Shooter(Actor* owner)
		: _owner{owner}
	{

	}
}