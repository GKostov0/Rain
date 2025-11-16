#include <SFML/System.hpp>
#include "Player/PlayerSpaceship.h"
#include "framework/MathUtility.h"
#include "Weapon/BulletShooter.h"
#include "Weapon/ThreeWayShooter.h"
#include "Weapon/FrontalWiper.h"

namespace rn
{
	PlayerSpaceship::PlayerSpaceship(World* owner, const std::string& path)
		: Spaceship{ owner, path },
		_moveInput{},
		_speed{ 400.0f },
		_invulnerableTime{2.0f},
		_invulnerableFlashInterval{0.3f},
		_invulnerableFlashTimer{0.0f},
		_invulnerableFlashDirection{1.0f},
		_isInvulnerable{true},
		_shooter{ new BulletShooter{this, 0.15f, {50.0f, 0.0f}} }
	{
		SetTeamID(1);
	}

	void PlayerSpaceship::BeginPlay()
	{
		Spaceship::BeginPlay();
		TimerManager::Get().SetTimer(GetWeakReference(), &PlayerSpaceship::StopInvulnerable, _invulnerableTime);
	}

	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		HandleInput();
		ConsumeInput(deltaTime);
		UpdateInvulnerable(deltaTime);
	}

	void PlayerSpaceship::ApplyDamage(float amount)
	{
		if (!_isInvulnerable)
		{
			Spaceship::ApplyDamage(amount);
		}
	}

	void PlayerSpaceship::Shoot()
	{
		if (_shooter)
		{
			_shooter->Shoot();
		}
	}

	void PlayerSpaceship::SetShooter(unique<Shooter>&& newShooter)
	{
		if (_shooter && typeid(*_shooter.get()) == typeid(*newShooter.get()))
		{
			_shooter->IncrementLevel();
			return;
		}

		_shooter = std::move(newShooter);
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

	void PlayerSpaceship::StopInvulnerable()
	{
		GetSprite().setColor({ 255, 255, 255, 255 });
		_isInvulnerable = false;
	}

	void PlayerSpaceship::UpdateInvulnerable(float deltaTime)
	{
		if (!_isInvulnerable)
			return;

		_invulnerableFlashTimer += deltaTime * _invulnerableFlashDirection;

		if (_invulnerableFlashTimer < 0 || _invulnerableFlashTimer > _invulnerableFlashInterval)
		{
			_invulnerableFlashDirection *= -1;
		}

		GetSprite().setColor(LerpColor({ 255, 255, 255, 64 }, {255, 255, 255, 128}, _invulnerableFlashTimer / _invulnerableFlashInterval));
	}
}