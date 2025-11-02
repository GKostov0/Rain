#include "Enemy/Vanguard.h"
#include "Enemy/VanguardStage.h"

#include "framework/World.h"

namespace rn
{
	VanguardStage::VanguardStage(World* owner)
		: GameStage{ owner },
		_spawnInterval{ 1.2f },
		_switchInterval{2.0f},
		_spawnDistanceToEdge{ 100.0f },
		_leftSpawnLocation{},
		_rightSpawnLocation{},
		_spawnLocation{},
		_rowsToSpawn{ 2 },
		_rowSpawnCount{},
		_vanguardPerRow{ 5 },
		_currentRowVanguardCount{}
	{
	}

	void VanguardStage::StartStage()
	{
		auto windowSize = GetWorld()->GetWindowSize();

		_leftSpawnLocation = sf::Vector2f{ _spawnDistanceToEdge, -100.0f };
		_rightSpawnLocation = sf::Vector2f{ windowSize.x - _spawnDistanceToEdge, -100.0f };

		SwitchRow();
	}

	void VanguardStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(_spawnTimerHandle);
		TimerManager::Get().ClearTimer(_switchTimerHandle);
	}

	void VanguardStage::SpawnVanguard()
	{
		weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
		newVanguard.lock()->SetActorLocation(_spawnLocation);
		++_currentRowVanguardCount;

		if (_currentRowVanguardCount == _vanguardPerRow)
		{
			TimerManager::Get().ClearTimer(_spawnTimerHandle);
			_switchTimerHandle = TimerManager::Get().SetTimer(GetWeakReference(), &VanguardStage::SwitchRow, _switchInterval, false);
			_currentRowVanguardCount = 0;
		}
	}

	void VanguardStage::SwitchRow()
	{
		if (_rowSpawnCount == _rowsToSpawn)
		{
			FinishStage();
			return;
		}

		_spawnLocation = _spawnLocation == _leftSpawnLocation ? _rightSpawnLocation : _leftSpawnLocation;

		_spawnTimerHandle = TimerManager::Get().SetTimer(GetWeakReference(), &VanguardStage::SpawnVanguard, _spawnInterval, true);
		++_rowSpawnCount;
	}
}