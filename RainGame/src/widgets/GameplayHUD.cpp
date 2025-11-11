#include "framework/Actor.h"
#include "widgets/GameplayHUD.h"

#include "Player/Player.h"
#include "Player/PlayerManager.h"
#include "Player/PlayerSpaceship.h"

namespace rn
{
	GameplayHUD::GameplayHUD()
		: _framerateText{"FPS:"},
		_playerHealthGauge{},
		_healthGoodColor{ 128, 255, 128, 255 },
		_healthDamagedColor{ 255, 200, 0, 255 },
		_healthCriticalColor{255, 64, 0, 255},
		_criticalThreshold{0.3f},
		_playerLifeIcon{ "SpaceShooterRedux/PNG/pickups/playerLife1_blue.png" },
		_widgetSpaceing{10.0f}
	{
		_framerateText.SetTextSize(20);
	}

	void GameplayHUD::Initialize(const sf::RenderWindow& windowReference)
	{
		auto windowSize = windowReference.getSize();
		_playerHealthGauge.SetWidgetLocation({ 10.0f, windowSize.y - 40.0f });

		sf::Vector2f lifeIconPosition = _playerHealthGauge.GetWidgetLocation();
		lifeIconPosition += sf::Vector2f{_playerHealthGauge.GetBound().width + _widgetSpaceing, 10.0f};
		_playerLifeIcon.SetWidgetLocation(lifeIconPosition);

		RefreshHealthBar();
	}

	void GameplayHUD::Draw(sf::RenderWindow& windowReference)
	{
		_framerateText.NativeDraw(windowReference);
		_playerHealthGauge.NativeDraw(windowReference);
		_playerLifeIcon.NativeDraw(windowReference);
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

			_playerHealthGauge.UpdatValue(healthComponent.GetCurrentHealth(), healthComponent.GetMaxHealth());
		}
	}

	void GameplayHUD::PlayerSpaceshipDestroyed(Actor* actor)
	{
		RefreshHealthBar();
		_playerHealthGauge.SetForegroundColor(_healthGoodColor);
	}
}