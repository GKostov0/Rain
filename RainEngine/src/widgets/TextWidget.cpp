#include "widgets/TextWidget.h"
#include "framework/AssetManager.h"

namespace rn
{
	TextWidget::TextWidget(const std::string& text, const std::string& fontPath, unsigned int characterSize)
		: _font{AssetManager::Get().LoadFont(fontPath)},
		_text{text, *(_font.get()), characterSize}
	{
	}

	void TextWidget::SetString(const std::string& newString)
	{
		_text.setString(newString);
	}

	void TextWidget::SetTextSize(unsigned int newSize)
	{
		_text.setCharacterSize(newSize);
	}

	sf::FloatRect TextWidget::GetBound() const
	{
		return _text.getGlobalBounds();
	}

	void TextWidget::LocationUpdated(const sf::Vector2f& newLocation)
	{
		_text.setPosition(newLocation);
	}

	void TextWidget::RotationUpdated(float newRotation)
	{
		_text.setRotation(newRotation);
	}

	void TextWidget::Draw(sf::RenderWindow& windowReference)
	{
		windowReference.draw(_text);
	}
}