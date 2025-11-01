#pragma once

#include <SFML/Graphics.hpp>

#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"

namespace rn
{
	class VanguardStage : public GameStage
	{
	public:
		VanguardStage(World* owner);

		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;
		void SpawnVanguard();
		void SwitchRow();

	private:
		float _spawnInterval;
		float _switchInterval;
		float _spawnDistanceToEdge;

		sf::Vector2f _leftSpawnLocation;
		sf::Vector2f _rightSpawnLocation;
		sf::Vector2f _spawnLocation;

		TimerHandle _spawnTimerHandle;
		TimerHandle _switchTimerHandle;

		int _rowsToSpawn;
		int _rowSpawnCount;

		int _vanguardPerRow;
		int _currentRowVanguardCount;
	};
}