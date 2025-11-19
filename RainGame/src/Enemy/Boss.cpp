#include "Enemy/Boss.h"

#include "gameplay/HealthComponent.h"

namespace rn
{
	Boss::Boss(World* owner)
		: EnemySpaceship{ owner, "SpaceShooterRedux/PNG/Enemies/boss.png" },
		_speed{ 100.0f },
		_switchDistanceToEdge{ 100.0f },
		_currentStage{1},
		_baseShooterLeft{ this, 0.8f, {50, -50.0f} },
		_baseShooterRight{ this, 0.8f, {50, 50.0f} },
		_finalStageShooterLeft{ this, 0.3f, {50.0f, -150.0f} },
		_finalStageShooterRight{ this, 0.3f, {50.0f, 150.0f} },
		_threeWayShooter{ this, 0.4f, {100.0f, 0.0f} },
		_frontalWiperLeft{ this, 0.5f, {80.0f, -100.0f} },
		_frontalWiperRight{ this, 0.5f, {80.0f, 100.0f} }
	{
		SetActorRotation(90.0f);
		SetVelocity({ _speed, 0.0f });
		SetRewardSpawnWeight(0.0f);
	}

	void Boss::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		ShootBaseShooters();
		ShootFrontalWipers();
		ShootThreeWayShooter();

		if (_currentStage > 3)
		{
			_finalStageShooterLeft.Shoot();
			_finalStageShooterRight.Shoot();
		}

		CheckMove();
	}

	void Boss::BeginPlay()
	{
		EnemySpaceship::BeginPlay();

		HealthComponent& healthComponent = GetHealthComponent();
		healthComponent.SetInitialHealth(3000.0f, 3000.0f);
		healthComponent.onHealthChanged.BindAction(GetWeakReference(), &Boss::HealthChanged);
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

	void Boss::ShootThreeWayShooter()
	{
		_threeWayShooter.Shoot();
	}

	void Boss::ShootFrontalWipers()
	{
		_frontalWiperLeft.Shoot();
		_frontalWiperRight.Shoot();
	}

	void Boss::HealthChanged(float amount, float currentHealth, float maxHealth)
	{
		float percentLeft = currentHealth / maxHealth;

		if (percentLeft < 0.7f && percentLeft > 0.5f)
		{
			SetStage(2);
		}
		if (percentLeft < 0.5f && percentLeft > 0.3f)
		{
			SetStage(3);
		}
		if (percentLeft < 0.3f)
		{
			SetStage(4);
		}
	}

	void Boss::SetStage(int newStage)
	{
		_currentStage = newStage;

		_baseShooterLeft.SetCurrentLevel(newStage);
		_baseShooterRight.SetCurrentLevel(newStage);

		_frontalWiperLeft.SetCurrentLevel(newStage);
		_frontalWiperRight.SetCurrentLevel(newStage);

		_threeWayShooter.SetCurrentLevel(newStage);
	}
}