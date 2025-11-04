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

	void Shooter::IncrementLevel(int amount)
	{
		_currentLevel = _currentLevel >= _maxLevel ? _maxLevel : ++_currentLevel;
	}

	Shooter::Shooter(Actor* owner)
		: _owner{owner},
		_currentLevel{1},
		_maxLevel{4}
	{

	}
}