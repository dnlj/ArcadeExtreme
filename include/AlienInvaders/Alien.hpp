#pragma once

// SFML
#include <SFML/Graphics.hpp>

// Arcade Extreme
#include <PhysicsObject.hpp>

namespace AlienInvaders {
	class Alien : public PhysicsObject {
		public:
			Alien();
			
			virtual void fixedUpdate(Gamemode* gm) override;
			virtual void update(Gamemode* gm, const float dt) override;
			virtual void draw(Gamemode* gm) override;

			int getHeight() const;

		private:
			/**
			 * @brief Sets the position of the shapes centered on \p position
			 * 
			 * @param position - The position to center the shapes around
			 * 
			 * @return void
			 */
			void setShapePositions(sf::Vector2f position);

			/**
			 * @brief Draws the shapes
			 * 
			 * @param window - The window to draw the shapes on
			 *
			 * @return void
			 */
			void drawShapes(sf::RenderWindow& window);
			
			/**
			 * @brief Setups the shape objects.
			 * 
			 * @return void
			 */
			void setupShapes();

			
			sf::ConvexShape topSemiCircle;
			sf::RectangleShape body;
			sf::RectangleShape tenticle1;
			sf::RectangleShape tenticle2;
			sf::RectangleShape tenticle3;
			int height;
	};
}
