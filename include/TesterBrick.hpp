#pragma once

// C++ STD
#include <iostream>

// ArcadeExtreme
#include <input/input.hpp>
#include <PhysicsObject.hpp>


/**
 * @brief A PhysicsObject used for testing collisions.
 */
class TesterBrick : public PhysicsObject {
	public:
		TesterBrick();
		virtual ~TesterBrick() = default;

		virtual void fixedUpdate(Gamemode* gm) override;
		virtual void update(Gamemode* gm, const float dt) override;
		virtual void draw(Gamemode* gm) override;

		std::vector<sf::Vertex> lineVerts;

	private:
		sf::CircleShape shape;
};