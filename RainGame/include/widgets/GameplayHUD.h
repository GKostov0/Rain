#pragma once

#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGauge.h"

namespace rn
{
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Draw(sf::RenderWindow& windowReference) override;
		virtual void Tick(float deltaTime) override;

	private:
		virtual void Initialize(const sf::RenderWindow& windowReference) override;

	private:
		TextWidget _framerateText;
		ValueGauge _playerHealthGauge;
	};
}