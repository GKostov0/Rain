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
		_pendingDestroy = true;
	}
}