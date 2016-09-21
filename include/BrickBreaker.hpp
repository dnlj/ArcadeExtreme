#pragma once

// C++ STD
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

// ArcadeExtreme
#include <util/util.hpp>
#include <util/vector/vector.hpp>
#include <Gamemode.hpp>
#include <Ball.hpp>
#include <Paddle.hpp>
#include <Brick.hpp>
#include <TesterBrick.hpp>
#include <Wall.hpp>

/**
 * @brief A Breakout style Gamemode.
 */ 
class BrickBreaker : public Gamemode {
	public:
		BrickBreaker(sf::RenderWindow& window, float fixedTimeStep);
		virtual ~BrickBreaker();

		virtual void fixedUpdate() override;
		virtual void update(const float dt) override;
		virtual void draw() override;

	private:
		float scrw;
		float scrh;
		Paddle paddle;
		Ball ball;
		TesterBrick testBrick;
		std::vector<Brick> bricks;
		std::vector<Wall> walls;
};