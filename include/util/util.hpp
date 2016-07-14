#pragma once
#include <SFML/Graphics.hpp>


/**
 * @brief A namespace for utility functions.
 */
namespace util {
	bool isInside(sf::Vector2f point, sf::Vector2f position, sf::Vector2f size);
}