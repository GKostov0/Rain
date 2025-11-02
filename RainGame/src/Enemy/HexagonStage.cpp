#include "Enemy/HexagonStage.h"
#include "framework/World.h"
#include "Enemy/Hexagon.h"

namespace rn
{
	HexagonStage::HexagonStage(World* owner)
		: GameStage{owner},
		_spawnInterval{5.0f},
		_sideSpawnOffset{80.0f},
		_spawnGroupAmount{5},
		_currentSpawnCount{0},
		_leftSpawnLocation{ GetWorld()->GetWindowSize().x / 2.0f - _sideSpawnOffset, -100.0f - _sideSpawnOffset },
		_middleSpawnLocation{GetWorld()->GetWindowSize().x / 2.0f, -100.0f},
		_rightSpawnLocation{ GetWorld()->GetWindowSize().x / 2.0f + _sideSpawnOffset, -100.0f - _sideSpawnOffset }
	{

	}

	void HexagonStage::StartStage()
	{
		_spawnTimer = TimerManager::Get().SetTimer(GetWeakReference(), &HexagonStage::SpawnHexagon, _spawnInterval, true);
	}

	void HexagonStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(_spawnTimer);
	}

	void HexagonStage::SpawnHexagon()
	{
		weak<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(_leftSpawnLocation);

		newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(_middleSpawnLocation);

		newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(_rightSpawnLocation);

		if (++_currentSpawnCount == _spawnGroupAmount)
		{
			FinishStage();
		}
	}
}