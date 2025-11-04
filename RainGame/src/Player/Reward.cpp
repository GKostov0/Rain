#include "Player/Reward.h"
#include "framework/World.h"
#include "Player/PlayerSpaceship.h"

#include "Weapon/ThreeWayShooter.h"
#include "Weapon/FrontalWiper.h"

namespace rn
{
	Reward::Reward(World* owner, const std::string& texturePath, RewardFunction rewardFunction, float speed)
		: Actor{owner, texturePath },
		_speed{speed},
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
		PlayerSpaceship* player = dynamic_cast<PlayerSpaceship*>(other);
		if (player != nullptr && !player->IsPendingDestroy())
		{
			_rewardFunction(player);
			Destroy();
		}
	}

	weak<Reward> CreateHealthReward(World* world)
	{
		return CrateReward(world, "SpaceShooterRedux/PNG/pickups/pill_green.png", RewardHealth);
	}

	weak<Reward> CreateThreeWayShooterReward(World* world)
	{
		return CrateReward(world, "SpaceShooterRedux/PNG/pickups/three_shooter_pickup.png", RewardThreeWayShooter);
	}

	weak<Reward> CreateFrontalWiperReward(World* world)
	{
		return CrateReward(world, "SpaceShooterRedux/PNG/pickups/front_row_shooter_pickup.png", RewardFrontalWiper);
	}

	weak<Reward> CrateReward(World* world, const std::string& texturePath, RewardFunction rewardFunctuion)
	{
		weak<Reward> reward = world->SpawnActor<Reward>(texturePath, rewardFunctuion);
		return reward;
	}

	void RewardHealth(PlayerSpaceship* player)
	{
		static float rewardAmount = 10.0f;

		if (player && !player->IsPendingDestroy())
		{
			player->GetHealthComponent().ChangeHealth(rewardAmount);
		}
	}

	void RewardThreeWayShooter(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->SetShooter(unique<Shooter>{new ThreeWayShooter{player, 0.15f, {50.0f, 0.0f} }});
		}
	}

	void RewardFrontalWiper(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->SetShooter(unique<Shooter>{new FrontalWiper{ player, 0.15f, {50.0f, 0.0f} }});
		}
	}
}