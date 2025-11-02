#pragma once
#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Object.h"

namespace rn
{
	class Actor;
	class Application;
	class GameStage;

	class World : public Object
	{
	public:
		World(Application* owner);
		virtual ~World();

		void BeginPlayInternal();
		void TickInternal(float deltaTime);

		void Render(sf::RenderWindow& window);

		template<typename A, typename... Args>
		weak<A> SpawnActor(Args... args);

		sf::Vector2u GetWindowSize() const;

		void CleanCycle();

		void AddStage(const shared<GameStage>& newStage);

	private:
		virtual void InitGameStages();
		virtual void AllGameStageFinished();
		void NextGameStage();
		void StartStagets();

	private:

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

		Application* _owner;
		bool _beginPlay;

		List<shared<Actor>> _actors;
		List<shared<Actor>> _pendingActors;
		List<shared<GameStage>> _gameStages;

		List<shared<GameStage>>::iterator _currentStage;
	};

	template<typename A, typename... Args>
	weak<A> World::SpawnActor(Args... args)
	{
		shared<A> newActor{ new A(this, args...) };
		_pendingActors.push_back(newActor);
		return newActor;
	}
}