#pragma once

#include "framework/Object.h"
#include "framework/Delegate.h"

namespace rn
{
	class PlayerSpaceship;
	class World;

	class Player : public Object
	{
	public:
		Player();

		weak<PlayerSpaceship> SpawnSpaceship(World* owner);
		const weak<PlayerSpaceship> GetCurrentSpaceship() const { return _currentPlayerSpaceship; }

		void AddLifeCount(unsigned int count);
		int GetLifeCount() const { return _lifeCount; }
		int AddScore(unsigned int amount);
		int GetScore() const { return _score; }

		Delegate<int> onLifeChange;
		Delegate<int> onScoreChange;
		Delegate<> onLifeExhausted;

	private:
		unsigned int _lifeCount;
		unsigned int _score;

		weak<PlayerSpaceship> _currentPlayerSpaceship;
	};
}