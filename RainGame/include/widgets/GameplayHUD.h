#pragma once

#include "widgets/HUD.h"
#include "widgets/TextWidget.h"

namespace rn
{
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Draw(sf::RenderWindow& windowReference) override;
		virtual void Tick(float deltaTime) override;

	private:
		TextWidget _framerateText;
	};
}