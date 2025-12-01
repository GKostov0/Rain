#pragma once

#include "Spaceship/Spaceship.h"
#include "Player/Reward.h"

namespace rn
{
	class EnemySpaceship : public Spaceship
	{
	public: 
		EnemySpaceship(World* owner, const std::string& texturePath, float collisionDamage = 200.0f, float rewardSpawnWeight = 0.5f,
			const List<RewardFactoryFunc> rewards = 
			{
				CreateHealthReward,
				CreateThreeWayShooterReward,
				CreateFrontalWiperReward,
				CreatLifeReward,
				CreateZigZagRocketReward
			});

		virtual void Tick(float deltaTime) override;

		void SetScoreAwardAmount(unsigned int amount);
		void SetRewardSpawnWeight(float weight);

	private:
		virtual void OnActorBeginOverlap(Actor* other) override;
		virtual void Blew() override;
		void SpawnReward();

	private:
		float _collisionDamage;
		unsigned int _scoreAwardAmount;
		float _rewardSpawnWeight;

		List<RewardFactoryFunc> _rewardFactories;
	};
}