#pragma once

#include <functional>

#include "framework/Actor.h"

namespace rn
{
	class PlayerSpaceship;
	using RewardFunction = std::function<void(PlayerSpaceship*)>;

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
}