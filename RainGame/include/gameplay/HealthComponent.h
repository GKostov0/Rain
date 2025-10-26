#pragma once

#include "framework/Delegate.h"

namespace rn
{
	class HealthComponent
	{
	public:
		HealthComponent(float currentHealt, float maxHealth);

		void ChangeHealth(float amount);
		float GetCurrentHealth() const { return _currentHealth; }
		float GetMaxHealth() const { return _maxHealth; }

		Delegate<float, float, float> onHealthChanged;
		Delegate<float, float, float> onTakenDamage;
		Delegate<> onHealthEmpty;

	private:
		void TakenDamage(float amount);
		void HealthEmpty();
		void HealthRegen(float amount);

	private:
		float _currentHealth;
		float _maxHealth;
	};
}