#include "Weapon/BulletShooter.h"
#include "framework/Core.h"
#include "Weapon/Bullet.h"
#include "framework/World.h"

namespace rn
{
	BulletShooter::BulletShooter(Actor* owner, float cooldownTime,
		const sf::Vector2f& localPositionOffset, float localRotationOffset)
		: Shooter{ owner }, _cooldownClock{}, _cooldownTime{ cooldownTime },
			_localPositionOffset{ localPositionOffset }, _localRotationOffset{ localRotationOffset }
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
		sf::Vector2f ownerForward = GetOwner()->GetActorForwardDirection();
		sf::Vector2f ownerRight = GetOwner()->GetActorRightDirection();

		_cooldownClock.restart();
		weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForward * _localPositionOffset.x + ownerRight * _localPositionOffset.y);
		newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() + _localRotationOffset);
	}
}