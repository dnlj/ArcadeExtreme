#include <BrickBreaker.hpp>

BrickBreaker::BrickBreaker(sf::RenderWindow &window, float fixedTimeStep)
		: Gamemode{window, fixedTimeStep},
		scrw{static_cast<float>(window.getSize().x)},
		scrh{static_cast<float>(window.getSize().y)},
		paddle{150.0f, 30.0f},
		ball{25.0f, 16},
		walls{} {
	
	paddle.setPosition({scrw / 2.0f, scrh - 10.0f - paddle.getSize().y / 2.0f});

	ball.setPosition({scrw / 2.0f, scrh / 2.0f});
	ball.setVelocity({0.0f, -500.0f});

	constexpr int brickCountX = 20;
	constexpr int brickCountY = 5;
	const float bottomPadding = scrh * 0.6666666666f;
	const float brickWidth = scrw / brickCountX;
	const float brickHeight = (scrh - bottomPadding) / brickCountY;
	const float halfbrickWidth = brickWidth / 2.0f;
	const float halfbrickHeight = brickHeight / 2.0f;

	for (int x=0; x < brickCountX; ++x) {
		for (int y=0; y < brickCountY; ++y) {
			bricks.emplace_back(brickWidth, brickHeight);
			bricks.back().setPosition({x * brickWidth + halfbrickWidth, y * brickHeight + halfbrickHeight});
		}
	}

	// Create the walls
	constexpr float wallThickness = 500.0f;
	constexpr float halfWallThickness = wallThickness / 2.0f;

	// Top wall
	walls.emplace_back(scrw, wallThickness);
	walls.back().setPosition({scrw / 2.0f, -halfWallThickness});

	// Bottom wall
	walls.emplace_back(scrw, wallThickness);
	walls.back().setPosition({scrw / 2.0f, scrh + halfWallThickness + 2.0f * ball.getRadius()});

	// Left wall
	walls.emplace_back(wallThickness, scrh);
	walls.back().setPosition({-halfWallThickness, scrh / 2.0f});

	// Right wall
	walls.emplace_back(wallThickness, scrh);
	walls.back().setPosition({scrw + halfWallThickness, scrh / 2.0f});
}

BrickBreaker::~BrickBreaker() {
}

namespace {
	sf::Vector2f getReflectionVector(sf::Vector2f normal, sf::Vector2f incident) {
		sf::Vector2f reflection = incident - 2 * util::vector::dot(incident, normal) * normal;
		//return util::vector::normalize(reflection);
		return reflection;
	}
}

void BrickBreaker::fixedUpdate() {
	const float timeStep = getFixedTimeStep();
	ball.fixedUpdate(this);
	paddle.fixedUpdate(this);

	// Bricks
	for (auto &brick : bricks) {
		if (!brick.getEnabled()) { continue; }

		brick.fixedUpdate(this);
		auto collision = ball.getCollision(brick);
		
		// TODO: move this into a function to avoid duplicate code
		if (collision.collided) {
			auto offset = collision.axis * collision.distance;
			ball.setPosition(ball.getPosition() + offset);

			// Handle bounce
			auto v = ball.getVelocity();
			auto n = collision.axis;
			brick.setEnabled(false);
			ball.setVelocity(getReflectionVector(n, v));
		}
	}

	// Walls
	for (int i=0; i < walls.size(); ++i) {
		auto &wall = walls[i];
		wall.fixedUpdate(this);
		auto collision = ball.getCollision(wall);

		// TODO: move this into a function to avoid duplicate code
		if (collision.collided) {
			auto offset = collision.axis * collision.distance;
			ball.setPosition(ball.getPosition() + offset);

			if (i == 1) { // index 1 (item 2) Is the bottom wall
				ball.setPosition({scrw / 2.0f, scrh / 2.0f});
			
				float angle = util::getRandom(0.0f, 360.0f) * util::degToRad;
				ball.setVelocity(sf::Vector2f{cosf(angle), sinf(angle)} * 500.0f);
			} else {
				// Handle bounce
				auto v = ball.getVelocity();
				auto n = collision.axis;
				ball.setVelocity(getReflectionVector(n, v));
			}
		}
	}

	// Paddle
	{
		auto collision = ball.getCollision(paddle);

		// TODO: move this into a function to avoid duplicate code
		if (collision.collided) {
			auto offset = collision.axis * collision.distance;
			ball.setPosition(ball.getPosition() + offset);

			// Handle bounce
			auto v = ball.getVelocity();
			auto n = collision.axis;
			auto motion = paddle.getVelocity() * 0.5f; // Add some of the paddles motion to the ball to give the player some control over the ball
			ball.setVelocity(motion + getReflectionVector(n, v));

			// If the ball is going faster then sqrt(speedLimitSquared) slow it down when it hits the paddle
			v = ball.getVelocity();
			float speedSquared = util::vector::squaredNorm(v);
			constexpr float speedLimitSquared = 800.0f * 800.0f;
			float slowMulti = speedSquared < speedLimitSquared ? 1.0f : 0.75f;
			ball.setVelocity(v * slowMulti);
		}
	}

	// TODO: Put this into its own private/protected method
	{ // Prevent the ball from moving to slow
		constexpr float minY = 150.0f;
		constexpr float minX = 100.0f;
		constexpr float increaseAmmountY = 20.0f;
		constexpr float increaseAmmountX = 10.0f;
		auto vel = ball.getVelocity();

		// If the ball is moving to slower than min_ increase it's _ component by increaseAmmount_ every second.
		// This helps keep the game moving, and it prevents the ball from getting stuck.
		if (vel.x != 0.0f || vel.y != 0.0f) {
			if (fabsf(vel.y) < minY) {
				vel.y += std::copysignf(increaseAmmountY * timeStep, vel.y);
				ball.setVelocity(vel);
			}

			if (fabsf(vel.x) < minX) {
				vel.x += std::copysignf(increaseAmmountX * timeStep, vel.x);
				ball.setVelocity(vel);
			}
		}
	}

	////////////////////////////////////////
	/// TODO: JUST FOR TESTING
	////////////////////////////////////////
	bricks[0].setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
	testBrick.lineVerts = {};
	testBrick.fixedUpdate(this);
	for (int i=1; i < bricks.size(); ++i) {
		const auto &brick = bricks[i];
		auto collision = testBrick.getCollision(brick);
	
		if (collision.collided) {
			auto offset = collision.axis * (collision.distance + 0.1f);
			sf::Vertex vert1{testBrick.getPosition(), sf::Color::Red};
			sf::Vertex vert2{testBrick.getPosition() + offset, sf::Color::Red};
			testBrick.lineVerts.push_back(vert1);
			testBrick.lineVerts.push_back(vert2);
		}
	}
};

void BrickBreaker::update(float dt) {
	testBrick.update(this, dt);
	paddle.update(this, dt);
	ball.update(this, dt);

	for (auto &brick : bricks) {
		brick.update(this, dt);
	}

	for (auto &wall : walls) {
		wall.update(this, dt);
	}
}

void BrickBreaker::draw() {
	testBrick.draw(this);
	paddle.draw(this);
	ball.draw(this);
	
	for (auto &brick : bricks) {
		brick.draw(this);
	}

	for (auto &wall : walls) {
		wall.draw(this);
	}
}