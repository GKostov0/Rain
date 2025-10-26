#include "SpaceShip/SpaceShip.h"

namespace rn
{
	SpaceShip::SpaceShip(World* owner, const std::string& texturePath)
		: Actor{ owner, texturePath }, _velocity{}, _healthComponent{100.0f, 100.0f}
	{

	}

	void SpaceShip::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		AddActorLocationOffset(_velocity * deltaTime);
	}

	void SpaceShip::SetVelocity(const sf::Vector2f& velocity)
	{
		_velocity = velocity;
	}

	void SpaceShip::Shoot()
	{

	}

	void SpaceShip::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);

		_healthComponent.onHealthChanged.BindAction(GetWeakReference(), &SpaceShip::OnHealthChanged);
		_healthComponent.onTakenDamage.BindAction(GetWeakReference(), &SpaceShip::OnTakenDamage);
		_healthComponent.onHealthEmpty.BindAction(GetWeakReference(), &SpaceShip::Blow);
	}

	void SpaceShip::ApplyDamage(float amount)
	{
		_healthComponent.ChangeHealth(-amount);
	}

	void SpaceShip::OnHealthChanged(float amount, float currentHelath, float maxHealth)
	{
		
	}

	void SpaceShip::OnTakenDamage(float amount, float currentHelath, float maxHealth)
	{
	}

	void SpaceShip::Blow()
	{
		Destroy();
	}
}