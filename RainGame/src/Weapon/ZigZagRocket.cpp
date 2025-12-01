#include "Weapon/ZigZagRocket.h"

namespace rn
{
	ZigZagRocket::ZigZagRocket(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset)
		: Shooter{owner},
		_shooter{ new BulletShooter{ owner, cooldownTime, localOffset, 0.0f, "SpaceShooterRedux/PNG/Lasers/bulletRed01.png"} }

	{
		_shooter->SetZigZag(true);
	}

	void ZigZagRocket::IncrementLevel(int amount)
	{
		Shooter::IncrementLevel(amount);
		_shooter->IncrementLevel(amount);
	}

	void ZigZagRocket::SetCurrentLevel(int level)
	{
		Shooter::SetCurrentLevel(level);
		_shooter->SetCurrentLevel(level);
	}

	void ZigZagRocket::ShooterImpl()
	{
		_shooter->Shoot();
	}
}