#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "gameplay/GameStage.h"

namespace rn
{
	World::World(Application* owner)
		: _owner{ owner }, _beginPlay{false},
			_pendingActors{}, _actors{}, _currentStageIndex{-1},
				_gameStages{}
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
			NextGameStage();
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

		if (_currentStageIndex >= 0 && _currentStageIndex < _gameStages.size())
		{
			_gameStages[_currentStageIndex]->TickStage(deltaTime);
		}

		Tick(deltaTime);
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto& actor : _actors)
		{
			actor->Render(window);
		}
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

		for (auto it = _gameStages.begin(); it != _gameStages.end();)
		{
			if (it->get()->IsStageFinished())
			{
				it = _gameStages.erase(it);
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

	void World::InitGameStages()
	{

	}

	void World::AllGameStageFinished()
	{

	}

	void World::NextGameStage()
	{
		++_currentStageIndex;
		if (_currentStageIndex >= 0 && _currentStageIndex < _gameStages.size())
		{
			_gameStages[_currentStageIndex]->onStageFinished.BindAction(GetWeakReference(), &World::NextGameStage);
			_gameStages[_currentStageIndex]->StartStage();
		}
		else
		{
			AllGameStageFinished();
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