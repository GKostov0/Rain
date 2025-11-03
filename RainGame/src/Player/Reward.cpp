#include "Player/Reward.h"
#include "Player/PlayerSpaceship.h"

namespace rn
{
	Reward::Reward(World* owner, const std::string& texturePath, RewardFunction rewardFunction, float speed)
		: Actor{owner, texturePath },
		_rewardFunction{ rewardFunction }
	{

	}

	void Reward::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}

	void Reward::Tick(float deltaTime)
	{
		AddActorLocationOffset({0.0f, _speed * deltaTime});
	}

	void Reward::OnActorBeginOverlap(Actor* other)
	{
		PlayerSpaceship* player = static_cast<PlayerSpaceship*>(other);
		if (player != nullptr && !player->IsPendingDestroy())
		{
			_rewardFunction(player);
		}
	}
}