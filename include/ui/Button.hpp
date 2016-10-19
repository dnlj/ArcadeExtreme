#pragma once

#include <iostream>
#include <random>
#include <chrono>
#include <functional>

#include <SFML/Graphics.hpp>

#include <util/util.hpp>
#include <ui/UIElement.hpp>
#include <input/input.hpp>


namespace ui {

	/**
	 * @brief A clickable button.
	 * 
	 * Should be used as a base class for any clickable ui.
	 */
	class Button : public UIElement {
		public:
			/**
			 * @brief Creates a button with the width and height specified.
			 *
			 * @param width The width of the button.
			 * @param height The height of the button.
			 */
			Button(int width, int height);

			/**
			 * @brief Performs cleanup when the button is destroyed.
			 */
			virtual ~Button();


			/**
			 * @brief Performs any per frame logic.
			 * 
			 * Should be called once per frame to update the button.
			 *
			 * @param window The the window in which the button resides .
			 * @return void
			 */
			virtual void update(sf::RenderWindow &window) override;
			
			/**
			 * @brief Called when the button is clicked.
			 *
			 * Does nothing by default. Should be overridden to add custom behavior.
			 * 
			 * @return void
			 */
			virtual void doClick();
			
			/**
			 * @brief Draws the button onto window.
			 *
			 * Should be called once per frame to draw the button on window.
			 *
			 * @param window The the window in which the button resides.
			 * @return void
			 */
			virtual void draw(sf::RenderWindow &window) override;

			/**
			 * @brief Set the function that is called when the Button is clicked
			 * 
			 * @param func The function that is called when the Button is clicked
			 * @return void
			 */
			void setDoClick(std::function<void(void)> func);


		private:
			sf::RectangleShape shape;
			std::function<void()> doClickFunction;
	};
}