#pragma once
#include <functional>

#include "framework/Core.h"

namespace rn
{
	class Object;

	template<typename... Args>
	class Delegate
	{
	public:
		template<typename ClassName>
		void BindAction(weak<Object> obj, void (ClassName::* callback)(Args...))
		{
			std::function<bool(Args...)> callbackFunc = [obj, callback](Args... args)->bool
			{
				if (!obj.expired())
				{
					(static_cast<ClassName*>(obj.lock().get())->*callback)(args...);
					return true;
				}
				return false;
			};

			_callbacks.push_back(callbackFunc);
		}

		void Broadcast(Args... args)
		{
			for (auto it = _callbacks.begin(); it != _callbacks.end();)
			{
				if ((*it)(args...))
				{
					++it;
				}
				else
				{
					it = _callbacks.erase(it);
				}
			}
		}

	private:
		List<std::function<bool(Args...)>> _callbacks;
	};
}