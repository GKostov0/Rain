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
		auto result = _loadedTextureMap.find(filePath);
		if (result != _loadedTextureMap.end())
		{
			return result->second;
		}

		shared<sf::Texture> newTexture{ new sf::Texture };
		if (newTexture->loadFromFile(_rootDirectory + filePath))
		{
			_loadedTextureMap.insert({ filePath, newTexture });
			return newTexture;
		}

		return shared<sf::Texture>{nullptr};
	}

	shared<sf::Font> AssetManager::LoadFont(const std::string& filePath)
	{
		auto result = _loadedFontMap.find(filePath);

		if (result != _loadedFontMap.end())
		{
			return result->second;
		}

		shared<sf::Font> newFont{ new sf::Font };
		if (newFont->loadFromFile(_rootDirectory + filePath))
		{
			_loadedFontMap.insert({ filePath, newFont });
			return newFont;
		}

		return shared<sf::Font>{nullptr};
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

		for (auto it = _loadedFontMap.begin(); it != _loadedFontMap.end(); )
		{
			if (it->second.unique())
			{
				LOG("Cleaning font: %s", it->first.c_str());
				it = _loadedFontMap.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void AssetManager::SetAssetRootDirectory(const std::string& directory)
	{
		_rootDirectory = directory;
	}

	
}