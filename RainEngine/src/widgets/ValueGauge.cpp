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
	}

	void ValueGauge::LocationUpdated(const sf::Vector2f& newLocation)
	{
		_text.setPosition(newLocation);
		_frontBar.setPosition(newLocation);
		_backBar.setPosition(newLocation);
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
}