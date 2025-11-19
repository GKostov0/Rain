#include "Player/PlayerManager.h"

namespace rn
{
	unique<PlayerManager> PlayerManager::_playerManager{nullptr};

	PlayerManager::PlayerManager()
	{
	}

	Player& PlayerManager::CreateNewPlayer()
	{
		_players.emplace(_players.begin(), Player());
		return _players.back();
	}

	Player* PlayerManager::GetPlayer(int playerIndex)
	{
		if (playerIndex >= 0 && playerIndex <= _players.size())
			return &(_players[playerIndex]);

		return nullptr;
	}

	const Player* PlayerManager::GetPlayer(int playerIndex) const
	{
		if (playerIndex >= 0 && playerIndex <= _players.size())
			return &(_players[playerIndex]);

		return nullptr;
	}

	void PlayerManager::Reset()
	{
		_players.clear();
	}

	PlayerManager& PlayerManager::Get()
	{
		if (!_playerManager)
		{
			_playerManager = std::move(unique<PlayerManager>{new PlayerManager{}});
		}

		return *_playerManager;
	}
}