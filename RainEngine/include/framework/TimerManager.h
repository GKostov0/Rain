#pragma once

#include "framework/Core.h"
#include "framework/Object.h"

namespace rn
{
	class TimerManager
	{
	public:
		static TimerManager& Get();

		template<typename ClassName>
		void SetTimer(weak<Object> weakReference, void(ClassName::* callback)(), float duration, bool repeat = false)
		{

		}
		
	protected:
		TimerManager();

	private:
		static unique<TimerManager> _timerManager;
	};
}