#pragma once

// C++ STD
#include <memory>
#include <vector>

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
			virtual void draw(sf::RenderWindow& window) override;
			virtual void update(sf::RenderWindow& window) override;

			/**
			 * @brief Sets up all the ui elements relative to \p window
			 * 
			 * @return void
			 */
			void performLayout(const sf::RenderWindow& window);

			/**
			 * @breif adds a Button to MainMenu::buttons
			 * 
			 * @param window - The window to pass on to the Gamemode
			 * @param label - The label to put on the button
			 */
			template<class T>
			void addButton(sf::RenderWindow& window, const std::string& label);
		
		private:
			std::vector<Button> buttons;
			std::unique_ptr<Gamemode>& gamemode;
			bool enabled;
			constexpr static float buttonWidth = 200.0f;
			constexpr static float buttonHeight = 50.0f;
	};

	template<class T>
	void MainMenu::addButton(sf::RenderWindow& window, const std::string& label) {
		buttons.emplace_back(buttonWidth, buttonHeight);
		buttons.back().setDoClick([&]() {
			gamemode.reset(new T{window, 1.0f / 60.0f});
			enabled = false;
		});
	}
}
