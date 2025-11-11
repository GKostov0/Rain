#include "widgets/ImageWidget.h"
#include "framework/AssetManager.h"

namespace rn
{
	ImageWidget::ImageWidget(const std::string& imagePath)
		: _texture{AssetManager::Get().LoadTexture(imagePath)},
		_sprite{*(_texture.get())}
	{
	}

	sf::FloatRect ImageWidget::GetBound() const
	{
		return _sprite.getGlobalBounds();
	}

	void ImageWidget::SetImage(const shared<sf::Texture>& newTexture)
	{
		if (newTexture)
		{
			_texture = newTexture;
			_sprite.setTexture(*(_texture.get()));
		}
	}

	void ImageWidget::LocationUpdated(const sf::Vector2f& newLocation)
	{
		_sprite.setPosition(newLocation);
	}

	void ImageWidget::RotationUpdated(float newRotation)
	{
		_sprite.setRotation(newRotation);
	}

	void ImageWidget::Draw(sf::RenderWindow& windowReference)
	{
		windowReference.draw(_sprite);
	}
}