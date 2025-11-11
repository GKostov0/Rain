#pragma once

#include "widgets/Widget.h"

namespace rn
{
	class ValueGauge : public Widget
	{
	public:
		ValueGauge(const sf::Vector2f& size = {200.0f, 30.0f}, float initialPercent = 0.75f,
			const sf::Color& frontColor = sf::Color{128, 255, 128, 255},
			const sf::Color& backColor = sf::Color{ 128, 128, 128, 255 });

		void UpdatValue(float value, float maxValue);
		void SetTextSize(unsigned int textSize);

		void SetForegroundColor(const sf::Color color);
		void SetBackgroundColor(const sf::Color color);

		virtual sf::FloatRect GetBound() const override;

	private:
		virtual void LocationUpdated(const sf::Vector2f& newLocation) override;
		virtual void RotationUpdated(float newRotation) override;
		virtual void Draw(sf::RenderWindow& windowReference) override;

		void CenterText();

	private:
		shared<sf::Font> _textFont;
		sf::Text _text;

		sf::RectangleShape _frontBar;
		sf::RectangleShape _backBar;

		sf::Color _frontColor;
		sf::Color _backColor;

		float _percent;
	};
}