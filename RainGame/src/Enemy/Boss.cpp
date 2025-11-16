#include "Enemy/Boss.h"

namespace rn
{
	Boss::Boss(World* owner)
		: EnemySpaceship{owner, "SpaceShooterRedux/PNG/Enemies/boss.png"},
		_speed{100.0f},
		_switchDirection{100.0f}
	{
		SetActorRotation(90.0f);
	}

	void Boss::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
	}
}