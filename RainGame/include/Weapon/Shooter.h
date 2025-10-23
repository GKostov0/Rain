#pragma once

namespace rn
{
	class Actor;

	class Shooter
	{
	public:
		void Shoot();

		virtual bool CanShoot() const { return true; }
		virtual bool IsOnCooldown() const { return false; }

		Actor* GetOwner() const { return _owner; }

	protected:
		Shooter(Actor* owner);

	private:
		virtual void ShooterImpl() = 0;

	private:
		Actor* _owner;
	};
}