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

		int GetCurrentLevel() const { return _currentLevel; }
		int GetMaxLevel() const { return _maxLevel; }

		virtual void IncrementLevel(int amount = 1);

	protected:
		Shooter(Actor* owner);

	private:
		virtual void ShooterImpl() = 0;

	private:
		Actor* _owner;

		int _currentLevel;
		int _maxLevel;
	};
}