#pragma once
#include <string>
#include "framework/Core.h"

namespace rn
{
	class World;

	class Explosion
	{
	public:
		Explosion(int particleAmount = 20, float lifeTimeMin = 0.5f, float lifeTimeMax = 2.0f,
					float sizeMin = 1.0f, float sizeMax = 2.0f, float speedMin = 200.0f, float speedMax = 400.0f,
						const sf::Color& particleColor = { sf::Color{255, 128, 0, 255} },

						const List<std::string>& particleImagePaths = 
						{
							"SpaceShooterRedux/PNG/Effects/star1.png",
							"SpaceShooterRedux/PNG/Effects/star2.png",
							"SpaceShooterRedux/PNG/Effects/star3.png"
						});

		void SpawnExplosion(World* world, const sf::Vector2f& location);

	private:
		int _particleAmount;

		float _lifeTimeMin, _lifeTimeMax;
		float _sizeMin, _sizeMax;
		float _speedMin, _speedMax;

		sf::Color _particleColor;

		List<std::string> _particleImagePaths;
	};
}