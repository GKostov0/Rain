#include "Weapon/BulletShooter.h"
#include "framework/Core.h"
#include "Weapon/Bullet.h"
#include "framework/World.h"

namespace rn
{
	BulletShooter::BulletShooter(Actor* owner, float cooldownTime,
		const sf::Vector2f& localPositionOffset, float localRotationOffset, const std::string& bulletTexturePath)
		: Shooter{ owner },
		_cooldownClock{},
		_cooldownTime{ cooldownTime },
		_localPositionOffset{ localPositionOffset },
		_localRotationOffset{ localRotationOffset },
		_bulletTextuePath{ bulletTexturePath }
	{

	}

	bool BulletShooter::IsOnCooldown() const
	{
		if (_cooldownClock.getElapsedTime().asSeconds() > _cooldownTime / GetCurrentLevel())
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
		weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), _bulletTextuePath);
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForward * _localPositionOffset.x + ownerRight * _localPositionOffset.y);
		newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() + _localRotationOffset);
	}

	void BulletShooter::SetBulletTexturePath(const std::string& newTexturePath)
	{
		_bulletTextuePath = newTexturePath;
	}

	void BulletShooter::IncrementLevel(int amount)
	{
		Shooter::IncrementLevel(amount);
	}
}