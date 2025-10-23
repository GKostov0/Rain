#pragma once
#include <SFML/System.hpp>
#include "Weapon/Shooter.h"

namespace rn
{
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner, float cooldownTime = 1.0f);

		virtual bool IsOnCooldown() const override;
		virtual void ShooterImpl() override;

	private:
		sf::Clock _cooldownClock;
		float _cooldownTime;
	};
}