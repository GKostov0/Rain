#include <box2d/b2_body.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"

namespace rn
{
	unique<PhysicsSystem> PhysicsSystem::_physicsSystem{ nullptr };

	PhysicsSystem& PhysicsSystem::Get()
	{
		if (!_physicsSystem)
		{
			_physicsSystem = std::move(unique<PhysicsSystem>{ new PhysicsSystem });
		}

		return *_physicsSystem;
	}

	void PhysicsSystem::Step(float deltaTime)
	{
		ProcessPendingRemoveListeners();
		_physicsWorld.Step(deltaTime, _velocityIterations, _positionIterations);
	}

	b2Body* PhysicsSystem::AddListener(Actor* listener)
	{
		if (listener->IsPendingDestroy())
		{
			return nullptr;
		}

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;

		bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);

		bodyDef.position.Set(listener->GetActorLocation().x * GetPhysicsScale(), listener->GetActorLocation().y * GetPhysicsScale());
		bodyDef.angle = DegreesToRadians(listener->GetActorRotation());

		b2Body* body = _physicsWorld.CreateBody(&bodyDef);

		b2PolygonShape shape;
		sf::FloatRect bounds = listener->GetActorGlobalBounds();

		shape.SetAsBox(bounds.width / 2.0f * GetPhysicsScale(), bounds.height / 2.0f * GetPhysicsScale());

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;

		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.isSensor = true;

		body->CreateFixture(&fixtureDef);

		return body;
	}

	void PhysicsSystem::RemoveListener(b2Body* remove)
	{
		_pendingReoveListeners.insert(remove);
	}

	void PhysicsSystem::Cleanup()
	{
		_physicsSystem = std::move(unique<PhysicsSystem>{ new PhysicsSystem });
	}

	PhysicsSystem::PhysicsSystem()
		: _physicsWorld{ b2Vec2{0.0f,0.0f} }, _physicsScale{0.01f},
		_velocityIterations{ 8 }, _positionIterations{ 3 }, _contactListener{},
		_pendingReoveListeners{}
	{
		_physicsWorld.SetContactListener(&_contactListener);
		_physicsWorld.SetAllowSleeping(false);
	}

	void PhysicsSystem::ProcessPendingRemoveListeners()
	{
		for (auto listener : _pendingReoveListeners)
		{
			_physicsWorld.DestroyBody(listener);
		}

		_pendingReoveListeners.clear();
	}

	void PhysicsContactListener::BeginContact(b2Contact* contact)
	{
		Actor* first = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		Actor* second = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (first && !first->IsPendingDestroy())
		{
			first->OnActorBeginOverlap(second);
		}

		if (second && !second->IsPendingDestroy())
		{
			second->OnActorBeginOverlap(first);
		}
	}

	void PhysicsContactListener::EndContact(b2Contact* contact)
	{
		Actor* first = nullptr;
		Actor* second = nullptr;

		if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
		{
			first = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		}

		if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
		{
			second = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
		}

		if (first && !first->IsPendingDestroy())
		{
			first->OnActorEndOverlap(second);
		}

		if (second && !second->IsPendingDestroy())
		{
			second->OnActorEndOverlap(first);
		}
	}
}