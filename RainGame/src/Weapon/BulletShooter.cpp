#include "Weapon/BulletShooter.h"
#include "framework/Core.h"

namespace rn
{
	BulletShooter::BulletShooter(Actor* owner, float cooldownTime)
		: Shooter{ owner }, _cooldownClock{}, _cooldownTime{ cooldownTime }
	{

	}

	bool BulletShooter::IsOnCooldown() const
	{
		if (_cooldownClock.getElapsedTime().asSeconds() > _cooldownTime)
		{
			return false;
		}
		
		return true;
	}

	void BulletShooter::ShooterImpl()
	{
		_cooldownClock.restart();
		LOG("Pew Pew!");
	}
}