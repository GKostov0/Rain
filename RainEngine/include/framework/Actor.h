#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "Object.h"

class b2Body;

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
		virtual void Tick(float deltaTime);
		void SetTexture(const std::string& path);
		void Render(sf::RenderWindow& window);

		void SetActorLocation(const sf::Vector2f& newLocation);
		void AddActorLocationOffset(const sf::Vector2f& offsetAmount);

		void SetActorRotation(float newRotation);
		void AddActorRotationOffset(float offsetAmount);

		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorRightDirection() const;

		sf::Vector2f GetActorLocation() const;
		float GetActorRotation() const;

		sf::FloatRect GetActorGlobalBounds() const;

		sf::Vector2u GetWindowSize() const;

		World* GetWorld() const { return _owner; }

		bool IsActorOutOfBounds() const;

		void SetEnablePhysics(bool enable);

	private:
		void CenterPivot();
		void InitializePhysics();
		void UnInitializePhysics();
		void UpdatePhysicsBodyTransform();

	private:
		World* _owner;
		bool _beginPlay;

		shared<sf::Texture> _texture;
		sf::Sprite _sprite;

		b2Body* _physicsBody;
		bool _physicsEnabled;
	};
}