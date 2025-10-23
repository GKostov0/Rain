#include "SpaceShip/SpaceShip.h"

namespace rn
{
	SpaceShip::SpaceShip(World* owner, const std::string& texturePath)
		: Actor{ owner, texturePath }, _velocity{}
	{

	}

	void SpaceShip::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		AddActorLocationOffset(_velocity * deltaTime);
	}

	void SpaceShip::SetVelocity(const sf::Vector2f& velocity)
	{
		_velocity = velocity;
	}

	void SpaceShip::Shoot()
	{

	}
}