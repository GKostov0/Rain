#pragma once

#include <SFML/Graphics.hpp>

namespace rn
{
	sf::Vector2f RotationToVector(float rotation);
	float DegreesToRadians(float degrees);
	float RadiansToDegrees(float radians);

	template<typename T>
	float GetVectorLength(const sf::Vector2<T>& vector)
	{
		return std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
	}

	template<typename T>
	sf::Vector2<T>& ScaleVector(sf::Vector2<T>& vector, float scale)
	{
		vector.x *= scale;
		vector.y *= scale;

		return vector;
	}

	template<typename T>
	sf::Vector2<T>& Normalize(sf::Vector2<T>& vector)
	{
		float length = GetVectorLength<T>(vector);

		if (length == 0.0f) 
			return sf::Vector2<T>{};

		ScaleVector(vector, 1.0f / length);

		return vector;
	}

	sf::Color LerpColor(const sf::Color& a, const sf::Color& b, float alpha);
	sf::Vector2f LerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float alpha);
	float LerpFloat(float a, float b, float alpha);

	float RandomRange(float min, float max);
	sf::Vector2f RandomUnitVector();
}