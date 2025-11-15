#pragma once
#include <SFML/Graphics.hpp>

#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace rn
{
	class ChaosStage : public GameStage
	{
	public:
		ChaosStage(World* owner);

		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;

		void SpawnTwinBlade();
		void SpawnVanguard();
		void SpawnHexagon();
		void SpawnUFO();

		void IncreaseDifficulty();
		void StageDurationReached();

	private:
		sf::Vector2f GetRandomSpawnLocationTop() const;
		sf::Vector2f GetRandomSpawnLocationSide() const;

		float _spawnInterval;
		float _minSpawnInterval;

		float _spawnIntervalDecrement;
		float _spawnIntervalDecrementInterval;

		float _stageDuration;

		TimerHandle _difficultyTimer;
		TimerHandle _spawnTimer;
	};
}