#include "framework/MathUtility.h"
#include "framework/World.h"

#include "Enemy/UFO.h"
#include "Enemy/UFOStage.h"
#include "weapon/BulletShooter.h"

namespace rn
{
	UFOStage::UFOStage(World* owner)
		: GameStage{owner},
		_spawnInterval{4.0f},
		_spawnAmount{10},
		_currentSpawnAmount{0},
		_ufoSpeed{200.0f}
	{
	}

	void UFOStage::StartStage()
	{
		_spawnTimer = TimerManager::Get().SetTimer(GetWeakReference(), &UFOStage::SpawnUFO, _spawnInterval, true);
	}

	void UFOStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(_spawnTimer);
	}

	void UFOStage::SpawnUFO()
	{
		sf::Vector2f spawnLocation = GetRandomSpawnLocation();
		auto windowSize = GetWorld()->GetWindowSize();
		sf::Vector2f center{ windowSize.x / 2.0f, windowSize.y / 2.0f };
		sf::Vector2f spawnLocationToCenter{ center.x - spawnLocation.x, center.y - spawnLocation.y };
		Normalize(spawnLocationToCenter);

		sf::Vector2f spawnVelocity = spawnLocationToCenter * _ufoSpeed;

		weak<UFO> newUFO = GetWorld()->SpawnActor<UFO>(spawnVelocity);
		newUFO.lock()->SetActorLocation(spawnLocation);

		if (++_currentSpawnAmount == _spawnAmount)
		{
			FinishStage();
		}
	}

	sf::Vector2f UFOStage::GetRandomSpawnLocation() const
	{
		auto windowSize = GetWorld()->GetWindowSize();

		float spawnLeft = RandomRange(-1, 1);

		float spawnLocationX = spawnLeft < 0 ? windowSize.x + 100.0f : -100.0f;
		float spawnLocationY = RandomRange(0, windowSize.y);

		return sf::Vector2f{ spawnLocationX , spawnLocationY };
	}
}