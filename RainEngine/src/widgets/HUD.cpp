#include "widgets/HUD.h"

namespace rn
{
	void HUD::NativeInitialize(const sf::RenderWindow& windowReference)
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

	void HUD::Tick(float deltaTime)
	{
	}

	HUD::HUD()
		: _isInitialized{false}
	{
	}

	void HUD::Initialize(const sf::RenderWindow& windowReference)
	{
	}
}