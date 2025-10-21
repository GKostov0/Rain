#pragma once

#include <SFML/Graphics.hpp>
#include <framework/Core.h>

namespace rn
{
	class World;

	class Application
	{
	public:
		Application();
		
		void Run();

		template<typename WorldType>
		weak<WorldType> LoadWorld();

	private:

		void TickInternal(float deltaTime);
		void RenderInternal();

		virtual void Render();
		virtual void Tick(float deltaTime);

		sf::RenderWindow _mainWindow;
		float _targetFrameRate;
		sf::Clock _tickClock;

		shared<World> _currentWorld;
	};

	template<typename WorldType>
	weak<WorldType> Application::LoadWorld()
	{
		shared<WorldType> newWorld{ new WorldType{this} };
		_currentWorld = newWorld;
		return newWorld;
	}
}