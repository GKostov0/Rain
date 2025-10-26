#include "framework/Object.h"
#include "framework/Core.h"

namespace rn
{
	Object::Object()
		: _pendingDestroy{false}
	{
	}

	Object::~Object()
	{
		LOG("Object Destroyed...");
	}

	void Object::Destroy()
	{
		onDestroy.Broadcast(this);
		_pendingDestroy = true;
	}

	weak<Object> Object::GetWeakReference()
	{
		return weak_from_this();
	}

	weak<const Object> Object::GetWeakReference() const
	{
		return weak_from_this();
	}
}