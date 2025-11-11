#include "widgets/ValueGauge.h"

#include "framework/AssetManager.h"

namespace rn
{
	ValueGauge::ValueGauge(const sf::Vector2f& size, float initialPercent, const sf::Color& frontColor, const sf::Color& backColor)
		: _textFont{ AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf") },
		_text{ "", *(_textFont.get()) },
		_frontBar{ size },
		_backBar{ size },
		_frontColor{frontColor},
		_backColor{backColor},
		_percent{ initialPercent }
	{
		_frontBar.setFillColor(_frontColor);
		_backBar.setFillColor(_backColor);
		SetTextSize(20);
	}

	void ValueGauge::UpdatValue(float value, float maxValue)
	{
		if (maxValue == 0)
			return;

		_percent = value / maxValue;
		std::string diplayText = std::to_string((int)value) + "/" + std::to_string((int)maxValue);
		_text.setString(diplayText);

		sf::Vector2f barSize = _backBar.getSize();
		_frontBar.setSize({barSize.x * _percent, barSize.y});
		CenterText();
	}

	sf::FloatRect ValueGauge::GetBound() const
	{
		return _backBar.getGlobalBounds();
	}

	void ValueGauge::LocationUpdated(const sf::Vector2f& newLocation)
	{
		_frontBar.setPosition(newLocation);
		_backBar.setPosition(newLocation);
		CenterText();
	}

	void ValueGauge::CenterText()
	{
		sf::Vector2f widgetCenter = GetCenterPosition();
		sf::FloatRect textBound = _text.getGlobalBounds();

		_text.setPosition(widgetCenter - sf::Vector2f{textBound.width / 2.0f, textBound.height});
	}

	void ValueGauge::RotationUpdated(float newRotation)
	{
		_text.setRotation(newRotation);
		_frontBar.setRotation(newRotation);
		_backBar.setRotation(newRotation);
	}

	void ValueGauge::Draw(sf::RenderWindow& windowReference)
	{
		windowReference.draw(_backBar);
		windowReference.draw(_frontBar);
		windowReference.draw(_text);
	}

	void ValueGauge::SetTextSize(unsigned int textSize)
	{
		_text.setCharacterSize(textSize);
	}

	void ValueGauge::SetForegroundColor(const sf::Color color)
	{
		_frontBar.setFillColor(color);
	}

	void ValueGauge::SetBackgroundColor(const sf::Color color)
	{
		_backBar.setFillColor(color);
	}
}