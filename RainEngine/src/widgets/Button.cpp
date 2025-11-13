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
		_normalColor{255, 255, 255, 255},
		_pressedColor{128, 128, 128, 255},
		_hoverColor{190, 190, 190, 255},
		_disabledColor{64, 64, 64, 128},
		_isPressed{false}
	{
	}

	sf::FloatRect Button::GetBound() const
	{
		return _buttonSprite.getGlobalBounds();
	}

	void Button::Draw(sf::RenderWindow& windowReference)
	{
		windowReference.draw(_buttonSprite);
		windowReference.draw(_buttonText);
	}

	void Button::LocationUpdated(const sf::Vector2f& newLocation)
	{
		_buttonSprite.setPosition(newLocation);
		_buttonText.setPosition(newLocation);
	}

	void Button::RotationUpdated(float newRotation)
	{
		_buttonSprite.setRotation(newRotation);
		_buttonText.setRotation(newRotation);
	}
}