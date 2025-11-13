#pragma once

#include "widgets/Widget.h"

namespace rn
{
	class Button : public Widget
	{
	public:
		Button(const std::string& text = "Button", const std::string& texturePath = "SpaceShooterRedux/PNG/UI/buttonBlue.png");
		virtual sf::FloatRect GetBound() const override;

	private:
		virtual void Draw(sf::RenderWindow& windowReference) override;
		virtual void LocationUpdated(const sf::Vector2f& newLocation) override;
		virtual void RotationUpdated(float newRotation) override;

	private:
		shared<sf::Texture> _buttonTexture;
		sf::Sprite _buttonSprite;

		shared<sf::Font> _buttonFont;
		sf::Text _buttonText;

		sf::Color _normalColor;
		sf::Color _pressedColor;
		sf::Color _hoverColor;
		sf::Color _disabledColor;

		bool _isPressed;
	};
}