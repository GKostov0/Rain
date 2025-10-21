#pragma once

#include <SFML/Graphics.hpp>

namespace rn
{
	class Application
	{
	public:
		Application();
		
		void Run();

	private:

		void TickInternal(float deltaTime);
		void RenderInternal();

		virtual void Render();
		virtual void Tick(float deltaTime);

		sf::RenderWindow _mainWindow;
		float _targetFrameRate;
		sf::Clock _tickClock;
	};
}