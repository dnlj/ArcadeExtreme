#pragma once

#include <SFML/Graphics.hpp>

namespace ui {

	/**
	 * @brief A ui element.
	 *
	 * Should be used as a base class for ui element.
	 */
	class UIElement {
		public:
			UIElement(); 
			virtual ~UIElement();

			/**
			 * @brief Draws the ui element.
			 *
			 * @param window The window on which to draw the ui element.
			 * @return void
			 */
			virtual void draw(sf::RenderWindow &window) = 0;

			/**
			 * @brief Updates the ui element.
			 *
			 * This method is used to update any logic the ui element may need.
			 * By default this method does nothing.
			 *
			 * @param window The window where the ui element resides.
			 * @return void
			 */
			virtual void update(sf::RenderWindow &window);

			/**
			 * @brief Sets the position of the ui element.
			 *
			 * @param x The x coordinate of the ui element.
			 * @param y The y coordinate of the ui element.
			 * @return void
			 */
			virtual void setPosition(float x, float y);

		protected:
			/**
			 * @brief The position of this ui element.
			 */
			sf::Vector2f position;
	};
}