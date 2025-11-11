#pragma once

#include <SFML/Graphics.hpp>
#include "framework/Object.h"

namespace rn
{
	class Widget : public Object
	{
	public:
		virtual bool HandleEvent(const sf::Event& ev);
		virtual sf::FloatRect GetBound() const;

		sf::Vector2f GetCenterPosition() const;

		void NativeDraw(sf::RenderWindow& windowReference);
		void SetWidgetLocation(const sf::Vector2f newLocation);
		void SetWidgetRotation(float newRotation);

		sf::Vector2f GetWidgetLocation() const { return _widgetTransform.getPosition(); }
		float GetWidgetRotation() const { return _widgetTransform.getRotation(); }

		void SetVisibility(bool visible);
		bool GetVisibility() const { return _isVisible; }

	protected:
		Widget();

	private:
		virtual void Draw(sf::RenderWindow& windowReference);
		virtual void LocationUpdated(const sf::Vector2f& newLocation);
		virtual void RotationUpdated(float newRotation);

	private:
		sf::Transformable _widgetTransform;
		bool _isVisible;
	};
}