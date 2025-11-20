#include "framework/BackgroundLayer.h"

#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"

namespace rn
{
	BackgroundLayer::BackgroundLayer(World* owner, const List<std::string>& assetPaths,
		const sf::Vector2f& minVelocity, const sf::Vector2f& maxVelocity,
		float minSize, float maxSize, int spriteCount, const sf::Color& colorTint)
		: Actor{owner},
		_minVelocity{minVelocity},
		_maxVelocity{maxVelocity},
		_minSize{ minSize },
		_maxSize{maxSize},
		_spriteCount{spriteCount},
		_tintColor{colorTint},
		_windowSize{}
	{
		SetAssets(assetPaths);
		SetEnablePhysics(false);
	}

	void BackgroundLayer::BeginPlay()
	{
		Actor::BeginPlay();
		_windowSize = GetWorld()->GetWindowSize();
	}

	void BackgroundLayer::Render(sf::RenderWindow& windowReference)
	{
		Actor::Render(windowReference);

		for (const sf::Sprite& sprite : _sprites)
		{
			windowReference.draw(sprite);
		}
	}

	void BackgroundLayer::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		for (int i = 0; i < _sprites.size(); ++i)
		{
			sf::Sprite& sprite = _sprites[i];
			sf::Vector2f& velocity = _velocities[i];

			sprite.setPosition(sprite.getPosition() + velocity * deltaTime);

			if (IsSpriteOffScreen(sprite))
			{
				RandomSpriteTexture(sprite);
				RandomSpriteTransform(sprite);

				float velocityX = RandomRange(_minVelocity.x, _maxVelocity.x);
				float velocityY = RandomRange(_minVelocity.y, _maxVelocity.y);

				_velocities[i] = sf::Vector2f{ velocityX ,velocityY };
			}
		}
	}

	void BackgroundLayer::SetAssets(const List<std::string>& assetPaths)
	{
		for (const std::string& texturePath : assetPaths)
		{
			shared<sf::Texture> newTexture = AssetManager::Get().LoadTexture(texturePath);
			_textures.push_back(newTexture);
		}
		RefreshSprites();
	}

	void BackgroundLayer::SetColorTint(const sf::Color& color)
	{
		_tintColor = color;
		for (sf::Sprite& sprite : _sprites)
		{
			sprite.setColor(_tintColor);
		}
	}

	void BackgroundLayer::SetSpriteCount(int newCount)
	{
		_spriteCount = newCount;
		RefreshSprites();
	}

	void BackgroundLayer::SetVelocities(const sf::Vector2f& min, const sf::Vector2f& max)
	{
		_minVelocity = min;
		_maxVelocity = max;

		for (int i = 0; i < _velocities.size(); ++i)
		{
			float velocityX = RandomRange(_minVelocity.x, _maxVelocity.x);
			float velocityY = RandomRange(_minVelocity.y, _maxVelocity.y);

			_velocities[i] = sf::Vector2f{ velocityX , velocityY };
		}
	}

	void BackgroundLayer::SetSizes(float min, float max)
	{
		_minSize = min;
		_maxSize = max;

		for (sf::Sprite& sprite : _sprites)
		{
			RandomSpriteSize(sprite);
		}
	}

	void BackgroundLayer::RefreshSprites()
	{
		_sprites.clear();
		_velocities.clear();

		for (int i = 0; i < _spriteCount; ++i)
		{
			sf::Sprite newSprite{};
			RandomSpriteTexture(newSprite);
			RandomSpriteTransform(newSprite, true);
			_sprites.push_back(newSprite);

			float velocityX = RandomRange(_minVelocity.x, _maxVelocity.x);
			float velocityY = RandomRange(_minVelocity.y, _maxVelocity.y);

			_velocities.push_back(sf::Vector2f{ velocityX , velocityY });
		}

		SetColorTint(_tintColor);
	}

	void BackgroundLayer::RandomSpriteTexture(sf::Sprite& sprite)
	{
		if (_textures.size() <= 0)
			return;

		shared<sf::Texture> randomTexture = GetRandomTexture();
		sprite.setTexture(*(randomTexture.get()));
		sprite.setTextureRect(sf::IntRect{0, 0, (int)randomTexture->getSize().x, (int)randomTexture->getSize().y});

		sf::FloatRect bound = sprite.getGlobalBounds();
		sprite.setOrigin(bound.width / 2.0f, bound. height / 2.0f);
	}

	void BackgroundLayer::RandomSpriteTransform(sf::Sprite& sprite, bool randomY)
	{
		RandomSpritePosition(sprite, randomY);
		RandomSpriteRotation(sprite);
		RandomSpriteSize(sprite);
	}

	void BackgroundLayer::RandomSpritePosition(sf::Sprite& sprite, bool randomY)
	{
		auto bound = sprite.getGlobalBounds();

		float positionX = RandomRange(0.0f, _windowSize.x);
		float positionY = randomY ?  RandomRange(0.0f, _windowSize.y) : -bound.height;

		sprite.setPosition(sf::Vector2f{positionX, positionY});
	}

	void BackgroundLayer::RandomSpriteRotation(sf::Sprite& sprite)
	{
		sprite.setRotation(RandomRange(0.0f, 360.0f));
	}

	void BackgroundLayer::RandomSpriteSize(sf::Sprite& sprite)
	{
		float randomSize = RandomRange(_minSize, _maxSize);
		sprite.setScale(randomSize, randomSize);
	}

	bool BackgroundLayer::IsSpriteOffScreen(sf::Sprite& sprite) const
	{
		sf::FloatRect bound = sprite.getGlobalBounds();
		sf::Vector2f position = sprite.getPosition();

		if (position.x < -bound.width || position.x > _windowSize.x + bound.width)
		{
			return true;
		}

		if (position.y < -bound.height || position.y > _windowSize.y + bound.height)
		{
			return true;
		}

		return false;
	}

	shared<sf::Texture> BackgroundLayer::GetRandomTexture() const
	{
		int randomIndex = (int)(RandomRange(0, _textures.size()));
		return _textures[randomIndex];
	}
}