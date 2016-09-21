#include <Wall.hpp>

Wall::Wall(float width, float height) {
	shape.setSize({width, height});
	shape.setOrigin({width / 2.0f, height / 2.0f}); // Set the origin to the center of the shape

	origin = shape.getOrigin();

	friction = 0.0f;
	position = {0.0f, 0.0f};
	velocity = {0.0f, 0.0f};

	for (int i = 0; i < shape.getPointCount(); ++i) {
		points.emplace_back(shape.getPoint(i));
	}

	calcNormals();
}


void Wall::fixedUpdate(Gamemode* gm) {
}

void Wall::update(Gamemode* gm, const float dt) {
}

void Wall::draw(Gamemode* gm) {
	auto& window = gm->getWindow();

	shape.setPosition(position);
	window.draw(shape);
}