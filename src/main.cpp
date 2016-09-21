// C++ STD
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <random>
#include <chrono>
#include <memory>

// SFML
#include <SFML/Graphics.hpp>

// ArcadeExtreme
#include <input/input.hpp>
#include <ui/UIElement.hpp>
#include <ui/Button.hpp>
#include <Gamemode.hpp>
#include <BrickBreaker.hpp>


namespace {
	// TODO: Document
	// TODO: Move
	double getTimeDelta(std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point end) {
		return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1>>>(std::chrono::high_resolution_clock::now() - start).count();
	}

	// TODO: Document
	// TODO: Move
	void checkForClose(sf::RenderWindow &window) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}
	}

	// TODO: Document
	// TODO: Move
	void updateTitle(sf::RenderWindow &window, const std::vector<double> &frameTimes) {
		double accFrameTime = 0;

		for (auto frameTime : frameTimes) {
			accFrameTime += frameTime;
		}

		window.setTitle("Arcade Extreme (" + std::to_string(frameTimes.size() / accFrameTime) + ")");
	}
}

// TODO: make sure to test with different fixed time steps
int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	//window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	input::bind("click", sf::Mouse::Left);

	input::bind("left", sf::Keyboard::Left);
	input::bind("right", sf::Keyboard::Right);
	input::bind("up", sf::Keyboard::Up);
	input::bind("down", sf::Keyboard::Down);

	//ui::Button b{100, 50};
	//b.setPosition(50,50);

	std::unique_ptr<Gamemode> gm(new BrickBreaker{window, 1.0f / 60.0f});


	auto oldTime = std::chrono::high_resolution_clock::now();
	double accumulator = 0.0;
	const float fixedTimeStep = gm->getFixedTimeStep();
	std::vector<double> frameTimes(100, 0.0);
	int nextFrameTime = 0;
	while (window.isOpen()) {
		// Get the current frameTime
		auto currentTime = std::chrono::high_resolution_clock::now();
		double frameTime = getTimeDelta(oldTime, currentTime);
		oldTime = currentTime;
		accumulator += frameTime;
		
		// Check if the window should close.
		checkForClose(window);
		
		// Fixed update
		for (;accumulator >= fixedTimeStep; accumulator -= fixedTimeStep) {
			gm->fixedUpdate();
		}

		// Update
		input::update();
		gm->update(static_cast<float>(frameTime));

		// Render update
		window.clear();
		gm->draw();
		window.display();

		// Frame rate title update
		updateTitle(window, frameTimes);

		// Update frameTimes
		frameTimes[nextFrameTime++] = frameTime;
		if (nextFrameTime >= frameTimes.size()) { nextFrameTime = 0; }
	}

	return 0;
}