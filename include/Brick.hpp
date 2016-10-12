#pragma once

// ArcadeExtreme
#include <PhysicsObject.hpp>


/**
 * @brief A square brick PhysicsObject.
 */
class Brick : public PhysicsObject {
	public:
		Brick(float width, float height);
		virtual ~Brick();

		virtual void fixedUpdate(Gamemode* gm) override;
		virtual void update(Gamemode* gm, const float dt) override;
		virtual void draw(Gamemode* gm) override;

		/**
		 * @brief Sets the value of Brick::enabled.
		 * 
		 * @param[in] enabled - The value to set Brick::enabled to.
		 * 
		 * @return void
		 */
		void setEnabled(bool enabled);

		/**
		 * @brief Gets the value of Brick::enabled.
		 * 
		 * @return bool - The current value of Brick::enabled.
		 */
		bool getEnabled() const;

		/**
		 * @brief Sets the color of the Brick.
		 * 
		 * @param[in] color - The color to set the brick to.
		 * 
		 * @return void
		 */
		void setColor(sf::Color color);

	private:
		sf::RectangleShape shape;
		bool enabled;
};