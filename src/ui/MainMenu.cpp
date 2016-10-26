// Arcade Extreme
#include <ui/MainMenu.hpp>
#include <BrickBreaker.hpp>
#include <input/input.hpp>
#include <AlienInvaders/AlienInvaders.hpp>



namespace ui {
	MainMenu::MainMenu(std::unique_ptr<Gamemode>& gm, sf::RenderWindow& window)
			: buttons{},
			gamemode{gm},
			enabled{true} {

		addButton<BrickBreaker>(window, "Brick Breaker");
		addButton<AlienInvaders::AlienInvaders>(window, "Alien Invaders");
		//addButton<BrickBreaker>(window, "BrickBreaker");
		//addButton<BrickBreaker>(window, "BrickBreaker");
		//addButton<BrickBreaker>(window, "BrickBreaker");

		performLayout(window);
	}

	void MainMenu::draw(sf::RenderWindow& window) {
		if (!enabled) { return; }

		for (auto button : buttons) {
			button.draw(window);
		}
	}

	void MainMenu::update(sf::RenderWindow& window) {
		if (input::wasPressed("menu") && gamemode != nullptr) { enabled = !enabled; };
		if (gamemode != nullptr) { gamemode->setPaused(enabled); }
		if (!enabled) { return; }

		for (auto button : buttons) {
			button.update(window);
		}
	}

	void MainMenu::performLayout(const sf::RenderWindow& window) {
		constexpr float padding = 10.0f;
		const auto& windowSize = window.getSize();
		float nextY = 200.0f;

		for (auto& button : buttons) {
			button.setPosition(windowSize.x / 2.0f - buttonWidth / 2.0f, nextY);
			nextY += padding + buttonHeight;
		}
	}
}