#pragma once

#include<SFML/Graphics.hpp>
#include "framework/Core.h"

namespace rn
{
	class AssetManager
	{
	public:
		static AssetManager& Get();
		shared<sf::Texture> LoadTexture(const std::string& filePath);
		shared<sf::Font> LoadFont(const std::string& filePath);

		void CleanCycle();
		void SetAssetRootDirectory(const std::string& directory);

	protected:
		AssetManager();

	private:
		template<typename T>
		shared<T> LoadAsset(const std::string& filePath, Dictionary<std::string, shared<T>>& container);

		template<typename T>
		void CleanUniqueReference(Dictionary<std::string, shared<T>>& container);
		
	private:
		static unique<AssetManager> _assetManager;

		Dictionary<std::string, shared<sf::Texture>> _loadedTextureMap;
		Dictionary<std::string, shared<sf::Font>> _loadedFontMap;

		std::string _rootDirectory;
	};

	template<typename T>
	inline shared<T> AssetManager::LoadAsset(const std::string& filePath, Dictionary<std::string, shared<T>>& container)
	{
		auto result = container.find(filePath);
		if (result != container.end())
		{
			return result->second;
		}

		shared<T> newAsset{ new T };
		if (newAsset->loadFromFile(_rootDirectory + filePath))
		{
			container.insert({ filePath, newAsset });
			return newAsset;
		}

		return shared<T>{nullptr};
	}

	template<typename T>
	inline void AssetManager::CleanUniqueReference(Dictionary<std::string, shared<T>>& container)
	{
		for (auto it = container.begin(); it != container.end(); )
		{
			if (it->second.unique())
			{
				LOG("Cleaning: %s", it->first.c_str());
				it = container.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}