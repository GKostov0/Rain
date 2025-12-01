#include <box2d/b2_body.h>

#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"

namespace rn
{
	Actor::Actor(World* owner, const std::string& texturePath)
		: _owner{ owner },
		_beginPlay{ false },
		_texture{ },
		_sprite{ },
		_physicsBody{ nullptr },
		_physicsEnabled{ false },
		_teamID{GetNeutralTeamID()}
	{
		SetTexture(texturePath);
	}

	Actor::~Actor()
	{
		/*LOG("Actor Destroyed!");*/
	}

	void Actor::BeginPlayInternal()
	{
		if (!_beginPlay)
		{
			_beginPlay = true;
			BeginPlay();
		}
	}

	void Actor::BeginPlay()
	{
		LOG("Actor begin play");
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (!IsPendingDestroy())
		{
			Tick(deltaTime);
		}
	}

	void Actor::Tick(float deltaTime)
	{
	}

	void Actor::SetTexture(const std::string& path)
	{
		_texture = AssetManager::Get().LoadTexture(path);
		if (!_texture) return;

		_sprite.setTexture(*_texture);

		int textureWidth = _texture->getSize().x;
		int textureHeight = _texture->getSize().y;

		_sprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight} });
		CenterPivot();
	}

	void Actor::SetTextureRepeated(bool repeat)
	{
		_texture->setRepeated(repeat);
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy())
			return;

		window.draw(_sprite);
	}

	void Actor::SetActorLocation(const sf::Vector2f& newLocation)
	{
		_sprite.setPosition(newLocation);
		UpdatePhysicsBodyTransform();
	}

	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmount)
	{
		SetActorLocation(GetActorLocation() + offsetAmount);
	}

	void Actor::SetActorRotation(float newRotation)
	{
		_sprite.setRotation(newRotation);
		UpdatePhysicsBodyTransform();
	}

	void Actor::AddActorRotationOffset(float offsetAmount)
	{
		SetActorRotation(GetActorRotation() + offsetAmount);
	}

	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation());
	}

	sf::Vector2f Actor::GetActorRightDirection() const
	{
		return RotationToVector(GetActorRotation() + 90.0f);
	}

	sf::Vector2f Actor::GetActorLocation() const
	{
		return _sprite.getPosition();
	}

	float Actor::GetActorRotation() const
	{
		return _sprite.getRotation();
	}

	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return _sprite.getGlobalBounds();
	}

	sf::Vector2u Actor::GetWindowSize() const
	{
		return _owner->GetWindowSize();
	}

	bool Actor::IsActorOutOfBounds(float tolerance) const
	{
		float windowWidth = GetWindowSize().x;
		float windowHeight = GetWindowSize().y;

		float width = GetActorGlobalBounds().width;
		float height = GetActorGlobalBounds().height;

		sf::Vector2f actorPosition = GetActorLocation();

		// Left						   or	Right
		if ((actorPosition.x < -width - tolerance) || (actorPosition.x > windowWidth + width + tolerance))
		{
			return true;
		}

		// Up							or	Down
		if ((actorPosition.y < -height - tolerance) || (actorPosition.y > windowHeight + height + tolerance))
		{
			return true;
		}

		return false;
	}

	void Actor::SetEnablePhysics(bool enable)
	{
		_physicsEnabled = enable;

		if (_physicsEnabled)
		{
			InitializePhysics();
		}
		else
		{
			UnInitializePhysics();
		}
	}

	void Actor::OnActorBeginOverlap(Actor* other)
	{
		//LOG("Begin Overlap!");
	}

	void Actor::OnActorEndOverlap(Actor* other)
	{
		//LOG("End Overlap!");
	}

	void Actor::Destroy()
	{
		UnInitializePhysics();
		onActorDestroy.Broadcast(this);
		Object::Destroy();
	}

	bool Actor::IsOtherHostile(Actor* other) const
	{
		if (other == nullptr)
			return false;

		if (GetTeamID() == GetNeutralTeamID() || other->GetTeamID() == GetNeutralTeamID())
		{
			return false;
		}

		return GetTeamID() != other->GetTeamID();
	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bound = _sprite.getGlobalBounds();
		_sprite.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
	}

	void Actor::InitializePhysics()
	{
		if (!_physicsBody)
		{
			_physicsBody = PhysicsSystem::Get().AddListener(this);
		}
	}

	void Actor::UnInitializePhysics()
	{
		if (_physicsBody)
		{
			PhysicsSystem::Get().RemoveListener(_physicsBody);
			_physicsBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(nullptr);
			_physicsBody = nullptr;
		}
	}

	void Actor::UpdatePhysicsBodyTransform()
	{
		if (_physicsBody)
		{
			float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
			b2Vec2 pos{ GetActorLocation().x * physicsScale, GetActorLocation().y * physicsScale };
			float rotation = DegreesToRadians(GetActorRotation());

			_physicsBody->SetTransform(pos, rotation);
		}
	}

	void Actor::ApplyDamage(float amount)
	{

	}
}