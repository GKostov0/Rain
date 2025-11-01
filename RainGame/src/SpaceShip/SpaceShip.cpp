#include "Spaceship/Spaceship.h"
#include "framework/MathUtility.h"
#include "VFX/Explosion.h"

namespace rn
{
	Spaceship::Spaceship(World* owner, const std::string& texturePath)
		: Actor{ owner, texturePath }, _velocity{}, _healthComponent{100.0f, 100.0f},
		_blinkTimer{ 0.0f }, _blinkDuration{ 0.4f }, _blinkColor{255, 0, 0 , 255}
	{

	}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		AddActorLocationOffset(_velocity * deltaTime);
		UpdateBlink(deltaTime);
	}

	void Spaceship::SetVelocity(const sf::Vector2f& velocity)
	{
		_velocity = velocity;
	}

	void Spaceship::Shoot()
	{

	}

	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);

		_healthComponent.onHealthChanged.BindAction(GetWeakReference(), &Spaceship::OnHealthChanged);
		_healthComponent.onTakenDamage.BindAction(GetWeakReference(), &Spaceship::OnTakenDamage);
		_healthComponent.onHealthEmpty.BindAction(GetWeakReference(), &Spaceship::Blow);
	}

	void Spaceship::ApplyDamage(float amount)
	{
		_healthComponent.ChangeHealth(-amount);
	}

	void Spaceship::OnHealthChanged(float amount, float currentHelath, float maxHealth)
	{
		
	}

	void Spaceship::OnTakenDamage(float amount, float currentHelath, float maxHealth)
	{
		Blink();
	}

	void Spaceship::Blow()
	{
		Explosion* explosion = new Explosion();
		explosion->SpawnExplosion(GetWorld(), GetActorLocation());
		Destroy();
		delete explosion;
	}

	void Spaceship::Blink()
	{
		if (_blinkTimer == 0.0f)
		{
			_blinkTimer = _blinkDuration;
		}
	}

	void Spaceship::UpdateBlink(float deltaTime)
	{
		if (_blinkTimer > 0)
		{
			_blinkTimer -= deltaTime;

			_blinkTimer = _blinkTimer > 0 ? _blinkTimer : 0.0f;

			GetSprite().setColor(LerpColor(sf::Color::White, _blinkColor, _blinkTimer));
		}
	}
}