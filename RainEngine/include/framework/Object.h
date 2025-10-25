#pragma once

namespace rn
{
	class Object
	{
	public:
		Object();
		virtual ~Object();

		bool IsPendingDestroy() const { return _pendingDestroy; }

		virtual void Destroy();

	private:
		bool _pendingDestroy;
	};
}