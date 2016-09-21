#pragma once

// C++ STD
#include <iostream>
#include <sstream>
#include <cmath>

// SFML
#include <SFML/Graphics.hpp>

/**
 * @brief A namespace for utility functions.
 */
namespace util {
	/**
	 * @brief Checks if @p p is inside a rectange descibed by @p position and @p size.
	 * 
	 * @param[in] point - The point to check.
	 * @param[in] position - The top left corner of the box.
	 * @param[in] size - The width (x) and height (y) of the box.
	 * 
	 * @return True if the point is inside the box otherwise false.
	 */
	bool isInside(sf::Vector2f point, sf::Vector2f position, sf::Vector2f size);


	/**
	 * @brief Converts a vector to a string suitable for display.	
	 * 
	 * @param[in] vec - The vector to be converted to a string.
	 * 
	 * @return The string representation of @p vec.
	 */
	std::string to_string(const sf::Vector2f& vec);

	/**
	 * @brief Generates a random number N, @p min <= N <= @p max
	 * 
	 * @param[in] min - The smallest number to be generated.
	 * @param[in] max - The largets number to be generated.
	 * 
	 * @return A number N, min <= N <= @p max
	 */
	float getRandom(float min, float max);

	// TODO: Figure how to document these
	constexpr float PI = 3.14159265358979323846264338327950288419716939937510582f;
	constexpr float radToDeg = 180.0f / PI;
	constexpr float degToRad = PI / 180.0f;
}
