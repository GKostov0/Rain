#include "framework/BackgroundLayer.h"

namespace rn
{
	BackgroundLayer::BackgroundLayer(World* owner, const List<std::string>& assetPaths,
		const sf::Vector2f& minVelocity, const sf::Vector2f& maxVelocity,
		float minSize, float maxSize, int spriteCount, const sf::Color& colorTint)
		: Actor{owner},
		_minVelocity{minVelocity},
		_maxVelocity{maxVelocity},
		_minSize{ minSize },
		_maxSize{maxSize},
		_spriteCount{spriteCount},
		_tintColor{colorTint}
	{
		SetEnablePhysics(false);
	}
}