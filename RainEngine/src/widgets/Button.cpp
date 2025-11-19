#include "widgets/Button.h"
#include "framework/Delegate.h"
#include "framework/AssetManager.h"

namespace rn
{
	Button::Button(const std::string& text, const std::string& texturePath)
		: _buttonTexture{AssetManager::Get().LoadTexture(texturePath)},
		_buttonSprite{*(_buttonTexture.get())},
		_buttonFont{AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf")},
		_buttonText{ text, *(_buttonFont.get())},
		_normalColor{215, 215, 215, 255},
		_pressedColor{128, 128, 128, 255},
		_hoverColor{190, 190, 190, 255},
		_disabledColor{64, 64, 64, 128},
		_isButtonDown{false},
		_isDisabled{false}
	{
		_buttonSprite.setColor(_normalColor);
		CenterText();
	}

	sf::FloatRect Button::GetBound() const
	{
		return _buttonSprite.getGlobalBounds();
	}

	bool Button::HandleEvent(const sf::Event& ev)
	{
		bool result = false;

		if (_isDisabled || !GetVisibility())
			return result;

		if (ev.type == sf::Event::MouseButtonReleased)
		{
			if (ev.mouseButton.button == sf::Mouse::Left)
			{
				if (_buttonSprite.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y) && _isButtonDown)
				{
					onButtonClicked.Broadcast();
					result = true;
				}
			}
			ButtonUp();
		}
		else if (ev.type == sf::Event::MouseButtonPressed)
		{
			if (_buttonSprite.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
			{
				ButtonDown();
				result = true;
			}
		}
		else if (ev.type == sf::Event::MouseMoved)
		{
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (_buttonSprite.getGlobalBounds().contains(ev.mouseMove.x, ev.mouseMove.y))
				{
					MouseHovered();
				}
				else
				{
					ButtonUp();
				}
			}
		}

		return result || Widget::HandleEvent(ev);
	}

	void Button::SetTextString(const std::string& newText)
	{
		_buttonText.setString(newText);
		CenterText();
	}

	void Button::SetTextSize(unsigned int size)
	{
		_buttonText.setCharacterSize(size);
		CenterText();
	}

	void Button::Draw(sf::RenderWindow& windowReference)
	{
		windowReference.draw(_buttonSprite);
		windowReference.draw(_buttonText);
	}

	void Button::LocationUpdated(const sf::Vector2f& newLocation)
	{
		_buttonSprite.setPosition(newLocation);
		CenterText();
	}

	void Button::RotationUpdated(float newRotation)
	{
		_buttonSprite.setRotation(newRotation);
		_buttonText.setRotation(newRotation);
	}

	void Button::CenterText()
	{
		sf::Vector2f widgetCenter = GetCenterPosition();
		sf::FloatRect textBound = _buttonText.getGlobalBounds();

		_buttonText.setPosition(widgetCenter - sf::Vector2f{ textBound.width / 2.0f, textBound.height });
	}

	void Button::ButtonDown()
	{
		_isButtonDown = true;
		_buttonSprite.setColor(_pressedColor);
	}

	void Button::ButtonUp()
	{
		_isButtonDown = false;
		_buttonSprite.setColor(_normalColor);
	}

	void Button::MouseHovered()
	{
		_buttonSprite.setColor(_hoverColor);
	}
}