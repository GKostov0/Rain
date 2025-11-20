#include "framework/BackdropActor.h"
#include "framework/World.h"

namespace rn
{
	BackdropActor::BackdropActor(World* owner, const std::string& texturePath, const sf::Vector2f& velocity)
		: Actor{owner, texturePath},
		_movingVelocity{velocity},
		_leftShift{0.0f},
		_topShift{0.0f}
	{
		auto windowSize = GetWorld()->GetWindowSize();
		GetSprite().setOrigin(0.0f, 0.0f);
		GetSprite().setTextureRect(sf::IntRect{ sf::Vector2i{0, 0}, sf::Vector2i{(int)windowSize.x, (int)windowSize.y} });
		SetTextureRepeated(true);
	}

	void BackdropActor::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		_leftShift += deltaTime * _movingVelocity.x;
		_topShift += deltaTime * _movingVelocity.y;

		sf::IntRect currentRect = GetSprite().getTextureRect();
		currentRect.left = _leftShift;
		currentRect.top = _topShift;

		GetSprite().setTextureRect(currentRect);
	}
}