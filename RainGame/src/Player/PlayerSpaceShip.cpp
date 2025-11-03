#include <SFML/System.hpp>
#include "Player/PlayerSpaceship.h"
#include "framework/MathUtility.h"
#include "Weapon/BulletShooter.h"
#include "Weapon/ThreeWayShooter.h"

namespace rn
{
	PlayerSpaceship::PlayerSpaceship(World* owner, const std::string& path)
		: Spaceship{ owner, path },
		_moveInput{},
		_speed{ 400.0f },
		_shooter{ new ThreeWayShooter{this, 0.1f, {50.0f, 0.0f}} }
	{
		SetTeamID(1);
	}

	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		HandleInput();
		ConsumeInput(deltaTime);
	}

	void PlayerSpaceship::Shoot()
	{
		if (_shooter)
		{
			_shooter->Shoot();
		}
	}

	void PlayerSpaceship::HandleInput()
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

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Shoot();
		}
	}

	void PlayerSpaceship::ConsumeInput(float deltaTime)
	{
		SetVelocity(_moveInput * _speed);
		_moveInput.x = _moveInput.y = 0;
	}

	void PlayerSpaceship::NormalizeInput()
	{
		Normalize(_moveInput);
	}

	void PlayerSpaceship::ClampInputOnEdge()
	{
		sf::Vector2f actorLocation = GetActorLocation();

		if (actorLocation.x < 0 && _moveInput.x == -1)					{ _moveInput.x = 0; }			// Left
		if (actorLocation.x > GetWindowSize().x && _moveInput.x == 1)	{ _moveInput.x = 0; }			// Right
		if (actorLocation.y < 0 && _moveInput.y == -1)					{ _moveInput.y = 0; }			// Up
		if (actorLocation.y > GetWindowSize().y && _moveInput.y == 1)	{ _moveInput.y = 0; }			// Down
	}
}