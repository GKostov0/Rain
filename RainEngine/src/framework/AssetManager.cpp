#include "framework/AssetManager.h"

namespace rn
{
	unique<AssetManager> AssetManager::_assetManager{ nullptr };

	AssetManager& AssetManager::Get()
	{
		if (!_assetManager)
		{
			_assetManager = unique<AssetManager> { new AssetManager };
		}

		return *_assetManager;
	}

	shared<sf::Texture> AssetManager::LoadTexture(const std::string& filePath)
	{
		auto result = _loadedTextureMap.find(filePath);
		if (result != _loadedTextureMap.end())
		{
			return result->second;
		}

		shared<sf::Texture> newTexture{ new sf::Texture };
		if (newTexture->loadFromFile(filePath))
		{
			_loadedTextureMap.insert({ filePath, newTexture });
			return newTexture;
		}

		return shared<sf::Texture>{nullptr};
	}

	void AssetManager::CleanCycle()
	{
		for (auto it = _loadedTextureMap.begin(); it != _loadedTextureMap.end(); )
		{
			if (it->second.unique())
			{
				LOG("Cleaning texture: %s", it->first.c_str());
				it = _loadedTextureMap.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	AssetManager::AssetManager()
	{
	}
}