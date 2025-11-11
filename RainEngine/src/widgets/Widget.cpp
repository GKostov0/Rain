#include "widgets/Widget.h"

namespace rn
{
	Widget::Widget()
		: _isVisible{true},
		_widgetTransform{}
	{
	}

	void Widget::Draw(sf::RenderWindow& windowReference)
	{
	}

	void Widget::LocationUpdated(const sf::Vector2f& newLocation)
	{
	}

	void Widget::RotationUpdated(float newRotation)
	{
	}

	void Widget::NativeDraw(sf::RenderWindow& windowReference)
	{
		if (_isVisible)
		{
			Draw(windowReference);
		}
	}

	bool Widget::HandleEvent(const sf::Event& ev)
	{
		return false;
	}

	sf::Vector2f Widget::GetCenterPosition() const
	{
		sf::FloatRect bound = GetBound();
		return { bound.left + bound.width / 2.0f, bound.top + bound.height / 2.0f };
	}

	void Widget::SetWidgetLocation(const sf::Vector2f newLocation)
	{
		_widgetTransform.setPosition(newLocation);
		LocationUpdated(newLocation);
	}

	void Widget::SetWidgetRotation(float newRotation)
	{
		_widgetTransform.setRotation(newRotation);
		RotationUpdated(newRotation);
	}

	void Widget::SetVisibility(bool visible)
	{
		_isVisible = visible;
	}
}