#pragma once

#include <SFML/Graphics.hpp>
#include "framework/Object.h"

namespace rn
{
	class HUD : public Object
	{
	public:
		virtual void Draw(sf::RenderWindow& windowReference) = 0;
		void NativeInitialize(const sf::RenderWindow& windowReference);

		bool IsInit() const { return _isInitialized; }
		virtual bool HandleEvent(const sf::Event& ev);
		virtual void Tick(float deltaTime);

	protected:
		HUD();

	private:
		virtual void Initialize(const sf::RenderWindow& windowReference);

	private:
		bool _isInitialized;
	};
}