#pragma once

#include <SFML/Graphics.hpp>
#include <framework/Core.h>

namespace rn
{
	class World;

	class Application
	{
	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, std::uint32_t style);
		
		void Run();

		template<typename WorldType>
		weak<WorldType> LoadWorld();

		sf::Vector2u GetWindowSize() const;

		sf::RenderWindow& GetWindow() { return _mainWindow; }
		const sf::RenderWindow& GetWindow() const { return _mainWindow; }

	private:

		void TickInternal(float deltaTime);
		void RenderInternal();

		virtual void Render();
		virtual void Tick(float deltaTime);

		bool DispatchEvent(const sf::Event& ev);

	private:
		sf::RenderWindow _mainWindow;
		float _targetFrameRate;
		sf::Clock _tickClock;

		sf::Clock _cleanCycleClock;
		float _cleanCycleInterval;

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