#include "Level/MainMenuLevel.h"
#include "widgets/MainMenuHUD.h"

#include "framework/Application.h"
#include "framework/BackdropActor.h"
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
		SpawnActor<BackdropActor>("SpaceShooterRedux/mainMenuBg.png", sf::Vector2f{0.0f, 0.0f});
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