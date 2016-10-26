#include <util/util.hpp>

bool util::isInside(sf::Vector2f point, sf::Vector2f position, sf::Vector2f size) {
	if (point.x > position.x && point.x < position.x + size.x) {
		if (point.y > position.y && point.y < position.y + size.y) {
			return true;
		}
	}

	return false;
}

std::string util::to_string(const sf::Vector2f &vec) {
	std::ostringstream stream;
	stream << "Vector2f(" << vec.x << ", " << vec.y << ")";
	return stream.str();
}

float util::getRandom(float min, float max) {
	return min + static_cast<float>(fmodf(static_cast<float>(rand()), max + 1.0f));
}

sf::Color util::toColor(float r, float g, float b) {
	return sf::Color{
		static_cast<sf::Uint8>(r * 255.0f),
		static_cast<sf::Uint8>(g * 255.0f),
		static_cast<sf::Uint8>(b * 255.0f)
	};
}

float util::lerp(float a, float b, float percent) {
	return a + (b - a) * percent;
}

float util::clamp(float min, float max, float value) {
	return std::max(min, std::min(max, value));
}