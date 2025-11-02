#pragma once

#include <SFML/Graphics.hpp>
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"

namespace rn
{
	class UFOStage : public GameStage
	{
	public:
		UFOStage(World* owner);

		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;

		void SpawnUFO();

		sf::Vector2f GetRandomSpawnLocation() const;

	private:
		float _spawnInterval;
		float _ufoSpeed;

		int _spawnAmount;
		int _currentSpawnAmount;

		TimerHandle _spawnTimer;
	};
}