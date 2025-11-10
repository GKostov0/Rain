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

	AssetManager::AssetManager()
		: _rootDirectory{}
	{
	}

	shared<sf::Texture> AssetManager::LoadTexture(const std::string& filePath)
	{
		return LoadAsset(filePath, _loadedTextureMap);
	}

	shared<sf::Font> AssetManager::LoadFont(const std::string& filePath)
	{
		return LoadAsset(filePath, _loadedFontMap);
	}

	void AssetManager::CleanCycle()
	{
		CleanUniqueReference(_loadedTextureMap);
		CleanUniqueReference(_loadedFontMap);
	}

	void AssetManager::SetAssetRootDirectory(const std::string& directory)
	{
		_rootDirectory = directory;
	}
}