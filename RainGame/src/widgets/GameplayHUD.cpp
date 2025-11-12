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
		_playerHealthGauge{},
		_healthGoodColor{ 128, 255, 128, 255 },
		_healthDamagedColor{ 255, 200, 0, 255 },
		_healthCriticalColor{255, 64, 0, 255},
		_playerLifeIcon{ "SpaceShooterRedux/PNG/pickups/playerLife1_blue.png" },
		_playerScoreIcon{ "SpaceShooterRedux/PNG/Power-ups/star_gold.png" },
		_criticalThreshold{0.3f},
		_widgetSpaceing{10.0f}
	{
		_framerateText.SetTextSize(20);
		_playerLifeText.SetTextSize(20);
		_playerScoreText.SetTextSize(20);
	}

	void GameplayHUD::Initialize(const sf::RenderWindow& windowReference)
	{
		auto windowSize = windowReference.getSize();
		_playerHealthGauge.SetWidgetLocation({ 10.0f, windowSize.y - 40.0f });

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
	}

	void GameplayHUD::Draw(sf::RenderWindow& windowReference)
	{
		_framerateText.NativeDraw(windowReference);
		_playerHealthGauge.NativeDraw(windowReference);

		// Score
		_playerScoreIcon.NativeDraw(windowReference);
		_playerScoreText.NativeDraw(windowReference);

		// Life
		_playerLifeIcon.NativeDraw(windowReference);
		_playerLifeText.NativeDraw(windowReference);
	}

	void GameplayHUD::Tick(float deltaTime)
	{
		int framerate = int(1 / deltaTime);
		std::string fps = "FPS: " + std::to_string(framerate);
		_framerateText.SetString(fps);
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
}