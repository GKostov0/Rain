#include "Weapon/BulletShooter.h"
#include "framework/Core.h"
#include "Weapon/Bullet.h"
#include "framework/World.h"

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
		weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation());
		newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation());
	}
}