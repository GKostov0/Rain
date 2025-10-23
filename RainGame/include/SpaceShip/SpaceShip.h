#pragma once

#include "framework/Actor.h"

namespace rn
{
	class SpaceShip : public Actor
	{
	public:
		SpaceShip(World* owner, const std::string& texturePath = "");

		virtual void Tick(float deltaTime) override;

		void SetVelocity(const sf::Vector2f& velocity);

		sf::Vector2f GetVelocity() const { return _velocity; }

		virtual void Shoot();

	private:

		sf::Vector2f _velocity;
	};
}