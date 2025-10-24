#include "framework/PhysicsSystem.h"

namespace rn
{
	unique<PhysicsSystem> PhysicsSystem::_physicsSystem{ nullptr };

	PhysicsSystem& PhysicsSystem::Get()
	{
		if (!_physicsSystem)
		{
			_physicsSystem = unique<PhysicsSystem>{ new PhysicsSystem };
		}

		return *_physicsSystem;
	}

	PhysicsSystem::PhysicsSystem()
		: _physicsWorld{ b2Vec2{0.0f,0.0f} }, _physicsScale{0.01f}
	{
	}
}