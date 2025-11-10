#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "widgets/Widget.h"

namespace rn
{
	class TextWidget : public Widget
	{
	public:
		TextWidget(const std::string& text,
			const std::string& fontPath = "SpaceShooterRedux/Bonus/kenvector_future.ttf",
			unsigned int characterSize = 10);

		void SetString(const std::string& newString);
		void SetTextSize(unsigned int newSize);

	private:
		virtual void LocationUpdated(const sf::Vector2f& newLocation) override;
		virtual void RotationUpdated(float newRotation) override;
		virtual void Draw(sf::RenderWindow& windowReference) override;

	private:
		shared<sf::Font> _font;
		sf::Text _text;
	};
}