#pragma once

#include "Spaceship/Spaceship.h"
#include "Player/Reward.h"

namespace rn
{
	class EnemySpaceship : public Spaceship
	{
	public: 
		EnemySpaceship(World* owner, const std::string& texturePath, float collisionDamage = 200.0f,
			const List<RewardFactoryFunc> rewards = 
			{
				CreateHealthReward,
				CreateThreeWayShooterReward,
				CreateFrontalWiperReward
			});

		virtual void Tick(float deltaTime) override;

	private:
		virtual void OnActorBeginOverlap(Actor* other) override;
		virtual void Blew() override;
		void SpawnReward();

	private:
		float _collisionDamage;

		List<RewardFactoryFunc> _rewardFactories;
	};
}