#include "gameplay/GameStage.h"
#include "framework/Core.h"

namespace rn
{
	GameStage::GameStage(World* world)
		: _owner{ world },
		_stageFinished{false}
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
		_stageFinished = true;
		StageFinished();
		onStageFinished.Broadcast();
	}

	void GameStage::StageFinished()
	{
		LOG("Stage Finished!");
	}
}