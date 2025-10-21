#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"

namespace rn
{
	World::World(Application* owner)
		: _owner{ owner }, _beginPlay{false},
		_pendingActors{}, _actors{}
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
			if (it->get()->IsPendingDestroy())
			{
				it = _actors.erase(it);
			}
			else
			{
				it->get()->TickInternal(deltaTime);
				++it;
			}
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

	void World::BeginPlay()
	{
		LOG("Begin play...");
	}

	void World::Tick(float deltaTime)
	{
		LOG("Tick at frame rate: %f", 1.0f / deltaTime);
	}
}