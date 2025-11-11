#pragma once

#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGauge.h"
#include "widgets/ImageWidget.h"


namespace rn
{
	class Actor;

	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Draw(sf::RenderWindow& windowReference) override;
		virtual void Tick(float deltaTime) override;

	private:
		virtual void Initialize(const sf::RenderWindow& windowReference) override;

		void RefreshHealthBar();
		void PlayerHealthUpdated(float amount, float currentHealth, float maxHealth);
		void PlayerSpaceshipDestroyed(Actor* actor);

	private:
		TextWidget _framerateText;
		ValueGauge _playerHealthGauge;

		sf::Color _healthGoodColor;
		sf::Color _healthDamagedColor;
		sf::Color _healthCriticalColor;

		ImageWidget _playerLifeIcon;

		float _criticalThreshold;
		float _widgetSpaceing;
	};
}