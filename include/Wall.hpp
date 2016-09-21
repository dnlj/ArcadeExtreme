#pragma once

// ArcadeExtreme
#include <PhysicsObject.hpp>

/**
 * @brief A wall PhysicsObject.
 */
class Wall : public PhysicsObject {
	public:
		Wall(float width, float height);
		virtual ~Wall() = default;
	
		virtual void fixedUpdate(Gamemode* gm) override;
		virtual void update(Gamemode* gm, const float dt) override;
		virtual void draw(Gamemode* gm) override;

	private:
		sf::RectangleShape shape;
};