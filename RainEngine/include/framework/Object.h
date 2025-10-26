#pragma once

#include <memory>
#include "framework/Core.h"
#include "framework/Delegate.h"

namespace rn
{
	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object();
		virtual ~Object();

		bool IsPendingDestroy() const { return _pendingDestroy; }

		virtual void Destroy();

		weak<Object> GetWeakReference();
		weak<const Object> GetWeakReference() const;

		Delegate<Object*> onDestroy;

	private:
		bool _pendingDestroy;
	};
}