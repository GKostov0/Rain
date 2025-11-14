#include "Level/MainMenuLevel.h"
#include "widgets/MainMenuHUD.h"

namespace rn
{
	MainMenuLevel::MainMenuLevel(Application* owner)
		: World{owner}
	{
		_mainMenuHUD = SpawnHUD<MainMenuHUD>();
	}

	void MainMenuLevel::BeginPlay()
	{
		_mainMenuHUD.lock()->onStartButtonClicked.BindAction(GetWeakReference(), &MainMenuLevel::StartGame);
		_mainMenuHUD.lock()->onQuitButtonClicked.BindAction(GetWeakReference(), &MainMenuLevel::QuitGame);
	}

	void MainMenuLevel::StartGame()
	{
		LOG("Start Game!");
	}

	void MainMenuLevel::QuitGame()
	{
		LOG("Quit Game!");
	}
}