#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "gameplay/GameStage.h"
#include "widgets/HUD.h"

namespace rn
{
	World::World(Application* owner)
		: _owner{ owner },
		_beginPlay{false},
		_pendingActors{},
		_actors{},
		_gameStages{},
		_currentStage{_gameStages.end()}
	{
	}

	World::~World()
	{
	}

	void World::BeginPlayInternal()
	{
		if (!_beginPlay)
		{
			_beginPlay = true;
			BeginPlay();
			InitGameStages();
			StartStagets();
		}
	}

	void World::TickInternal(float deltaTime)
	{
		for (shared<Actor> actor : _pendingActors)
		{
			_actors.push_back(actor);
			actor->BeginPlayInternal();
		}
		_pendingActors.clear();

		for (auto it = _actors.begin(); it != _actors.end();)
		{
			it->get()->TickInternal(deltaTime);
			++it;
		}

		if (_currentStage != _gameStages.end())
		{
			_currentStage->get()->TickStage(deltaTime);
		}

		Tick(deltaTime);

		if (_hud)
		{
			if (!_hud->IsInit())
			{
				_hud->NativeInitialize(_owner->GetWindow());
			}

			_hud->Tick(deltaTime);
		}
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto& actor : _actors)
		{
			actor->Render(window);
		}

		RenderHUD(window);
	}

	sf::Vector2u World::GetWindowSize() const
	{
		return _owner->GetWindowSize();
	}

	void World::CleanCycle()
	{
		for (auto it = _actors.begin(); it != _actors.end();)
		{
			if (it->get()->IsPendingDestroy())
			{
				it = _actors.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void World::AddStage(const shared<GameStage>& newStage)
	{
		_gameStages.push_back(newStage);
	}

	bool World::DispatchEvent(const sf::Event& ev)
	{
		if (_hud)
		{
			return _hud->HandleEvent(ev);
		}
		return false;
	}

	void World::InitGameStages()
	{

	}

	void World::AllGameStageFinished()
	{
		LOG("All stages Finished!");
	}

	void World::RenderHUD(sf::RenderWindow& window)
	{
		if (_hud)
		{
			_hud->Draw(window);
		}
	}

	void World::NextGameStage()
	{
		_currentStage = _gameStages.erase(_currentStage);

		if (_currentStage != _gameStages.end())
		{
			_currentStage->get()->StartStage();
			_currentStage->get()->onStageFinished.BindAction(GetWeakReference(), &World::NextGameStage);
		}
		else
		{
			AllGameStageFinished();
		}
	}

	void World::StartStagets()
	{
		_currentStage = _gameStages.begin();

		if (_currentStage != _gameStages.end())
		{
			_currentStage->get()->StartStage();
			_currentStage->get()->onStageFinished.BindAction(GetWeakReference(), &World::NextGameStage);
		}
	}

	void World::BeginPlay()
	{
		LOG("Begin play...");
	}

	void World::Tick(float deltaTime)
	{
	}
}