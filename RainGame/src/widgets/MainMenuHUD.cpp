#include "widgets/MainMenuHUD.h"

namespace rn
{
	MainMenuHUD::MainMenuHUD()
		: _titleText{"Rain"},
		_startButton{"Start Game"},
		_quitButton{"Quit Game"}
	{
		_titleText.SetTextSize(40);
		_startButton.SetTextSize(20);
		_quitButton.SetTextSize(20);
	}

	void MainMenuHUD::Draw(sf::RenderWindow& windowReference)
	{
		_titleText.NativeDraw(windowReference);
		_startButton.NativeDraw(windowReference);
		_quitButton.NativeDraw(windowReference);
	}

	bool MainMenuHUD::HandleEvent(const sf::Event& ev)
	{
		return _startButton.HandleEvent(ev) || _quitButton.HandleEvent(ev) || HUD::HandleEvent(ev);
	}

	void MainMenuHUD::Initialize(const sf::RenderWindow& windowReference)
	{
		auto windowSize = windowReference.getSize();

		_titleText.SetWidgetLocation({ windowSize.x / 2.0f - _titleText.GetBound().width / 2.0f, 100.0f });
		_startButton.SetWidgetLocation({ windowSize.x / 2.0f - _startButton .GetBound().width / 2.0f, 400.0f});
		_quitButton.SetWidgetLocation(_startButton.GetWidgetLocation() + sf::Vector2f{ 0.0f, 100.0f });

		_startButton.onButtonClicked.BindAction(GetWeakReference(), &MainMenuHUD::StartButtonClicked);
		_quitButton.onButtonClicked.BindAction(GetWeakReference(), &MainMenuHUD::QuitButtonClicked);
	}

	void MainMenuHUD::StartButtonClicked()
	{
		onStartButtonClicked.Broadcast();
	}

	void MainMenuHUD::QuitButtonClicked()
	{
		onQuitButtonClicked.Broadcast();
	}
}