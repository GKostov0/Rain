#pragma once

#include <functional>
#include "framework/Core.h"
#include "framework/Object.h"

namespace rn
{
	struct Timer
	{
	public:
		Timer(weak<Object> weakReference, std::function<void()> callback, float duration, bool repeat);
		void TickTime(float deltaTime);
		bool Expired() const;
		void SetExpired();

	private:
		std::pair<weak<Object>, std::function<void()>> _listener;
		
		float _duration;
		bool _repeat;

		float _counter;
		bool _isExpired;
	};

	class TimerManager
	{
	public:
		static TimerManager& Get();

		template<typename ClassName>
		void SetTimer(weak<Object> weakReference, void(ClassName::* callback)(), float duration, bool repeat = false)
		{
			_timers.push_back(Timer{ weakReference, [=] { (static_cast<ClassName*>(weakReference.lock().get())->*callback)(); }, duration, repeat });
		}

		void UpdateTimer(float deltaTime);
		
	protected:
		TimerManager();

	private:
		static unique<TimerManager> _timerManager;

		List<Timer> _timers;
	};
}