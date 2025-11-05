#include "widgets/HUD.h"

namespace rn
{
	void HUD::NativeIniti(sf::RenderWindow& windowReference)
	{
		if (!_isInitialized)
		{
			_isInitialized = true;
			Initialize(windowReference);
		}
	}

	bool HUD::HandleEvent(const sf::Event& ev)
	{
		return false;
	}

	HUD::HUD()
		: _isInitialized{false}
	{
	}

	void HUD::Initialize(sf::RenderWindow& windowReference)
	{
	}
}