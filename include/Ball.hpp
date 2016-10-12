#pragma once

// SFML
#include <SFML/Graphics.hpp>

// ArcadeExtreme
#include <GameObject.hpp>
#include <PhysicsObject.hpp>

/**
 * @brief A Ball PhysicsObject. 
 */
class Ball : public PhysicsObject {
	public:
		Ball(float radius, unsigned int points = 8);
		virtual ~Ball() = default;

		virtual void fixedUpdate(Gamemode* gm) override;
		virtual void update(Gamemode* gm, const float dt) override;
		virtual void draw(Gamemode* gm) override;

		/**
		 * @brief Gets the radius of this Ball.
		 * 
		 * @return float - The radius of this Ball.
		 */
		float getRadius() const;

		/**
		 * @brief Does the bounce effect
		 * 
		 * @return void
		 */
		void bounceEffect();

	private:
		sf::CircleShape shape;
};