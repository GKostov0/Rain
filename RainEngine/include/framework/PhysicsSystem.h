#pragma once

#include "framework/Core.h"
#include <box2d/b2_world.h>

namespace rn
{
	class Actor;

	class PhysicsContactListener : public b2ContactListener
	{
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;
	};

	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Get();

		void Step(float deltaTime);

		b2Body* AddListener(Actor* listener);
		void RemoveListener(b2Body* remove);

		float GetPhysicsScale() const { return _physicsScale; }

		static void Cleanup();

	protected:
		PhysicsSystem();

		void ProcessPendingRemoveListeners();

	private:
		static unique<PhysicsSystem> _physicsSystem;
		b2World _physicsWorld;
		float _physicsScale;

		int _velocityIterations;
		int _positionIterations;

		PhysicsContactListener _contactListener;

		Set<b2Body*> _pendingReoveListeners;
	};
}