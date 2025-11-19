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

		void GameFinished(bool didWin);

		Delegate<> onRestartButtonClicked;
		Delegate<> onQuitButtonClicked;

	private:
		virtual void Initialize(const sf::RenderWindow& windowReference) override;

		void RefreshHealthBar();
		void PlayerHealthUpdated(float amount, float currentHealth, float maxHealth);
		void PlayerSpaceshipDestroyed(Actor* actor);
		void ConnectPlayerStatus();
		void PlayerLifeCountUpdated(int amount);
		void PlayerScorCountUpdated(int amount);

		void RestartButtonClicked();
		void QuitButtonClicked();

	private:
		TextWidget _framerateText;
		TextWidget _playerLifeText;
		TextWidget _playerScoreText;
		TextWidget _winLoseText;
		TextWidget _finalScoreText;

		Button _restartButton;
		Button _quitButton;

		ValueGauge _playerHealthGauge;

		sf::Color _healthGoodColor;
		sf::Color _healthDamagedColor;
		sf::Color _healthCriticalColor;

		ImageWidget _playerLifeIcon;
		ImageWidget _playerScoreIcon;

		float _criticalThreshold;
		float _widgetSpaceing;
	};
}