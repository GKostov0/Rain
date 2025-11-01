#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/PhysicsSystem.h"
#include "framework/TimerManager.h"

namespace rn
{
    Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, std::uint32_t style)
        : _mainWindow{ sf::VideoMode({ windowWidth, windowHeight }), title, style },
            _targetFrameRate{ 60.0f }, _tickClock{}, _currentWorld{ nullptr },
                _cleanCycleClock{}, _cleanCycleInterval{3.0f}
    {

    }

	void Application::Run()
	{
        _tickClock.restart();
        
        float accumulatedTime = 0.0f;
        float targetDeltaTime = 1.0f / _targetFrameRate;

        while (_mainWindow.isOpen())
        {
            sf::Event windowEvent;
            while (_mainWindow.pollEvent(windowEvent))
            {
                if (windowEvent.type == sf::Event::EventType::Closed)
                {
                    _mainWindow.close();
                }
                else if (windowEvent.type == sf::Event::KeyPressed)
                {
                    if (windowEvent.key.code == sf::Keyboard::Escape)
                    {
                        _mainWindow.close();
                    }
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

    sf::Vector2u Application::GetWindowSize() const
    {
        return _mainWindow.getSize();
    }

    void Application::TickInternal(float deltaTime)
    {
        Tick(deltaTime);

        if (_currentWorld)
        {
            _currentWorld->BeginPlayInternal();
            _currentWorld->TickInternal(deltaTime);
        }

        TimerManager::Get().UpdateTimer(deltaTime);

        PhysicsSystem::Get().Step(deltaTime);

        if (_cleanCycleClock.getElapsedTime().asSeconds() >= _cleanCycleInterval)
        {
            // TODO: make the asset manager handle it's own cleaning and the world too!
            _cleanCycleClock.restart();
            AssetManager::Get().CleanCycle();
            if (_currentWorld)
            {
                _currentWorld->CleanCycle();
            }
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