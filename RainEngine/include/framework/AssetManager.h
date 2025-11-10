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
		static unique<AssetManager> _assetManager;

		Dictionary<std::string, shared<sf::Texture>> _loadedTextureMap;
		Dictionary<std::string, shared<sf::Font>> _loadedFontMap;

		std::string _rootDirectory;
	};
}