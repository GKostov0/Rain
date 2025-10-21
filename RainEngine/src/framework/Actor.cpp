#include "framework/Actor.h"
#include "framework/Core.h"

namespace rn
{
	Actor::Actor(World* owner)
		: _owner{ owner }, _beginPlay{false}
	{
	}

	Actor::~Actor()
	{
	}

	void Actor::BeginPlayInternal()
	{
		if (!_beginPlay)
		{
			_beginPlay = true;
			BeginPlay();
		}
	}

	void Actor::BeginPlay()
	{
		LOG("Actor begin play");
	}

	void Actor::Tick(float deltaTime)
	{
		LOG("Actor tick!");
	}
}
