#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace rn
{
	class Actor;
	class Application;

	class World
	{
	public:
		World(Application* owner);
		virtual ~World();

		void BeginPlayInternal();
		void TickInternal(float deltaTime);

		void Render(sf::RenderWindow& window);

		template<typename A>
		weak<A> SpawnActor();

	private:

		void BeginPlay();
		void Tick(float deltaTime);

		Application* _owner;
		bool _beginPlay;

		List<shared<Actor>> _actors;
		List<shared<Actor>> _pendingActors;
	};

	template<typename A>
	weak<A> World::SpawnActor()
	{
		shared<A> newActor{ new A{this} };
		_pendingActors.push_back(newActor);
		return newActor;
	}
}