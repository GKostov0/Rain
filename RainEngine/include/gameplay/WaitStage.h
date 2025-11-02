#pragma once 

#include "gameplay/GameStage.h"

namespace rn
{
	class WaitStage : public GameStage
	{
	public:
		WaitStage(World* owner, float waitDuration);
		virtual void StartStage() override;

	private:
		float _waitDuration;
	};
}