#include "gameplay/WaitStage.h"

#include "framework/TimerManager.h"

namespace rn
{
	WaitStage::WaitStage(World* owner, float waitDuration)
		: GameStage{ owner },
		_waitDuration{waitDuration}
	{
	}

	void WaitStage::StartStage()
	{
		TimerManager::Get().SetTimer(GetWeakReference(), &WaitStage::FinishStage, _waitDuration);
	}
}