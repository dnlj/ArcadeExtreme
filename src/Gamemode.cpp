#include <Gamemode.hpp>

Gamemode::Gamemode(sf::RenderWindow &window, float fixedTimeStep) :
		window{window},
		fixedTimeStep{fixedTimeStep} {

	
}

Gamemode::~Gamemode() {
}

sf::RenderWindow& Gamemode::getWindow() const {
	return window;
}

float Gamemode::getFixedTimeStep() const {
	return fixedTimeStep;
}