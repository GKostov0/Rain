#include <iostream>
#include "framework/Application.h"

namespace rn
{
	Application::Application()
		: _mainWindow{ sf::VideoMode({ 800, 600 }), "Rain" },
        _targetFrameRate{ 60.0f }, _tickClock{}
	{
	}

	void Application::Run()
	{
        _tickClock.restart();
        
        float accumulatedTime = 0.0f;
        float targetDeltaTime = 1.0f / _targetFrameRate;

        while (_mainWindow.isOpen())
        {
            while (const std::optional wndowEvent = _mainWindow.pollEvent())
            {
                if (wndowEvent->is<sf::Event::Closed>())
                {
                    _mainWindow.close();
                }
                else if (const auto* keyPressed = wndowEvent->getIf<sf::Event::KeyPressed>())
                {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                        _mainWindow.close();
                }
            }

            float frameDeltaTime = _tickClock.restart().asSeconds();
            accumulatedTime += frameDeltaTime;
            while (accumulatedTime > targetDeltaTime)
            {
                accumulatedTime -= targetDeltaTime;
                TickInternal(targetDeltaTime);
                RenderInternal();
            }

            std::cout << "Ticking at framerate: " << 1.0f / frameDeltaTime << std::endl;
        }
	}

    void Application::TickInternal(float deltaTime)
    {
        Tick(deltaTime);
    }

    void Application::RenderInternal()
    {
        _mainWindow.clear();

        Render();
        
        _mainWindow.display();
    }

    void Application::Render()
    {
        sf::RectangleShape rect{ sf::Vector2f{100, 100} };
        rect.setFillColor(sf::Color::Cyan);
        _mainWindow.draw(rect);
    }

    void Application::Tick(float deltaTime)
    {
    }
}