#include "widgets/GameplayHUD.h"

namespace rn
{
	GameplayHUD::GameplayHUD()
		: _framerateText{"FPS:"}
	{
		_framerateText.SetTextSize(20);
	}

	void GameplayHUD::Draw(sf::RenderWindow& windowReference)
	{
		_framerateText.NativeDraw(windowReference);
	}

	void GameplayHUD::Tick(float deltaTime)
	{
		int framerate = int(1 / deltaTime);
		std::string fps = "FPS: " + std::to_string(framerate);
		_framerateText.SetString(fps);
	}
}