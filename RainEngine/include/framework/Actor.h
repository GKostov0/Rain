#pragma once

namespace rn
{
	class World;

	class Actor
	{
	public:
		Actor(World* owner);
		virtual ~Actor();

		void BeginPlayInternal();
		virtual void BeginPlay();

		void Tick(float deltaTime);

	private:
		World* _owner;
		bool _beginPlay;
	};
}