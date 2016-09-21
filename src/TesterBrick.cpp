#include <TesterBrick.hpp>

TesterBrick::TesterBrick() {
	constexpr float radius = 20.0f;
	shape.setFillColor({255, 255, 255, 255});
	shape.setPointCount(8);
	shape.setRadius(radius);
	shape.setOrigin({radius, radius});

	origin = shape.getOrigin();

	friction = 0.0f;
	position = {0.0f, 0.0f};
	velocity = {0.0f, 0.0f};

	for (int i = 0; i < shape.getPointCount(); ++i) {
		points.emplace_back(shape.getPoint(i));
	}

	calcNormals();

	lineVerts.push_back(sf::Vertex{sf::Vector2f{0.0f, 0.0f}, {255, 0, 0, 255}});
	lineVerts.push_back(sf::Vertex{sf::Vector2f{10.0f, 10.0f}, {255, 0, 0, 255}});
}

void TesterBrick::fixedUpdate(Gamemode *gm) {
	const auto& window = gm->getWindow();

	auto mousePos = sf::Mouse::getPosition(window);
	position = static_cast<sf::Vector2f>(mousePos);
}

void TesterBrick::update(Gamemode *gm, const float dt) {
}

void TesterBrick::draw(Gamemode *gm) {
	auto& window = gm->getWindow();

	shape.setPosition(position);
	window.draw(shape);

	for (int i=0; i+1 < lineVerts.size(); i += 2) {
		window.draw(static_cast<const sf::Vertex *>(&lineVerts[0] + i), 2, sf::Lines);
	}
}