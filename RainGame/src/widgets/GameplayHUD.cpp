#include "framework/Actor.h"
#include "widgets/GameplayHUD.h"

#include "Player/Player.h"
#include "Player/PlayerManager.h"
#include "Player/PlayerSpaceship.h"

namespace rn
{
	GameplayHUD::GameplayHUD()
		: _framerateText{"FPS:"},
		_playerHealthGauge{}
	{
		_framerateText.SetTextSize(20);
	}

	void GameplayHUD::Draw(sf::RenderWindow& windowReference)
	{
		_framerateText.NativeDraw(windowReference);
		_playerHealthGauge.NativeDraw(windowReference);
	}

	void GameplayHUD::Tick(float deltaTime)
	{
		int framerate = int(1 / deltaTime);
		std::string fps = "FPS: " + std::to_string(framerate);
		_framerateText.SetString(fps);
	}

	void GameplayHUD::Initialize(const sf::RenderWindow& windowReference)
	{
		auto windowSize = windowReference.getSize();
		_playerHealthGauge.SetWidgetLocation({10.0f, windowSize.y - 50.0f});

		RefreshHealthBar();
	}

	void GameplayHUD::PlayerHealthUpdated(float amount, float currentHealth, float maxHealth)
	{
		_playerHealthGauge.UpdatValue(currentHealth, maxHealth);
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
	}
}