#include "Enemy/Boss.h"

#include "gameplay/HealthComponent.h"

namespace rn
{
	Boss::Boss(World* owner)
		: EnemySpaceship{ owner, "SpaceShooterRedux/PNG/Enemies/boss.png" },
		_speed{ 100.0f },
		_switchDistanceToEdge{ 100.0f },
		_baseShooterLeft{ this, 0.8f, {50, -50.0f} },
		_baseShooterRight{ this, 0.8f, {50, 50.0f} }
	{
		SetActorRotation(90.0f);
		SetVelocity({ _speed, 0.0f });
		SetRewardSpawnWeight(0.0f);

		HealthComponent& healthComponent = GetHealthComponent();
		healthComponent.SetInitialHealth(3000.0f, 3000.0f);
	}

	void Boss::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		ShootBaseShooters();
		CheckMove();
	}

	void Boss::CheckMove()
	{
		if (GetActorLocation().x > GetWindowSize().x - _switchDistanceToEdge)
		{
			SetVelocity({ -_speed, 0.0f });
		}
		else if (GetActorLocation().x < _switchDistanceToEdge)
		{
			SetVelocity({ _speed, 0.0f });
		}
	}

	void Boss::ShootBaseShooters()
	{
		_baseShooterLeft.Shoot();
		_baseShooterRight.Shoot();
	}
}