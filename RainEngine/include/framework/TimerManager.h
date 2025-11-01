#pragma once

#include <functional>
#include "framework/Core.h"
#include "framework/Object.h"

namespace rn
{
	struct TimerHandle
	{
	public:
		TimerHandle();
		unsigned int GetTimerKey() const { return _timerKey; }

	private:
		unsigned int _timerKey;
		static unsigned int _timerKeyCounter;
		static unsigned int GetNextTimerKey() { return ++_timerKeyCounter; }
	};

	struct TimerHandleHashFunction
	{
	public:
		std::size_t operator()(const TimerHandle& timerHandle) const
		{
			return timerHandle.GetTimerKey();
		}
	};

	bool operator==(const TimerHandle& left, const TimerHandle& right);

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
		TimerHandle SetTimer(weak<Object> weakReference, void(ClassName::* callback)(), float duration, bool repeat = false)
		{
			TimerHandle newHandle{};
			_timers.insert(
			{
				newHandle, // Key
				Timer { weakReference, [=] { (static_cast<ClassName*>(weakReference.lock().get())->*callback)(); }, duration, repeat } // Value
			});

			return newHandle;
		}

		void UpdateTimer(float deltaTime);
		void ClearTimer(TimerHandle timerHandle);
		
	protected:
		TimerManager();

	private:
		static unique<TimerManager> _timerManager;

		Dictionary<TimerHandle, Timer, TimerHandleHashFunction> _timers;
	};
}