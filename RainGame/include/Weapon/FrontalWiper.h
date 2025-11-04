#pragma once
#include <SFML/Graphics.hpp>

#include "Weapon/BulletShooter.h"
#include "framework/Core.h"

namespace rn
{
	class FrontalWiper : public Shooter
	{
	public:
		FrontalWiper(Actor* owner, float cooldownTime = 0.1f,
						const sf::Vector2f& localOffset = { 0.0f, 0.0f }, float width = 60.0f);

		virtual void IncrementLevel(int amount = 1) override;

	private:
		virtual void ShooterImpl() override;

	private:
		float _width;

		unique<BulletShooter> _shooter1;
		unique<BulletShooter> _shooter2;
		unique<BulletShooter> _shooter3;
		unique<BulletShooter> _shooter4;

		unique<BulletShooter> _shooter5;
		unique<BulletShooter> _shooter6;
	};
}