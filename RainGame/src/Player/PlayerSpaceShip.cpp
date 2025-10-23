#include <SFML/System.hpp>
#include "Player/PlayerSpaceShip.h"
#include "framework/MathUtility.h"

namespace rn
{
	PlayerSpaceShip::PlayerSpaceShip(World* owner, const std::string& path)
		: SpaceShip{ owner, path }, _moveInput{}, _speed{200.0f}
	{
	}

	void PlayerSpaceShip::Tick(float deltaTime)
	{
		SpaceShip::Tick(deltaTime);
		HandleInput();
		ConsumeInput(deltaTime);
	}

	void PlayerSpaceShip::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			_moveInput.y = -1.0f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			_moveInput.y = 1.0f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			_moveInput.x = -1.0f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			_moveInput.x = 1.0f;
		}

		NormalizeInput();
	}

	void PlayerSpaceShip::ConsumeInput(float deltaTime)
	{
		SetVelocity(_moveInput * _speed);
		_moveInput.x = _moveInput.y = 0;
	}

	void PlayerSpaceShip::NormalizeInput()
	{
		Normalize(_moveInput);
		LOG("Move input is now: %f, %f", _moveInput.x, _moveInput.y);
	}
}