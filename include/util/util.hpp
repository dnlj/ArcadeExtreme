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

	/**
	 * @brief Constructs a sf::Color from float percent values
	 * 
	 * @param[in] r - The percent red value for the color
	 * @param[in] g - The percent green value for the color
	 * @param[in] b - The percent blue value for the color
	 * 
	 * @return A color constructed from @p r @p g and @p b 
	 */
	sf::Color toColor(float r, float g, float b);

	/**
	 * @brief Linearly interpolates between @p a and @p b
	 *
	 * @param[in] a - The first value to interpolate between
	 * @param[in] b - The second value to interpolate between
	 * @param[in] percent - The percent inbetween @p a and @p b
	 *
	 * @return Returns a value @p percent percent between @p a and @p b
	 */
	float lerp(float a, float b, float percent);

	/**
	 * @brief Clamps @p value between @p a and @p b
	 *
	 * @param[in] min - The minimum value to clamp to
	 * @param[in] max - The maximum value to clamp to
	 * @param[in] value - The number to clamp inbetween @p a and @p b
	 *
	 * @return Returns a value clamped to @p min and @p max
	 */
	float clamp(float min, float max, float value);
	
	/**
	 * @brief Gets the global font.
	 * 
	 * @return Retuns the global font.
	 */
	const sf::Font& getFont();

	// TODO: Figure how to document these
	constexpr float PI = 3.14159265358979323846264338327950288419716939937510582f;
	constexpr float radToDeg = 180.0f / PI;
	constexpr float degToRad = PI / 180.0f;
}
