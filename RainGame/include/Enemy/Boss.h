#pragma once 
#include "Enemy/EnemySpaceship.h"

#include "Weapon/BulletShooter.h"
#include "Weapon/ThreeWayShooter.h"
#include "Weapon/FrontalWiper.h"

namespace rn
{
	class Boss : public EnemySpaceship
	{
	public:
		Boss(World* owner);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;

	private:
		void CheckMove();

		void ShootBaseShooters();
		void ShootThreeWayShooter();
		void ShootFrontalWipers();

		void HealthChanged(float amount, float currentHealth, float maxHealth);

		void SetStage(int newStage);

	private:
		float _speed;
		float _switchDistanceToEdge;

		int _currentStage;

		BulletShooter _baseShooterLeft;
		BulletShooter _baseShooterRight;
		BulletShooter _finalStageShooterLeft;
		BulletShooter _finalStageShooterRight;

		ThreeWayShooter _threeWayShooter;

		FrontalWiper _frontalWiperLeft;
		FrontalWiper _frontalWiperRight;
	};
}