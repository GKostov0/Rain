#include "Enemy/BossStage.h"
#include "Enemy/Boss.h"
#include "framework/World.h"

namespace rn
{
	BossStage::BossStage(World* world)
		: GameStage{world}
	{
	}

	void BossStage::StartStage()
	{
		auto windowSize = GetWorld()->GetWindowSize();

		weak<Boss> boss = GetWorld()->SpawnActor<Boss>();
		boss.lock()->SetActorLocation({windowSize.x / 2.0f, 200.0f});
		boss.lock()->onActorDestroy.BindAction(GetWeakReference(), &BossStage::BossDestroyed);
	}

	void BossStage::BossDestroyed(Actor* bossActor)
	{
		FinishStage();
	}
}