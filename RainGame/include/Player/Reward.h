#pragma once

#include <functional>

#include "framework/Actor.h"

namespace rn
{
	class PlayerSpaceship;
	class Reward;

	using RewardFunction = std::function<void(PlayerSpaceship*)>;
	using RewardFactoryFunc = std::function<weak<Reward>(World*)>;

	class Reward : public Actor
	{
	public:
		Reward(World* owner, const std::string& texturePath,
				RewardFunction rewardFunction, float speed = 200.0f);

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

	private:
		virtual void OnActorBeginOverlap(Actor* other) override;

	private:
		float _speed;
		RewardFunction _rewardFunction;
	};

	weak<Reward> CreateHealthReward(World* world);
	weak<Reward> CreateThreeWayShooterReward(World* world);
	weak<Reward> CreateFrontalWiperReward(World* world);
	weak<Reward> CreatLifeReward(World* world);

	weak<Reward> CrateReward(World* world, const std::string& texturePath, RewardFunction rewardFunctuion);

	void RewardHealth(PlayerSpaceship* player);
	void RewardThreeWayShooter(PlayerSpaceship* player);
	void RewardFrontalWiper(PlayerSpaceship* player);
	void RewardLife(PlayerSpaceship* player);
}