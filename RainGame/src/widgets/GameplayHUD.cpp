#include "framework/Actor.h"
#include "widgets/GameplayHUD.h"

#include "Player/Player.h"
#include "Player/PlayerManager.h"
#include "Player/PlayerSpaceship.h"

namespace rn
{
	GameplayHUD::GameplayHUD()
		: _framerateText{"FPS:"},
		_playerLifeText{ "" },
		_playerScoreText{""},
		_winLoseText{""},
		_finalScoreText{""},
		_restartButton{"Restart"},
		_quitButton{"Quit"},
		_playerHealthGauge{},
		_healthGoodColor{ 128, 255, 128, 255 },
		_healthDamagedColor{ 255, 200, 0, 255 },
		_healthCriticalColor{255, 64, 0, 255},
		_windowSize{},
		_playerLifeIcon{ "SpaceShooterRedux/PNG/pickups/playerLife1_blue.png" },
		_playerScoreIcon{ "SpaceShooterRedux/PNG/Power-ups/star_gold.png" },
		_criticalThreshold{0.3f},
		_widgetSpaceing{10.0f}
	{
		// In game stats
		// Text
		_framerateText.SetTextSize(20);
		_playerLifeText.SetTextSize(20);
		_playerScoreText.SetTextSize(20);

		// Game Over
		// Text
		_winLoseText.SetVisibility(false);
		_finalScoreText.SetVisibility(false);

		// Buttons
		_restartButton.SetVisibility(false);
		_quitButton.SetVisibility(false);
	}

	void GameplayHUD::Initialize(const sf::RenderWindow& windowReference)
	{
		_windowSize = windowReference.getSize();
		_playerHealthGauge.SetWidgetLocation({ 10.0f, _windowSize.y - 40.0f });

		sf::Vector2f nextWidgetPosition = _playerHealthGauge.GetWidgetLocation();

		nextWidgetPosition += sf::Vector2f{ _playerHealthGauge.GetBound().width + _widgetSpaceing * 3, 0.0f };
		_playerScoreIcon.SetWidgetLocation(nextWidgetPosition);

		nextWidgetPosition += sf::Vector2f{ _playerScoreIcon.GetBound().width + _widgetSpaceing, 0.0f };
		_playerScoreText.SetWidgetLocation(nextWidgetPosition);

		nextWidgetPosition += sf::Vector2f{ _playerScoreText.GetBound().width + _widgetSpaceing * 8, -2.0f};
		_playerLifeIcon.SetWidgetLocation(nextWidgetPosition);

		nextWidgetPosition += sf::Vector2f{ _playerLifeIcon.GetBound().width + _widgetSpaceing, 0.0f };
		_playerLifeText.SetWidgetLocation(nextWidgetPosition);

		RefreshHealthBar();
		ConnectPlayerStatus();

		_winLoseText.SetTextSize(40);
		_finalScoreText.SetTextSize(40);

		_restartButton.SetWidgetLocation({ _windowSize.x / 2.0f - _restartButton.GetBound().width / 2.0f, _windowSize.y / 2.0f });
		_quitButton.SetWidgetLocation(_restartButton.GetWidgetLocation() + sf::Vector2f(0.5f, 50.0f));

		_restartButton.onButtonClicked.BindAction(GetWeakReference(), &GameplayHUD::RestartButtonClicked);
		_quitButton.onButtonClicked.BindAction(GetWeakReference(), &GameplayHUD::QuitButtonClicked);
	}

	void GameplayHUD::Draw(sf::RenderWindow& windowReference)
	{
		_framerateText.NativeDraw(windowReference);
		_playerHealthGauge.NativeDraw(windowReference);

		// In game stats
		_playerScoreIcon.NativeDraw(windowReference);
		_playerScoreText.NativeDraw(windowReference);
		_playerLifeIcon.NativeDraw(windowReference);
		_playerLifeText.NativeDraw(windowReference);

		// Game Over
		_winLoseText.NativeDraw(windowReference);
		_finalScoreText.NativeDraw(windowReference);
		_restartButton.NativeDraw(windowReference);
		_quitButton.NativeDraw(windowReference);
	}

