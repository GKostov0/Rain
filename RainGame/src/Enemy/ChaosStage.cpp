#include "Enemy/ChaosStage.h"

#include "Enemy/TwinBlade.h"
#include "Enemy/Hexagon.h"
#include "Enemy/Vanguard.h"
#include "Enemy/UFO.h"

#include "framework/MathUtility.h"
#include "framework/World.h"

namespace rn
{
	ChaosStage::ChaosStage(World* owner)
		: GameStage{owner},
		_spawnInterval{4.0f},
		_minSpawnInterval{0.8f},
		_spawnIntervalDecrement{0.5f},
		_spawnIntervalDecrementInterval{5.0f},
		_stageDuration{60.0f}
	{
	}

	void ChaosStage::StartStage()
	{
		_spawnTimer = TimerManager::Get().SetTimer(GetWeakReference(), &ChaosStage::SpawnTwinBlade, _spawnInterval);
		_difficultyTimer = TimerManager::Get().SetTimer(GetWeakReference(), &ChaosStage::IncreaseDifficulty, _spawnIntervalDecrementInterval, true);
		TimerManager::Get().SetTimer(GetWeakReference(), &ChaosStage::StageDurationReached, _stageDuration);
	}

	void ChaosStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(_spawnTimer);
		TimerManager::Get().ClearTimer(_difficultyTimer);
	}

	void ChaosStage::SpawnTwinBlade()
	{
		weak<TwinBlade> enemy = GetWorld()->SpawnActor<TwinBlade>();
		enemy.lock()->SetActorLocation(GetRandomSpawnLocationTop());
		_spawnTimer = TimerManager::Get().SetTimer(GetWeakReference(), &ChaosStage::SpawnVanguard, _spawnInterval);
	}

	void ChaosStage::SpawnVanguard()
	{
		weak<Vanguard> enemy = GetWorld()->SpawnActor<Vanguard>();
		enemy.lock()->SetActorLocation(GetRandomSpawnLocationTop());
		_spawnTimer = TimerManager::Get().SetTimer(GetWeakReference(), &ChaosStage::SpawnHexagon, _spawnInterval);
	}

	void ChaosStage::SpawnHexagon()
	{
		weak<Hexagon> enemy = GetWorld()->SpawnActor<Hexagon>();
		enemy.lock()->SetActorLocation(GetRandomSpawnLocationTop());
		_spawnTimer = TimerManager::Get().SetTimer(GetWeakReference(), &ChaosStage::SpawnUFO, _spawnInterval);
	}

	void ChaosStage::SpawnUFO()
	{
		sf::Vector2f spawnLocation = GetRandomSpawnLocationSide();

		auto windowSize = GetWorld()->GetWindowSize();
		sf::Vector2f center = { windowSize.x / 2.0f, windowSize.y / 2.0f };

		sf::Vector2f directionToCenter = center - spawnLocation;
		Normalize(directionToCenter);

		weak<UFO> enemy = GetWorld()->SpawnActor<UFO>(directionToCenter * 200.0f);
		enemy.lock()->SetActorLocation(spawnLocation);

		_spawnTimer = TimerManager::Get().SetTimer(GetWeakReference(), &ChaosStage::SpawnTwinBlade, _spawnInterval);
	}

	void ChaosStage::IncreaseDifficulty()
	{
		_spawnInterval -= _spawnIntervalDecrement;

		if (_spawnInterval < _minSpawnInterval)
		{
			_spawnInterval = _minSpawnInterval;
		}
	}

	void ChaosStage::StageDurationReached()
	{
		FinishStage();
	}

	sf::Vector2f ChaosStage::GetRandomSpawnLocationTop() const
	{
		auto windowSize = GetWorld()->GetWindowSize();

		float spawnX = RandomRange(100.0f, windowSize.x - 100.0f);
		float spawnY = -100.0f;

		return { spawnX, spawnY };
	}

	sf::Vector2f ChaosStage::GetRandomSpawnLocationSide() const
	{
		auto windowSize = GetWorld()->GetWindowSize();

		bool spawnLeft = RandomRange(-1, 1);

		float spawnX = spawnLeft ? -100.0f : windowSize.x + 100.0f;
		float spanwY = RandomRange(0, windowSize.y);

		return { spawnX, spanwY };
	}
}