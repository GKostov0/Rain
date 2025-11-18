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

	private:
		void CheckMove();
		void ShootBaseShooters();

	private:
		float _speed;
		float _switchDistanceToEdge;

		BulletShooter _baseShooterLeft;
		BulletShooter _baseShooterRight;
	};
}