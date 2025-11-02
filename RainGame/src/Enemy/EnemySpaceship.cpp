#include "Enemy/EnemySpaceship.h"

namespace rn
{
	EnemySpaceship::EnemySpaceship(World* owner, const std::string& texturePath, float collisionDamage)
		: Spaceship{ owner, texturePath },
		_collisionDamage{ collisionDamage }
	{
		SetTeamID(2);
	}

	void EnemySpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);

		if (IsActorOutOfBounds(GetActorGlobalBounds().width * 2.0f))
		{
			Destroy();
		}
	}

	void EnemySpaceship::OnActorBeginOverlap(Actor* other)
	{
		Spaceship::OnActorBeginOverlap(other);

		if (IsOtherHostile(other))
		{
			other->ApplyDamage(_collisionDamage);
		}
	}
}