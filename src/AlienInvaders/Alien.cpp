// Arcade Extreme
#include <AlienInvaders/Alien.hpp>


namespace AlienInvaders {
	Alien::Alien() {
		setupShapes();
	}

	void Alien::fixedUpdate(Gamemode* gm) {
	}

	void Alien::update(Gamemode* gm, const float dt) {
	}

	void Alien::draw(Gamemode* gm) {
		auto& window = gm->getWindow();

		setShapePositions(position);
		drawShapes(window);		
	}

	int Alien::getHeight() const {
		return height;
	}

	void Alien::setupShapes() {
		constexpr float radius = 40.0f;
		constexpr float bodyWidth = radius * 2.0f;
		constexpr float bodyHeight = radius * 0.75f;
		constexpr float tenticleWidth = bodyWidth / 5.0f;
		constexpr float tenticleHeight = bodyHeight / 2.0f;

		{ // Top Semi Circle
			constexpr int roundCount = 12; // Number of points
			constexpr float accAmount = util::PI / (roundCount - 1.0f);
			float accumulator = 0.0f;

			topSemiCircle.setPointCount(roundCount);

			// Generate points
			for (int i = 0; i < roundCount; ++i, accumulator += accAmount) {
				const float x = radius * cosf(accumulator);
				const float y = radius * -sinf(accumulator); // This is negative because +y is down

				topSemiCircle.setPoint(i, {x, y});
			}

			// Set the origin at the center of ALL the shapes
			topSemiCircle.setOrigin({0.0f, bodyHeight / 2.0f});
		}

		{ // Body
			body.setSize({bodyWidth, bodyHeight});
			body.setOrigin({bodyWidth / 2.0f, bodyHeight / 2.0f});
		}

		{ // Tenticle 1
			tenticle1.setSize({tenticleWidth, tenticleHeight});
			tenticle1.setOrigin({bodyWidth / 2.0f, -bodyHeight / 2.0f});
		}

		{ // Tenticle 2
			tenticle2.setSize({tenticleWidth, tenticleHeight});
			tenticle2.setOrigin({tenticleWidth / 2.0f, -bodyHeight / 2.0f});
		}

		{ // Tenticle 3
			tenticle3.setSize({tenticleWidth, tenticleHeight});
			tenticle3.setOrigin({(-bodyWidth / 2.0f) + tenticleWidth, -bodyHeight / 2.0f});
		}

		height = static_cast<int>(radius + bodyHeight + tenticleHeight);
	}

	void Alien::setShapePositions(sf::Vector2f position) {
		topSemiCircle.setPosition(position);
		body.setPosition(position);
		tenticle1.setPosition(position);
		tenticle2.setPosition(position);
		tenticle3.setPosition(position);
	}

	void Alien::drawShapes(sf::RenderWindow& window) {
		window.draw(topSemiCircle);
		window.draw(body);
		window.draw(tenticle1);
		window.draw(tenticle2);
		window.draw(tenticle3);
	}
}