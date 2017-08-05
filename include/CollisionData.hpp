#pragma once

// SFML
#include <SFML/System.hpp>

/**
 * @brief Contains data about a collision.
 */
class CollisionData {
	public:
		/** Set to true if collided, otherwise set to false. */
		bool collided;

		/** How far along CollisionData::axis the overlap of the collision is. */
		float distance;

		/** The axis on which the collision occured. */
		sf::Vector2f axis;
};