#include "gameplay/GameStage.h"
#include "framework/Core.h"

namespace rn
{
	GameStage::GameStage(World* world)
		: _owner{ world }, _stageFinished{false}
	{
	}

	void GameStage::StartStage() 
	{
		LOG("Stage Started!");
	}

	void GameStage::TickStage(float deltaTime)
	{
	}

	void GameStage::FinishStage()
	{
		onStageFinished.Broadcast();
		_stageFinished = true;
		StageFinished();
	}

	void GameStage::StageFinished()
	{
		LOG("Stage Finished!");
	}
}