#pragma once

#include "widgets/Widget.h"

namespace rn
{
	class Button : public Widget
	{
	public:
		Button(const std::string& text = "Button", const std::string& texturePath = "SpaceShooterRedux/PNG/UI/buttonBlue.png");

		virtual sf::FloatRect GetBound() const override;
		virtual bool HandleEvent(const sf::Event& ev) override;

		void SetTextString(const std::string& newText);
		void SetTextSize(unsigned int size);

		Delegate<> onButtonClicked;

	private:
		virtual void Draw(sf::RenderWindow& windowReference) override;
		virtual void LocationUpdated(const sf::Vector2f& newLocation) override;
		virtual void RotationUpdated(float newRotation) override;

		void CenterText();

		void ButtonDown();
		void ButtonUp();
		void MouseHovered();

	private:
		shared<sf::Texture> _buttonTexture;
		sf::Sprite _buttonSprite;

		shared<sf::Font> _buttonFont;
		sf::Text _buttonText;

		sf::Color _normalColor;
		sf::Color _pressedColor;
		sf::Color _hoverColor;
		sf::Color _disabledColor;

		bool _isButtonDown;
		bool _isDisabled;
	};
}