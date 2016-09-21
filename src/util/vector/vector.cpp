#include <util/vector/vector.hpp>

namespace util {
	float vector::dot(const sf::Vector2f &vec1, const sf::Vector2f &vec2) {
		return (vec1.x * vec2.x) + (vec1.y * vec2.y);
	}
	
	float vector::squaredNorm(const sf::Vector2f &vec) {
		return vec.x * vec.x + vec.y * vec.y;
	}

	float vector::norm(const sf::Vector2f &vec) {
		return sqrtf(squaredNorm(vec));
	}

	sf::Vector2f vector::normalize(const sf::Vector2f &vec) {
		if (vec.x == 0.0f && vec.y == 0.0f) {
			return {0.0f, 0.0f};
		}

		return vec / norm(vec);
	}	
}