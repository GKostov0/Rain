#pragma once

#include <SFML/Graphics.hpp>

#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"

namespace rn
{
	class HexagonStage : public GameStage
	{
	public:
		HexagonStage(World* owner);

		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;
		void SpawnHexagon();

	private:
		float _spawnInterval;
		float _sideSpawnOffset;

		int _spawnGroupAmount;
		int _currentSpawnCount;

		sf::Vector2f _leftSpawnLocation;
		sf::Vector2f _middleSpawnLocation;
		sf::Vector2f _rightSpawnLocation;

		TimerHandle _spawnTimer;
	};
}