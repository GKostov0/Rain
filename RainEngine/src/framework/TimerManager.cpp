#include "framework/TimerManager.h"

namespace rn
{
	unique<TimerManager> TimerManager::_timerManager{ nullptr };
	unsigned int TimerHandle::_timerKeyCounter = 0;

	TimerManager::TimerManager()
		: _timers{}
	{
	}

	TimerManager& TimerManager::Get()
	{
		if (!_timerManager)
		{
			_timerManager = std::move(unique<TimerManager>{ new TimerManager{} });
		}

		return *_timerManager;
	}

	Timer::Timer(weak<Object> weakReference, std::function<void()> callback, float duration, bool repeat)
		: _listener{ weakReference, callback },
			_duration{ duration }, _repeat{ repeat },
				_counter{ 0.0f }, _isExpired{false} { }

	void TimerManager::UpdateTimer(float deltaTime)
	{
		for (auto it = _timers.begin(); it != _timers.end();)
		{
			if (it->second.Expired())
			{
				it = _timers.erase(it);
			}
			else
			{
				it->second.TickTime(deltaTime);
				++it;
			}
		}
	}

	void TimerManager::ClearTimer(TimerHandle timerHandle)
	{
		auto it = _timers.find(timerHandle);
		if (it != _timers.end())
		{
			it->second.SetExpired();
		}
	}

	void Timer::TickTime(float deltaTime)
	{
		if (Expired())
			return;

		_counter += deltaTime;

		if (_counter >= _duration)
		{
			_listener.second();

			if (_repeat)
			{
				_counter = 0.0f;
			}
			else
			{
				SetExpired();
			}
		}
	}

	bool Timer::Expired() const
	{
		return _isExpired || _listener.first.expired() || _listener.first.lock()->IsPendingDestroy();
	}

	void Timer::SetExpired()
	{
		_isExpired = true;
	}

	TimerHandle::TimerHandle()
		: _timerKey{ GetNextTimerKey() }
	{
	}

	bool operator==(const TimerHandle& left, const TimerHandle& right)
	{
		return left.GetTimerKey() == right.GetTimerKey();
	}
}