#include <SFML/System.hpp>
#include "Player/PlayerSpaceShip.h"
#include "framework/MathUtility.h"
#include "Weapon/BulletShooter.h"

namespace rn
{
	PlayerSpaceShip::PlayerSpaceShip(World* owner, const std::string& path)
		: SpaceShip{ owner, path }, _moveInput{}, _speed{ 400.0f }, _shooter{ new BulletShooter{this, 0.1f} }
	{
	}

	void PlayerSpaceShip::Tick(float deltaTime)
	{
		SpaceShip::Tick(deltaTime);
		HandleInput();
		ConsumeInput(deltaTime);
	}

	void PlayerSpaceShip::Shoot()
	{
		if (_shooter)
		{
			_shooter->Shoot();
		}
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

		ClampInputOnEdge();
		NormalizeInput();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Shoot();
		}
	}

	void PlayerSpaceShip::ConsumeInput(float deltaTime)
	{
		SetVelocity(_moveInput * _speed);
		_moveInput.x = _moveInput.y = 0;
	}

	void PlayerSpaceShip::NormalizeInput()
	{
		Normalize(_moveInput);
	}

	void PlayerSpaceShip::ClampInputOnEdge()
	{
		sf::Vector2f actorLocation = GetActorLocation();

		if (actorLocation.x < 0 && _moveInput.x == -1)					{ _moveInput.x = 0; }			// Left
		if (actorLocation.x > GetWindowSize().x && _moveInput.x == 1)	{ _moveInput.x = 0; }			// Right
		if (actorLocation.y < 0 && _moveInput.y == -1)					{ _moveInput.y = 0; }			// Up
		if (actorLocation.y > GetWindowSize().y && _moveInput.y == 1)	{ _moveInput.y = 0; }			// Down
	}
}