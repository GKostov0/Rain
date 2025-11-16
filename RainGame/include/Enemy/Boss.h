#pragma once 

#include "Enemy/EnemySpaceship.h"

namespace rn
{
	class Boss : public EnemySpaceship
	{
	public:
		Boss(World* owner);

		virtual void Tick(float deltaTime) override;

	private:
		float _speed;
		float _switchDirection;
	};
}