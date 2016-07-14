#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <random>
#include <chrono>

#include <SFML/Graphics.hpp>

#include <input/input.hpp>
#include <ui/UIElement.hpp>
#include <ui/Button.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(500, 400), "SFML works!");

	input::bind("click", sf::Mouse::Left);

	ui::Button b{100, 50};
	b.setPosition(50,50);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}

		input::update();

		b.update(window);

		window.clear();
		
		b.draw(window);

		window.display();
	}

	return 0;
}