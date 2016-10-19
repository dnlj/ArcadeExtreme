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
}

void Ball::fixedUpdate(Gamemode *gm) {
	const float timeStep = gm->getFixedTimeStep();
	
	// Update position
	position += velocity * timeStep;
}

void Ball::update(Gamemode *gm, const float dt) {
	auto scale = shape.getScale();

	// Decrease scale by 98% every second
	scale.x = scale.x * powf(0.02f, dt);
	scale.y = scale.y * powf(0.02f, dt);

	// Don't let scale go below 1.0f
	scale.x = std::max(1.0f, scale.x);
	scale.y = std::max(1.0f, scale.y);

	// Update scale
	shape.setScale(scale);

	// Update color
	float percentY = position.y / gm->getWindow().getSize().y;
	shape.setFillColor(util::toColor(
		1.0f,
		percentY,
		percentY
	));
}

void Ball::draw(Gamemode *gm) {
	auto& window = gm->getWindow();

	shape.setPosition(position);
	window.draw(shape);
}

float Ball::getRadius() const {
	return shape.getRadius();
}

void Ball::bounceEffect() {
	// The amount to scale by every bounce
	constexpr float scaleAmount = 1.70f;

	// If it has recently bounced dont do it again
	const auto scale = shape.getScale();
	if (scale.x > 1.1f || scale.y > 1.1f) { return; }

	// Scale
	float scaleX = scale.x * scaleAmount;
	float scaleY = scale.y * scaleAmount;
	
	// Update scale
	shape.setScale(scaleX, scaleY);
}