#pragma once

#include "framework/Actor.h"

namespace rn
{
	class BackgroundLayer : public Actor
	{
	public:
		BackgroundLayer(World* owner, const List<std::string>& assetPaths = {},
			const sf::Vector2f& minVelocity = sf::Vector2f{0.0f, 50.0f}, const sf::Vector2f& maxVelocity = sf::Vector2f{ 0.0f, 200.0f },
			float minSize = 1.0f, float maxSize = 2.0f, int spriteCount = 20,
			const sf::Color& colorTint = sf::Color{180, 180, 200, 255});

	private:
		sf::Vector2f _minVelocity;
		sf::Vector2f _maxVelocity;

		float _minSize;
		float _maxSize;
		int _spriteCount;

		sf::Color _tintColor;

		List<shared<sf::Texture>> _textures;
		List<sf::Sprite> _sprites;
		List<sf::Vector2f> _velocities;
	};
}