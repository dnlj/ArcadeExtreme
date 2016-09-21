#include <GameObject.hpp>

GameObject::GameObject() : enabled{true}, position{0, 0} {
}

GameObject::~GameObject() {
}

void GameObject::fixedUpdate(Gamemode *gm) {
}

void GameObject::update(Gamemode *gm, const float dt) {
}

void GameObject::setPosition(sf::Vector2f pos) {
	position = pos;
}

sf::Vector2f GameObject::getPosition() const {
	return position;
}