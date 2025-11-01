#pragma once

#include "framework/Object.h"
#include "framework/Delegate.h"

namespace rn
{
	class World;

	class GameStage : public Object
	{
	public:
		GameStage(World* world);

		virtual void StartStage();
		virtual void TickStage(float deltaTime);
		void FinishStage();

		Delegate<> onStageFinished;

		const World* GetWorld() const { return _owner; }
		World* GetWorld() { return _owner; }

		bool IsStageFinished() const { return _stageFinished; }

	private:
		virtual void StageFinished();

	private:
		World* _owner;
		bool _stageFinished;
	};
}