#pragma once

// C++ STD
#include <vector>

// Arcade Extreme
#include <Gamemode.hpp>
#include <AlienInvaders/Alien.hpp>
#include <AlienInvaders/Ship.hpp>

namespace AlienInvaders {
	class AlienInvaders : public Gamemode {
		public:
			AlienInvaders(sf::RenderWindow& window, float fixedTimeStep);
			virtual ~AlienInvaders();

			virtual void fixedUpdate() override;
			virtual void update(const float dt) override;
			virtual void draw() override;

		private:
			std::vector<Alien> aliens;
			Ship ship;
	};
}
