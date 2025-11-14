#pragma once

#include "framework/World.h"

namespace rn
{
	class MainMenuHUD;

	class MainMenuLevel : public World
	{
	public:
		MainMenuLevel(Application* owner);
		
		virtual void BeginPlay() override;

	private:
		weak<MainMenuHUD> _mainMenuHUD;

		void StartGame();
		void QuitGame();
	};
}