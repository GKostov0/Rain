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

		virtual void BeginPlay() override;
		virtual void Render(sf::RenderWindow& windowReference) override;
		virtual void Tick(float deltaTime) override;

		void SetAssets(const List<std::string>& assetPaths);
		void SetColorTint(const sf::Color& color);
		void SetSpriteCount(int newCount);
		void SetVelocities(const sf::Vector2f& min, const sf::Vector2f& max);
		void SetSizes(float min, float max);

	private:
		void RefreshSprites();
		void RandomSpriteTexture(sf::Sprite& sprite);
		void RandomSpriteTransform(sf::Sprite& sprite, bool randomY = false);
		void RandomSpritePosition(sf::Sprite& sprite, bool randomY);
		void RandomSpriteRotation(sf::Sprite& sprite);
		void RandomSpriteSize(sf::Sprite& sprite);

		bool IsSpriteOffScreen(sf::Sprite& sprite) const;
		shared<sf::Texture> GetRandomTexture() const;

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

		sf::Vector2u _windowSize;
	};
}