#include "Level/MainMenuLevel.h"
#include "widgets/MainMenuHUD.h"

#include "framework/Application.h"
#include "Level/GameLevelOne.h"

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
		GetApplication()->LoadWorld<GameLevelOne>();
	}

	void MainMenuLevel::QuitGame()
	{
		GetApplication()->QuitApplication();
	}
}