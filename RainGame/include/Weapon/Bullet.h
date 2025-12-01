#pragma once

#include <framework/Actor.h>

namespace rn
{
	class Bullet : public Actor
	{
	public:
		Bullet(World* world, Actor* owner, const std::string& texturePath, float speed = 800.0f, float damage = 10.0f);

		void SetSpeed(float speed);
		void SetDamage(float damage);
		void SetZigZag(bool isZigZag);

		virtual void Tick(float deltaTime) override;

		virtual void OnActorBeginOverlap(Actor* other) override;

		float GetDamage() const { return _damage; }

		virtual void BeginPlay() override;

	private:
		void Move(float deltaTime);

	private:
		Actor* _owner;
		float _speed;
		float _damage;

		bool _isZigZag;
		int _zigZagOffset;
		bool _isZigZagLeft;
	};
}