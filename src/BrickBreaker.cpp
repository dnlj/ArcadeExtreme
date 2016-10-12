// Arcade
#include <BrickBreaker.hpp>

BrickBreaker::BrickBreaker(sf::RenderWindow &window, float fixedTimeStep)
		: Gamemode{window, fixedTimeStep},
		scrw{static_cast<float>(window.getSize().x)},
		scrh{static_cast<float>(window.getSize().y)},
		paddle{200.0f, 30.0f},
		ball{25.0f, 16},
		walls{},
		font{},
		score{}
		{

	font.loadFromFile("C:/Windows/Fonts/arial.ttf");

	scoreText.setFont(font);
	scoreText.setCharacterSize(32);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setOutlineColor(sf::Color::Black);
	scoreText.setOutlineThickness(3);
	scoreText.setPosition(scrw * 0.01f, scrw * 0.01f);
	
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
			const float percentY = static_cast<float>(y) / static_cast<float>(brickCountY);
			const float percentX = static_cast<float>(x) / static_cast<float>(brickCountX);

			bricks.back().setColor(util::toColor(
				1.0f,
				percentY,
				percentY
			));
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
		return reflection;
	}

	bool handleCollision(Ball& ball, PhysicsObject& fixedObject, bool respond = true) {
		auto collision = ball.getCollision(fixedObject);

		if (collision.collided && respond) {
			// Get the vector needed to move movingObject out of fixedObject
			auto offset = collision.axis * collision.distance;
			
			// Move movingObject out of fixedObject
			ball.setPosition(ball.getPosition() + offset);

			// Handle bounce
			auto v = ball.getVelocity();
			auto n = collision.axis;
			ball.setVelocity(getReflectionVector(n, v));

			// Bounce effect
			ball.bounceEffect();
		}

		return collision.collided;
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

		if (handleCollision(ball, brick)) {
			// The brick has been hit. Disable it.
			brick.setEnabled(false);
			score += 10;
		}
	}

	// Walls
	for (int i=0; i < walls.size(); ++i) {
		auto &wall = walls[i];
		wall.fixedUpdate(this);

		if (handleCollision(ball, wall, i != 1) && i == 1) {
			// Set it back to the center
			ball.setPosition({scrw / 2.0f, scrh / 2.0f});

			// Give the ball a random velocity
			float angle = util::getRandom(0.0f, 360.0f) * util::degToRad;
			ball.setVelocity(sf::Vector2f{cosf(angle), sinf(angle)} * 500.0f);
		}
	}

	// Paddle
	if (handleCollision(ball, paddle)) {
		// Allow the paddle to move the ball some
		auto motion = paddle.getVelocity() * 0.5f;

		// If the ball is going faster then sqrt(speedLimitSquared) slow it down when it hits the paddle
		auto v = ball.getVelocity();
		float speedSquared = util::vector::squaredNorm(v);
		constexpr float speedLimitSquared = 800.0f * 800.0f;
		float slowMulti = speedSquared < speedLimitSquared ? 1.0f : 0.75f;

		// Update the velocity
		ball.setVelocity(v * slowMulti + motion);
	}

	clampMinSpeed(timeStep);
	clampMaxSpeed(timeStep);

	////////////////////////////////////////
	// TODO: JUST FOR TESTING
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

	// Bricks
	for (auto &brick : bricks) {
		brick.update(this, dt);
	}

	// Walls
	for (auto &wall : walls) {
		wall.update(this, dt);
	}
}

void BrickBreaker::draw() {
	testBrick.draw(this);
	paddle.draw(this);
	ball.draw(this);
	
	// Bricks
	for (auto &brick : bricks) {
		brick.draw(this);
	}

	// Walls
	for (auto &wall : walls) {
		wall.draw(this);
	}

	// Score
	{
		scoreText.setString(std::to_string(score));
		window.draw(scoreText);
	}
	
}

void BrickBreaker::clampMinSpeed(const float timeStep) {
	// The minimum speed on each axis
	constexpr float minY = 150.0f;
	constexpr float minX = 100.0f;
	
	// The amount to increase by on each axis
	constexpr float increaseAmountY = 20.0f;
	constexpr float increaseAmountX = 10.0f;
	auto vel = ball.getVelocity();

	// If the ball is moving to slower than min_ increase it's _ component by increaseAmmount_ every second.
	// This helps keep the game moving. It also prevents the ball from getting stuck.
	if (vel.x != 0.0f || vel.y != 0.0f) {
		if (fabsf(vel.y) < minY) {
			// Increase velocity
			vel.y += std::copysignf(increaseAmountY * timeStep, vel.y);
		}

		if (fabsf(vel.x) < minX) {
			// Increase velocity
			vel.x += std::copysignf(increaseAmountX * timeStep, vel.x);
		}

		// Update velocity
		ball.setVelocity(vel);
	}
}

void BrickBreaker::clampMaxSpeed(const float timeStep) {
	// The maximum velocity on each axis
	constexpr float maxY = 500.0f;
	constexpr float maxX = 750.0f;
	auto vel = ball.getVelocity();

	// Clamp velocity
	vel.x = util::clamp(-maxX, maxX, vel.x);
	vel.y = util::clamp(-maxY, maxY, vel.y);

	// Update velocity
	ball.setVelocity(vel);
}