	void GameplayHUD::Tick(float deltaTime)
	{
		int framerate = int(1 / deltaTime);
		std::string fps = "FPS: " + std::to_string(framerate);
		_framerateText.SetString(fps);
	}

	bool GameplayHUD::HandleEvent(const sf::Event& ev)
	{
		if (_restartButton.HandleEvent(ev))
			return true;

		if (_quitButton.HandleEvent(ev))
			return true;

		return HUD::HandleEvent(ev);
	}

	void GameplayHUD::GameFinished(bool didWin)
	{
		_winLoseText.SetVisibility(true);
		_finalScoreText.SetVisibility(true);
		_restartButton.SetVisibility(true);
		_quitButton.SetVisibility(true);

		int score = PlayerManager::Get().GetPlayer()->GetScore();
		_finalScoreText.SetString("Score: " + std::to_string(score));

		_winLoseText.SetString(didWin ? "You Win!" : "You Lose!");

		_winLoseText.SetWidgetLocation({ _windowSize.x / 2.0f - _winLoseText.GetBound().width / 2.0f, 100.0f });
		_finalScoreText.SetWidgetLocation({ _windowSize.x / 2.0f - _finalScoreText.GetBound().width / 2.0f, 200.0f });
	}

	void GameplayHUD::PlayerHealthUpdated(float amount, float currentHealth, float maxHealth)
	{
		_playerHealthGauge.UpdatValue(currentHealth, maxHealth);

		if ((currentHealth / maxHealth) <= _criticalThreshold)
		{
			_playerHealthGauge.SetForegroundColor(_healthCriticalColor);
		}
		else
		{
			if (currentHealth == maxHealth)
			{
				_playerHealthGauge.SetForegroundColor(_healthGoodColor);
			}
			else
			{
				_playerHealthGauge.SetForegroundColor(_healthDamagedColor);
			}
		}
	}

	void GameplayHUD::RefreshHealthBar()
	{
		Player* player = PlayerManager::Get().GetPlayer();
		if (player && !player->GetCurrentSpaceship().expired())
		{
			weak<PlayerSpaceship> playerSpaceship = player->GetCurrentSpaceship();
			playerSpaceship.lock()->onActorDestroy.BindAction(GetWeakReference(), &GameplayHUD::PlayerSpaceshipDestroyed);

			HealthComponent& healthComponent = player->GetCurrentSpaceship().lock()->GetHealthComponent();
			healthComponent.onHealthChanged.BindAction(GetWeakReference(), &GameplayHUD::PlayerHealthUpdated);
			PlayerHealthUpdated(0, healthComponent.GetCurrentHealth(), healthComponent.GetMaxHealth());
		}
	}

	void GameplayHUD::PlayerSpaceshipDestroyed(Actor* actor)
	{
		RefreshHealthBar();
	}

	void GameplayHUD::ConnectPlayerStatus()
	{
		Player* player = PlayerManager::Get().GetPlayer();
		if (player)
		{
			int lifeCount = player->GetLifeCount();
			_playerLifeText.SetString(std::to_string(lifeCount));
			player->onLifeChange.BindAction(GetWeakReference(), &GameplayHUD::PlayerLifeCountUpdated);

			int playerScore = player->GetScore();
			_playerScoreText.SetString(std::to_string(playerScore));
			player->onScoreChange.BindAction(GetWeakReference(), &GameplayHUD::PlayerScorCountUpdated);
		}
	}

	void GameplayHUD::PlayerLifeCountUpdated(int amount)
	{
		_playerLifeText.SetString(std::to_string(amount));
	}

	void GameplayHUD::PlayerScorCountUpdated(int amount)
	{
		_playerScoreText.SetString(std::to_string(amount));
	}

	void GameplayHUD::RestartButtonClicked()
	{
		onRestartButtonClicked.Broadcast();
	}

	void GameplayHUD::QuitButtonClicked()
	{
		onQuitButtonClicked.Broadcast();
	}
}