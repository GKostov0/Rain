#pragma once

#include "framework/Core.h"
#include "Player/Player.h"

namespace rn
{
	class PlayerManager
	{
	public:
		Player& CreateNewPlayer();

		Player* GetPlayer(int playerIndex = 0);
		const Player* GetPlayer(int playerIndex = 0) const;

		static PlayerManager& Get();

	protected:
		PlayerManager();

	private:
		List<Player> _players;
		static unique<PlayerManager> _playerManager;
	};
}