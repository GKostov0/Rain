#include "Player/Player.h"
#include "framework/World.h"
#include "Player/PlayerSpaceship.h"

namespace rn
{
	Player::Player()
		: _lifeCount{ 3 },
		_score{ 0 },
		_currentPlayerSpaceship{}
	{
	}

	weak<PlayerSpaceship> Player::SpawnSpaceship(World* owner)
	{
		if (_lifeCount > 0)
		{
			--_lifeCount;

			auto windowSize = owner->GetWindowSize();

			_currentPlayerSpaceship = owner->SpawnActor<PlayerSpaceship>();
			_currentPlayerSpaceship.lock()->SetActorLocation({ windowSize.x / 2.0f, windowSize.y - 100.0f });
			_currentPlayerSpaceship.lock()->SetActorRotation(-90.0f);

			onLifeChange.Broadcast(_lifeCount);
		}
		else
		{
			onLifeExhausted.Broadcast();
		}
	}

	void Player::AddLifeCount(unsigned int count)
	{
		if (count > 0)
		{
			_lifeCount += count;
			onLifeChange.Broadcast(_lifeCount);
		}
	}

	int Player::AddScore(unsigned int amount)
	{
		if (amount > 0)
		{
			_score += amount;
			onScoreChange.Broadcast(_score);
		}
	}
}