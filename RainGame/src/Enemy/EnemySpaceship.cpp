#include "Enemy/EnemySpaceship.h"
#include "framework/MathUtility.h"
#include "Player/PlayerManager.h"

namespace rn
{
	EnemySpaceship::EnemySpaceship(World* owner, const std::string& texturePath,
									float collisionDamage, const List<RewardFactoryFunc> rewards)
		: Spaceship{ owner, texturePath },
		_collisionDamage{ collisionDamage },
		_rewardFactories{ rewards },
		_scoreAwardAmount{10}
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

	void EnemySpaceship::SetScoreAwardAmount(unsigned int amount)
	{
		_scoreAwardAmount = amount;
	}

	void EnemySpaceship::OnActorBeginOverlap(Actor* other)
	{
		Spaceship::OnActorBeginOverlap(other);

		if (IsOtherHostile(other))
		{
			other->ApplyDamage(_collisionDamage);
		}
	}

	void EnemySpaceship::Blew()
	{
		SpawnReward();
		Player* player = PlayerManager::Get().GetPlayer();
		if (player)
		{
			player->AddScore(_scoreAwardAmount);
		}
	}

	void EnemySpaceship::SpawnReward()
	{
		if (_rewardFactories.size() == 0) return;

		int result = (int)RandomRange(0, _rewardFactories.size());
		if (result >= 0 && result < _rewardFactories.size())
		{
			weak<Reward> reward = _rewardFactories[result](GetWorld());
			reward.lock()->SetActorLocation(GetActorLocation());
		}
	}
}