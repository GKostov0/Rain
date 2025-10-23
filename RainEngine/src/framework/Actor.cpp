#include "framework/Actor.h"
#include "framework/Core.h"

#include "framework/AssetManager.h"

namespace rn
{
	Actor::Actor(World* owner, const std::string& texturePath)
		: _owner{ owner }, _beginPlay{ false }, _texture{ }, _sprite{ }
	{
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
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy())
			return;

		window.draw(_sprite);
	}
}
