#pragma once

namespace rn
{
	class HealthComponent
	{
	public:
		HealthComponent(float currentHealt, float maxHealth);

		void ChangeHealth(float amount);
		float GetCurrentHealth() const { return _currentHealth; }
		float GetMaxHealth() const { return _maxHealth; }

	private:
		void TakenDamage(float amount);
		void HealthEmpty();
		void HealthRegen(float amount);

	private:
		float _currentHealth;
		float _maxHealth;
	};
}