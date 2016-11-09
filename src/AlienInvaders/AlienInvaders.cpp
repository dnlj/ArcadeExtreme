// Arcade Extreme
#include <AlienInvaders/AlienInvaders.hpp>

namespace AlienInvaders {
	AlienInvaders::AlienInvaders(sf::RenderWindow& window, float fixedTimeStep) :
		Gamemode{window, fixedTimeStep} {
		const int width = window.getSize().x;
		const int height = window.getSize().y;

		constexpr int widthCount = 5;
		constexpr int heightCount = 3;
		constexpr int widthPadding = 200;
		constexpr int topPadding = 100;
		constexpr int bottomPadding = 300;
		const int widthInc = (width - widthPadding * 2) / (widthCount - 1);

		// Setup the Aliens
		for (int x = 0; x < widthCount; ++x) {
			int xPos = widthPadding + widthInc * x;
			for (int y = 0; y < heightCount; ++y) {
				aliens.emplace_back();
				Alien& alien = aliens.back();
				int yPos = static_cast<int>(topPadding + alien.getHeight() * 1.2f * y);
				alien.setPosition({static_cast<float>(xPos), static_cast<float>(yPos)});
			}
		}

		// Setup the ship
		ship.setPosition({height - 50.0f, width / 2.0f - 50.0f});
	}

	AlienInvaders::~AlienInvaders() {
	}

	void AlienInvaders::fixedUpdate() {
		ship.fixedUpdate(this);

		for (auto& alien : aliens) {
			alien.fixedUpdate(this);
		}
	}

	void AlienInvaders::update(const float dt) {
		ship.update(this, dt);
		
		for (auto& alien : aliens) {
			alien.update(this, dt);
		}
	}

	void AlienInvaders::draw() {
		for (auto& alien : aliens) {
			alien.draw(this);
		}

		ship.draw(this);
	}
}