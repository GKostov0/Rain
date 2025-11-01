#include "framework/TimerManager.h"

namespace rn
{
	unique<TimerManager> TimerManager::_timerManager{ nullptr };

	TimerManager::TimerManager() { }

	TimerManager& TimerManager::Get()
	{
		if (!_timerManager)
		{
			_timerManager = std::move(unique<TimerManager>{ new TimerManager{} });
		}

		return *_timerManager;
	}
}