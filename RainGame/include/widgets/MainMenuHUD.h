#pragma once

#include "widgets/HUD.h"
#include "widgets/Button.h"
#include "widgets/TextWidget.h"

namespace rn
{
	class MainMenuHUD : public HUD
	{
	public:
		MainMenuHUD();

		virtual void Draw(sf::RenderWindow& windowReference) override;
		virtual bool HandleEvent(const sf::Event& ev) override;

		Delegate<> onStartButtonClicked;
		Delegate<> onQuitButtonClicked;

	private:
		virtual void Initialize(const sf::RenderWindow& windowReference) override;
		
		void StartButtonClicked();
		void QuitButtonClicked();

	private:
		TextWidget _titleText;
		Button _startButton;
		Button _quitButton;
	};
}