#pragma once

#include "framework/Core.h"
#include <box2d/b2_world.h>

namespace rn
{
	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Get();

	protected:
		PhysicsSystem();

	private:
		static unique<PhysicsSystem> _physicsSystem;
		b2World _physicsWorld;
		float _physicsScale;
	};
}