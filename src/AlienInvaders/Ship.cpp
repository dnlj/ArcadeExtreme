// Arcade Extreme
#include <AlienInvaders/Ship.hpp>
#include <input/input.hpp>

namespace AlienInvaders {
	Ship::Ship() :
		moveSpeed{50.0f}
		{

		friction = 0.000005f;

		shape.setSize({50, 35});
		shape.setFillColor(sf::Color::Red);
	}

	void Ship::fixedUpdate(Gamemode* gm) {
		const auto dt = gm->getFixedTimeStep();

		if (input::isPressed("left")) {
			velocity.x -= moveSpeed;
		}

		if (input::isPressed("right")) {
			velocity.x += moveSpeed;
		}

		PhysicsObject::fixedUpdate(gm);
	}

	void Ship::update(Gamemode* gm, const float dt) {
	}

	void Ship::draw(Gamemode* gm) {
		auto& window = gm->getWindow();

		shape.setPosition(position);
		window.draw(shape);
	}
}