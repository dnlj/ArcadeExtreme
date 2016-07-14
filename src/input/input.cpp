#include <input/input.hpp>

std::unordered_map<std::string, sf::Keyboard::Key> input::detail::keyBinds;
std::unordered_map<std::string, sf::Mouse::Button> input::detail::mouseBinds;
std::unordered_map<std::string, bool> input::detail::pressed;
std::unordered_map<std::string, bool> input::detail::lastFrame;


void input::bind(const std::string &name, sf::Keyboard::Key key) {
	detail::keyBinds[name] = key;
}

void input::bind(const std::string &name, sf::Mouse::Button button) {
	detail::mouseBinds[name] = button;
}

bool input::isPressed(const std::string &name) {
	return detail::pressed.find(name) != detail::pressed.end();
};

bool input::wasPressed(const std::string &name) {
	return detail::lastFrame.find(name) == detail::lastFrame.end() && isPressed(name);
}

bool input::wasReleased(const std::string &name) {
	return detail::lastFrame.find(name) != detail::lastFrame.end() && !isPressed(name);
}

void input::update() {
	detail::lastFrame = {};
	detail::pressed.swap(detail::lastFrame);

	for (auto it = detail::keyBinds.begin(); it != detail::keyBinds.end(); ++it) {
		if (sf::Keyboard::isKeyPressed(it->second)) {
			detail::pressed[it->first] = true;
		}
	}

	for (auto it = detail::mouseBinds.begin(); it != detail::mouseBinds.end(); ++it) {
		if (sf::Mouse::isButtonPressed(it->second)) {
			detail::pressed[it->first] = true;
		}
	}
}