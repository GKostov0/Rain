#pragma once

#include "framework/Core.h"
#include <box2d/b2_world.h>

namespace rn
{
	class Actor;

	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Get();

		void Step(float deltaTime);

		b2Body* AddListener(Actor* listener);

		float GetPhysicsScale() const { return _physicsScale; }

	protected:
		PhysicsSystem();

	private:
		static unique<PhysicsSystem> _physicsSystem;
		b2World _physicsWorld;
		float _physicsScale;

		int _velocityIterations;
		int _positionIterations;
	};
}