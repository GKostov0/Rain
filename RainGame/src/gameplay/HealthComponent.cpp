#include "gameplay/HealthComponent.h"

#include "framework/Core.h"

namespace rn
{
	HealthComponent::HealthComponent(float currentHealt, float maxHealth)
		: _currentHealth{ currentHealt }, _maxHealth{maxHealth}
	{

	}

	void HealthComponent::ChangeHealth(float amount)
	{
		if (amount == 0) return;
		if (_currentHealth == 0) return;

		_currentHealth += amount;

		if (_currentHealth < 0)
			_currentHealth = 0;

		if (_currentHealth > _maxHealth)
			_currentHealth = _maxHealth;

		if (amount < 0)
		{
			TakenDamage(-amount);

			if (_currentHealth <= 0)
			{

			}
		}
		else
		{

		}
	}

	void HealthComponent::TakenDamage(float amount)
	{
		LOG("Damage taken: %f, current hp: %f/%f", amount, _currentHealth, _maxHealth);
	}

	void HealthComponent::HealthEmpty()
	{
		LOG("Health Empty: %f/%f", _currentHealth, _maxHealth);
	}

	void HealthComponent::HealthRegen(float amount)
	{
		LOG("Health regenerated: %f, current hp: %f/%f", amount, _currentHealth, _maxHealth);
	}
}