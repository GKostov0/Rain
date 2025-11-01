#pragma once

#include "Spaceship/Spaceship.h"

namespace rn
{
	class EnemySpaceship : public Spaceship
	{
	public: 
		EnemySpaceship(World* owner, const std::string& texturePath, float collisionDamage = 200.0f);

		virtual void Tick(float deltaTime) override;

	private:
		virtual void OnActorBeginOverlap(Actor* other) override;

	private:
		float _collisionDamage;
	};
}