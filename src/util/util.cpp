#include <util/util.hpp>

bool util::isInside(sf::Vector2f point, sf::Vector2f position, sf::Vector2f size) {
	if (point.x > position.x && point.x < position.x + size.x) {
		if (point.y > position.y && point.y < position.y + size.y) {
			return true;
		}
	}

	return false;
}