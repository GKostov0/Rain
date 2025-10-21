#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "Object.h"

namespace rn
{
	class World;

	class Actor : public Object
	{
	public:
		Actor(World* owner, const std::string& texturePath = "");
		virtual ~Actor();

		void BeginPlayInternal();
		virtual void BeginPlay();

		void TickInternal(float deltaTime);
		void Tick(float deltaTime);
		void SetTexture(const std::string& path);
		void Render(sf::RenderWindow& window);

	private:
		World* _owner;
		bool _beginPlay;

		sf::Texture _texture;
		sf::Sprite _sprite;
	};
}