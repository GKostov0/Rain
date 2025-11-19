#pragma once
#include <SFML/Graphics.hpp>

#include "Weapon/BulletShooter.h"
#include "framework/Core.h"

namespace rn
{
	class ThreeWayShooter : public Shooter
	{
	public:
		ThreeWayShooter(Actor* owner, float cooldownTime = 0.6f,
			const sf::Vector2f& localOffset = {0.0f, 0.0f});

		virtual void IncrementLevel(int amount = 1) override;
		virtual void SetCurrentLevel(int level) override;

	private:
		virtual void ShooterImpl() override;

	private:
		unique<BulletShooter> _shooterLeft;
		unique<BulletShooter> _shooterMiddle;
		unique<BulletShooter> _shooterRight;

		unique<BulletShooter> _shooterLeftTopLevel;
		unique<BulletShooter> _shooterRightTopLevel;
	};
}