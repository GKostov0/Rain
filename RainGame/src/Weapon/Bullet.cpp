#include "Weapon/Bullet.h"

namespace rn
{
	Bullet::Bullet(World* world, Actor* owner, const std::string& texturePath, float speed, float damage)
		: Actor{ world, texturePath }, _owner{ owner }, 
			_speed{ speed }, _damage{damage}
	{

	}

	void Bullet::SetSpeed(float speed)
	{
		_speed = speed;
	}

	void Bullet::SetDamage(float damage)
	{
		_damage = damage;
	}

	void Bullet::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		Move(deltaTime);
		if (IsActorOutOfBounds())
		{
			Destroy();
		}
	}

	void Bullet::Move(float deltaTime)
	{
		AddActorLocationOffset(GetActorForwardDirection() * _speed * deltaTime);
	}
}