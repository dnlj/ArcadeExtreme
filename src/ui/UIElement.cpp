#include <ui/UIElement.hpp>

namespace ui {
	UIElement::UIElement() {
	};

	UIElement::~UIElement() {
	};

	void UIElement::update(sf::RenderWindow &window) {
	}

	void UIElement::setPosition(float x, float y) {
		position.x = x;
		position.y = y;
	};
}