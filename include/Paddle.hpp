#pragma once

// C++ STD
#include <iostream>

// ArcadeExtreme
#include <input/input.hpp>
#include <PhysicsObject.hpp>

/**
 * @brief A paddle PhysicsObject.
 */
class Paddle : public PhysicsObject {
	public:
		Paddle(float width, float height);
		virtual ~Paddle() = default;

		virtual void fixedUpdate(Gamemode* gm) override;
		virtual void update(Gamemode* gm, const float dt) override;
		virtual void draw(Gamemode* gm) override;

		/**
		 * @brief Gets the width and height of the paddle.
		 * 
		 * @return sf::Vector2f - A vector containing the width in the x component and the height in the y component.
		 */
		sf::Vector2f getSize();

	private:
		sf::RectangleShape shape;
		float moveSpeed;
};