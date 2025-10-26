#include "VFX/Particle.h"
#include "framework/MathUtility.h"

namespace rn
{
	Particle::Particle(World* owner, const std::string& path)
		: Actor{ owner, path }, _velocity{}, _lifetime{ 1.0f }, _timer{}
	{
	}

	void Particle::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		Move(deltaTime);
		Fade(deltaTime);

		if (_timer.getElapsedTime().asSeconds() >= _lifetime)
		{
			Destroy();
		}
	}

	void Particle::RandomVelocity(float minSpeed, float maxSpeed)
	{
		_velocity = RandomUnitVector() * RandomRange(minSpeed, maxSpeed);
	}

	void Particle::RandomSize(float min, float max)
	{
		float scale = RandomRange(min, max);
		GetSprite().setScale(scale, scale);
	}

	void Particle::RandomLifetime(float min, float max)
	{
		_lifetime = RandomRange(min, max);
	}

	void Particle::Move(float deltaTime)
	{
		AddActorLocationOffset(_velocity * deltaTime);
	}

	void Particle::Fade(float deltaTime)
	{
		float elapsedTime = _timer.getElapsedTime().asSeconds();
		GetSprite().setColor(LerpColor(GetSprite().getColor(), sf::Color(255, 255, 255, 0), elapsedTime / _lifetime));
		GetSprite().setScale(LerpVector(GetSprite().getScale(), sf::Vector2f{ 0, 0 }, elapsedTime / _lifetime));
	}
}