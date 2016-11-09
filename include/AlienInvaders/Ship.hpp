#pragma once

// SFML
#include <SFML/Graphics.hpp>

// Arcade Exteme
#include <PhysicsObject.hpp>

namespace AlienInvaders {
	class Ship : public PhysicsObject {
		public:
			Ship();

			virtual void fixedUpdate(Gamemode* gm) override;
			virtual void update(Gamemode* gm, const float dt) override;
			virtual void draw(Gamemode* gm) override;

		private:
			float moveSpeed;
			sf::RectangleShape shape;
	};
}