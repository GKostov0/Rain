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
		unsigned int SetTimer(weak<Object> weakReference, void(ClassName::* callback)(), float duration, bool repeat = false)
		{
			++_timerIndexCounter;
			_timers.insert(
				{
					_timerIndexCounter, // Key
					Timer { weakReference, [=] { (static_cast<ClassName*>(weakReference.lock().get())->*callback)(); }, duration, repeat } // Value
				});

			return _timerIndexCounter;
		}

		void UpdateTimer(float deltaTime);
		void ClearTimer(unsigned int timerIndex);
		
	protected:
		TimerManager();

	private:
		static unique<TimerManager> _timerManager;
		static unsigned int _timerIndexCounter;

		Dictionary<unsigned int, Timer> _timers;
	};
}