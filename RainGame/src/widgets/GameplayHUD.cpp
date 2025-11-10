#include "widgets/GameplayHUD.h"

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
		_playerHealthGauge.SetWidgetLocation({10.0f, windowSize.y - 30.0f});
		_playerHealthGauge.UpdatValue(100.0f, 250.0f);
	}
}