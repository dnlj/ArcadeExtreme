#pragma once

// SFML
#include <SFML/System.hpp>

// TODO: Figure out why these @var comments dont work with doxygen
/**
 * @brief Contains data about a collision.
 */
class CollisionData {
	public:
		/** @var bool - Set to true if collided, otherwise set to false. */
		bool collided;

		/** @var float - How far along CollisionData::axis the overlap of the collision is. */
		float distance;

		/** @var sf::Vector2f - The axis on which the collision occured. */
		sf::Vector2f axis;
};