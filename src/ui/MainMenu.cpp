// Arcade Extreme
#include <BrickBreaker.hpp>
#include <ui/MainMenu.hpp>
#include <input/input.hpp>

namespace ui {
	MainMenu::MainMenu(std::unique_ptr<Gamemode>& gm, sf::RenderWindow& window)
			: brickBreakerButton{100, 50},
			gamemode{gm},
			enabled{true} {

		brickBreakerButton.setPosition(20, 20);
		brickBreakerButton.setDoClick([&](){
			gamemode.reset(new BrickBreaker{window, 1.0f / 60.0f});
			enabled = false;
		});

	}

	void MainMenu::draw(sf::RenderWindow &window) {
		if (!enabled) { return; }

		brickBreakerButton.draw(window);
	}

	void MainMenu::update(sf::RenderWindow &window) {
		if (input::wasPressed("menu") && gamemode != nullptr) { enabled = !enabled; };
		if (gamemode != nullptr) { gamemode->setPaused(enabled); }
		if (!enabled) { return; }

		brickBreakerButton.update(window);
	}
}