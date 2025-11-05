#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/Delegate.h"
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

		const World* GetWorld() const { return _owner; }
		World* GetWorld() { return _owner; }

		bool IsActorOutOfBounds(float tolerance = 10.0f) const;

		void SetEnablePhysics(bool enable);

		virtual void OnActorBeginOverlap(Actor* other);
		virtual void OnActorEndOverlap(Actor* other);

		virtual void Destroy() override;

		static uint8 GetNeutralTeamID() { return neutralTeamID; }
		void SetTeamID(uint8 teamID) { _teamID = teamID; }
		uint8 GetTeamID() const { return _teamID; }

		bool IsOtherHostile(Actor* other) const;

		virtual void ApplyDamage(float amount);

		sf::Sprite& GetSprite() { return _sprite; }
		const sf::Sprite& GetSprite() const { return _sprite; }

		Delegate<Actor*> onActorDestroy;

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

		uint8 _teamID;

		const static uint8 neutralTeamID = 255;
	};
}