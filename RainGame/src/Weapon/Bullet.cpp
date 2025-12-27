#include "Weapon/Bullet.h"

#include "framework/MathUtility.h"

namespace rn
{
	Bullet::Bullet(World* world, Actor* owner, const std::string& texturePath, float speed, float damage)
		: Actor{ world, texturePath },
		_owner{ owner }, 
		_speed{ speed },
		_damage{ damage },
		_isZigZag{ false },
		_zigZagOffset{0},
		_isZigZagLeft{RandomRange(0, 1) > 0.5f ? true : false}
	{
		SetTeamID(owner->GetTeamID());
	}

	void Bullet::SetSpeed(float speed)
	{
		_speed = speed;
	}

	void Bullet::SetDamage(float damage)
	{
		_damage = damage;
	}

	void Bullet::SetZigZag(bool isZigZag)
	{
		_isZigZag = isZigZag;
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

	void Bullet::OnActorBeginOverlap(Actor* other)
	{
		if (IsOtherHostile(other))
		{
			other->ApplyDamage(GetDamage());
			Destroy();
		}
	}

	void Bullet::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}

	void Bullet::Move(float deltaTime)
	{
		AddActorLocationOffset(GetActorForwardDirection() * _speed * deltaTime);
		
		if (_isZigZag)
		{
			if (++_zigZagOffset > 10)
			{
				_zigZagOffset = 0;
				_isZigZagLeft = !_isZigZagLeft;
			}

			SetActorRotation(_isZigZagLeft ? 225 : 315);
		}
	}
}