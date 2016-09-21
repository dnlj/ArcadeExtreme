#pragma once

#include <SFML/System.hpp>

namespace util {
	/**
	 * @brief Contains utility function related to vectors.
	 */
	namespace vector {
		/**
		 * @brief Takes the dot product of two sf::Vector2f's
		 * 
		 * @param[in] vec1 - The first sf::Vector2f.
		 * @param[in] vec2 - The second sf::Vector2f.
		 * 
		 * @return float - The dot product of @p vec1 and @p vec2.
		 */
		float dot(const sf::Vector2f& vec1, const sf::Vector2f& vec2);

		/**
		 * @brief Gets the squared norm (magnitude) of a sf::Vector2f.
		 *
		 * @param[in] vec - The sf::Vector2f to get the squared norm of.
		 *
		 * @return float - The squared norm of @p vec.
		 */
		float squaredNorm(const sf::Vector2f& vec);

		/**
		 * @brief Gets the norm (magnitude) of a sf::Vector2f.
		 *
		 * @param[in] vec - The sf::Vector2f to get the norm of.
		 *
		 * @return float - The norm of @p vec.
		 */
		float norm(const sf::Vector2f& vec);

		/**
		 * @brief Normalizes a sf::Vector2f.
		 *
		 * @param[in] vec - The sf::Vector2f get the normal of.
		 *
		 * @return float - The normalized version of @p vec.
		 */
		sf::Vector2f normalize(const sf::Vector2f& vec);
	}
}