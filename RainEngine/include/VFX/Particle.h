#pragma once

#include "framework/Actor.h"

namespace rn
{
	class Particle : public Actor
	{
	public:
		Particle(World* owner, const std::string& path);

		virtual void Tick(float deltaTime) override;

		void RandomVelocity(float minSpeed, float maxSpeed);
		void RandomSize(float min, float max);
		void RandomLifetime(float min, float max);

	private:
		void Move(float deltaTime);
		void Fade(float deltaTime);

	private:

		sf::Vector2f _velocity;
		float _lifetime;
		sf::Clock _timer;
	};
}