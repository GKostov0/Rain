#pragma once
#include <SFML/Graphics.hpp>

#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"

namespace rn
{
	class TwinBladeStage : public GameStage
	{
	public:
		TwinBladeStage(World* owner);

		virtual void StartStage() override;

	private:
		void SpawnTwinBlade();
		virtual void StageFinished() override;

	private:
		float _spawnInterval;
		float _spawnDistanceToCenter;

		sf::Vector2f _leftSpawnLocation;
		sf::Vector2f _rightSpawnLocation;
		sf::Vector2f _spawnLocation;

		int _spawnAmount;
		int _currentSpawnCount;

		TimerHandle _spawnTimerHandle;
	};
}