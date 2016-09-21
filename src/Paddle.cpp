#include <Paddle.hpp>


Paddle::Paddle(float width, float height) : moveSpeed{350.0f} {
	shape.setSize({width, height});
	shape.setOrigin({width/2.0f, height/2.0f}); // Set the origin to the center of the shape

	origin = shape.getOrigin();
	
	friction = 0.000005f;
	position = {0.0f, 0.0f};
	velocity = {0.0f, 0.0f};

	for (int i = 0; i < shape.getPointCount(); ++i) {
		points.emplace_back(shape.getPoint(i));
	}

	calcNormals();
}


void Paddle::fixedUpdate(Gamemode *gm) {

	if (input::isPressed("left")) {
		velocity.x -= moveSpeed;
	}

	if (input::isPressed("right")) {
		velocity.x += moveSpeed;
	}

	PhysicsObject::fixedUpdate(gm);
}

void Paddle::update(Gamemode *gm, const float dt) {
}

void Paddle::draw(Gamemode *gm) {
	auto& window = gm->getWindow();

	shape.setPosition(position);
	window.draw(shape);
}

sf::Vector2f Paddle::getSize() {
	return shape.getSize();
}