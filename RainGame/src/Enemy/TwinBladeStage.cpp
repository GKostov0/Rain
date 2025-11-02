#include "Enemy/TwinBladeStage.h"
#include "Enemy/TwinBlade.h"

#include "framework/World.h"

namespace rn
{
	TwinBladeStage::TwinBladeStage(World* owner)
		: GameStage{ owner },
		_spawnInterval{ 1.5f },
		_spawnDistanceToCenter{100.0f},
		_leftSpawnLocation{ owner->GetWindowSize().x / 2.0f - _spawnDistanceToCenter, -100.0f },
		_rightSpawnLocation{owner->GetWindowSize().x / 2.0f + _spawnDistanceToCenter, - 100.0f},
		_spawnLocation{_leftSpawnLocation},
		_spawnAmount{ 10 },
		_currentSpawnCount{0}
	{
	}

	void TwinBladeStage::StartStage()
	{
		_spawnTimerHandle = TimerManager::Get().SetTimer(GetWeakReference(), &TwinBladeStage::SpawnTwinBlade, _spawnInterval, true);
	}

	void TwinBladeStage::SpawnTwinBlade()
	{
		weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
		newTwinBlade.lock()->SetActorLocation(_spawnLocation);

		_spawnLocation = _spawnLocation == _leftSpawnLocation ? _rightSpawnLocation : _leftSpawnLocation;

		++_currentSpawnCount;

		if (_currentSpawnCount == _spawnAmount)
		{
			FinishStage();
		}
	}

	void TwinBladeStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(_spawnTimerHandle);
	}
}