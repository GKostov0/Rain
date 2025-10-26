#pragma once

#include "framework/Actor.h"
#include "gameplay/HealthComponent.h"

namespace rn
{
	class SpaceShip : public Actor
	{
	public:
		SpaceShip(World* owner, const std::string& texturePath = "");

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

		void SetVelocity(const sf::Vector2f& velocity);
		sf::Vector2f GetVelocity() const { return _velocity; }

		virtual void Shoot();
		virtual void ApplyDamage(float amount) override;

	private:
		virtual void OnHealthChanged(float amount, float currentHelath, float maxHealth);
		virtual void OnTakenDamage(float amount, float currentHelath, float maxHealth);
		virtual void Blow();

	private:

		sf::Vector2f _velocity;
		HealthComponent _healthComponent;
	};
}