#pragma once

#include "framework/Actor.h"

namespace rn
{
	class BackdropActor : public Actor
	{
	public:
		BackdropActor(World* owner, const std::string& texturePath, const sf::Vector2f& velocity = sf::Vector2f{0.0f, -50.0f});

		virtual void Tick(float deltaTime) override;

	private:
		sf::Vector2f _movingVelocity;

		float _leftShift;
		float _topShift;
	};
}