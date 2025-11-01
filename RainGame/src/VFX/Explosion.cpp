#include "framework/MathUtility.h"
#include "framework/World.h"

#include "VFX/Explosion.h"
#include "VFX/Particle.h"

namespace rn
{
	Explosion::Explosion(int particleAmount, float lifeTimeMin, float lifeTimeMax,
							float sizeMin, float sizeMax, float speedMin, float speedMax,
								const sf::Color& particleColor, const List<std::string>& particleImagePaths)

			: _particleAmount{ particleAmount }, _lifeTimeMin{ lifeTimeMin }, _lifeTimeMax{lifeTimeMax},
				_sizeMin{ sizeMin }, _sizeMax{ sizeMax }, _speedMin{ speedMin }, _speedMax{speedMax},
					_particleColor{ particleColor }, _particleImagePaths { particleImagePaths } { }

	void Explosion::SpawnExplosion(World* world, const sf::Vector2f& location)
	{
		if (!world)
			return;

		for (int i = 0; i < _particleAmount; ++i)
		{
			std::string particleImagePath = _particleImagePaths[(int)RandomRange(0, _particleImagePaths.size())];
			weak<Particle> newParticle = world->SpawnActor<Particle>(particleImagePath);
			newParticle.lock()->RandomLifetime(_lifeTimeMin, _lifeTimeMax);
			newParticle.lock()->SetActorLocation(location);
			newParticle.lock()->RandomSize(_sizeMin, _sizeMax);
			newParticle.lock()->RandomVelocity(_speedMin, _speedMax);
			newParticle.lock()->GetSprite().setColor(_particleColor);
		}
	}
}