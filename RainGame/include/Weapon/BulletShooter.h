#pragma once
#include <SFML/System.hpp>
#include "Weapon/Shooter.h"

namespace rn
{
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner, float cooldownTime = 1.0f, const sf::Vector2f& localPositionOffset = {0.0f, 0.0f},
			float localRotationOffset = 0.0f, const std::string& bulletTexturePath = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");

		virtual bool IsOnCooldown() const override;
		virtual void ShooterImpl() override;

		void SetBulletTexturePath(const std::string& newTexturePath);

	private:
		sf::Clock _cooldownClock;
		float _cooldownTime;
		sf::Vector2f _localPositionOffset;
		float _localRotationOffset;

		std::string _bulletTextuePath;
	};
}