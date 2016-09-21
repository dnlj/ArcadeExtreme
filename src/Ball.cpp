#include <Ball.hpp>

Ball::Ball(float radius, unsigned int pointCount) : shape{radius, pointCount} {
	shape.setFillColor({255, 0, 0});
	shape.setOrigin({radius, radius});

	origin = shape.getOrigin();

	friction = 1.0f;
	position = {0.0f, 0.0f};
	velocity = {0.0f, 0.0f};
	
	for (int i=0; i < shape.getPointCount(); ++i) {
		points.emplace_back(shape.getPoint(i));
	}

	calcNormals();

	std::cout << "origin: " << origin.x << std::endl;
}

void Ball::fixedUpdate(Gamemode *gm) {
	position += velocity * gm->getFixedTimeStep();
}

void Ball::update(Gamemode *gm, const float dt) {
}

void Ball::draw(Gamemode *gm) {
	auto& window = gm->getWindow();

	shape.setPosition(position);
	window.draw(shape);
}

float Ball::getRadius() const {
	return shape.getRadius();
}