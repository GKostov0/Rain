#pragma once

#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGauge.h"
#include "widgets/ImageWidget.h"
#include "widgets/Button.h"


namespace rn
{
	class Actor;

	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Draw(sf::RenderWindow& windowReference) override;
		virtual void Tick(float deltaTime) override;
		virtual bool HandleEvent(const sf::Event& ev) override;

	private:
		virtual void Initialize(const sf::RenderWindow& windowReference) override;

		void RefreshHealthBar();
		void PlayerHealthUpdated(float amount, float currentHealth, float maxHealth);
		void PlayerSpaceshipDestroyed(Actor* actor);
		void ConnectPlayerStatus();
		void PlayerLifeCountUpdated(int amount);
		void PlayerScorCountUpdated(int amount);

		void TESTFUNCTION();

	private:

		TextWidget _framerateText;
		TextWidget _playerLifeText;
		TextWidget _playerScoreText;

		ValueGauge _playerHealthGauge;

		sf::Color _healthGoodColor;
		sf::Color _healthDamagedColor;
		sf::Color _healthCriticalColor;

		ImageWidget _playerLifeIcon;
		ImageWidget _playerScoreIcon;

		Button _testButton;

		float _criticalThreshold;
		float _widgetSpaceing;
	};
}