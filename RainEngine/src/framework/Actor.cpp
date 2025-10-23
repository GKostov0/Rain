#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace rn
{
	Actor::Actor(World* owner, const std::string& texturePath)
		: _owner{ owner }, _beginPlay{ false }, _texture{ }, _sprite{ }
	{
		SetTexture(texturePath);
	}

	Actor::~Actor()
	{
		LOG("Actor Destroyed!");
	}

	void Actor::BeginPlayInternal()
	{
		if (!_beginPlay)
		{
			_beginPlay = true;
			BeginPlay();
		}
	}

	void Actor::BeginPlay()
	{
		LOG("Actor begin play");
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (!IsPendingDestroy())
		{
			Tick(deltaTime);
		}
	}

	void Actor::Tick(float deltaTime)
	{
	}

	void Actor::SetTexture(const std::string& path)
	{
		_texture = AssetManager::Get().LoadTexture(path);
		if (!_texture) return;

		_sprite.setTexture(*_texture);

		int textureWidth = _texture->getSize().x;
		int textureHeight = _texture->getSize().y;

		_sprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight} });
		CenterPivot();
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy())
			return;

		window.draw(_sprite);
	}

	void Actor::SetActorLocation(const sf::Vector2f& newLocation)
	{
		_sprite.setPosition(newLocation);
	}

	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmount)
	{
		SetActorLocation(GetActorLocation() + offsetAmount);
	}

	void Actor::SetActorRotation(float newRotation)
	{
		_sprite.setRotation(newRotation);
	}

	void Actor::AddActorRotationOffset(float offsetAmount)
	{
		SetActorRotation(GetActorRotation() + offsetAmount);
	}

	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation());
	}

	sf::Vector2f Actor::GetActorRightDirection() const
	{
		return RotationToVector(GetActorRotation() + 90.0f);
	}

	sf::Vector2f Actor::GetActorLocation() const
	{
		return _sprite.getPosition();
	}

	float Actor::GetActorRotation() const
	{
		return _sprite.getRotation();
	}

	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return _sprite.getGlobalBounds();
	}

	sf::Vector2u Actor::GetWindowSize() const
	{
		return _owner->GetWindowSize();
	}

	bool Actor::IsActorOutOfBounds() const
	{
		float windowWidth = GetWindowSize().x;
		float windowHeight = GetWindowSize().y;

		float width = GetActorGlobalBounds().width;
		float height = GetActorGlobalBounds().height;

		sf::Vector2f actorPosition = GetActorLocation();

		// Left						   or	Right
		if ((actorPosition.x < -width) || (actorPosition.x > windowWidth + width))
		{
			return true;
		}

		// Up							or	Down
		if ((actorPosition.y < -height) || (actorPosition.y > windowHeight + height))
		{
			return true;
		}

		return false;
	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bound = _sprite.getGlobalBounds();
		_sprite.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
	}
}