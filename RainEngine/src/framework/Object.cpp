#include "framework/Object.h"
#include "framework/Core.h"

namespace rn
{
	unsigned int Object::_uniqueIdCounter = 0;

	Object::Object()
		: _pendingDestroy{false},
		_uniqueID{ GetNextAvailableID()}
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

	unsigned int Object::GetNextAvailableID()
	{
		return _uniqueIdCounter++;
	}
}