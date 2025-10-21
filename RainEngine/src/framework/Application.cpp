#include "framework/Application.h"
#include "framework/Core.h"
#include <framework/World.h>

namespace rn
{
    Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, std::uint32_t style)
        : _mainWindow{ sf::VideoMode({ windowWidth, windowHeight }), title, style },
        _targetFrameRate{ 60.0f }, _tickClock{}, _currentWorld{ nullptr }
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
        }
	}

    void Application::TickInternal(float deltaTime)
    {
        Tick(deltaTime);

        if (_currentWorld)
        {
            _currentWorld->BeginPlayInternal();
            _currentWorld->TickInternal(deltaTime);
        }
    }

    void Application::RenderInternal()
    {
        _mainWindow.clear();

        Render();
        
        _mainWindow.display();
    }

    void Application::Render()
    {
        _currentWorld->Render(_mainWindow);
    }

    void Application::Tick(float deltaTime)
    {
    }
}