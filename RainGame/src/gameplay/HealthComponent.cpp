#include "gameplay/HealthComponent.h"

#include "framework/Core.h"

namespace rn
{
	HealthComponent::HealthComponent(float currentHealt, float maxHealth)
		: _currentHealth{ currentHealt },
		_maxHealth{maxHealth}
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

		onHealthChanged.Broadcast(amount, _currentHealth, _maxHealth);

		if (amount < 0)
		{
			TakenDamage(-amount);

			if (_currentHealth <= 0)
			{
				HealthEmpty();
			}
		}
	}

	void HealthComponent::SetInitialHealth(float health, float maxHealth)
	{
		_currentHealth = health;
		_maxHealth = maxHealth;
	}

	void HealthComponent::TakenDamage(float amount)
	{
		onTakenDamage.Broadcast(amount, _currentHealth, _maxHealth);
	}

	void HealthComponent::HealthEmpty()
	{
		onHealthEmpty.Broadcast();
	}
}