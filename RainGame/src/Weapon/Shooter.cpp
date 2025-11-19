#include "Weapon/Shooter.h"

namespace rn
{
	Shooter::Shooter(Actor* owner)
		: _owner{ owner },
		_currentLevel{ 1 },
		_maxLevel{ 4 }
	{

	}

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

	void Shooter::SetCurrentLevel(int level)
	{
		_currentLevel = level;
	}
}