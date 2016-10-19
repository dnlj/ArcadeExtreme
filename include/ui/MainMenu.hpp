#pragma once

// C++ STD
#include <memory>

// SFML
#include <SFML/Graphics.hpp>

// Arcade Extreme
#include <ui/UIElement.hpp>
#include <ui/Button.hpp>
#include <Gamemode.hpp>

namespace ui {

	/**
	* @brief The main menu for the game.
	*
	* Should be used as a base class for any clickable ui.
	*/
	class MainMenu : public UIElement {
		public:
			MainMenu(std::unique_ptr<Gamemode>& gm, sf::RenderWindow& window);
			virtual void draw(sf::RenderWindow &window) override;
			virtual void update(sf::RenderWindow &window) override;
		
		private:
			Button brickBreakerButton;
			std::unique_ptr<Gamemode>& gamemode;
			bool enabled;
	};
}
