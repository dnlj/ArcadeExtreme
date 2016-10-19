#include <ui/Button.hpp>


namespace ui {
	Button::Button(int width, int height) :
			shape{{static_cast<float>(width), static_cast<float>(height)}},
			doClickFunction{} {

		shape.setFillColor(sf::Color::Cyan);
	}

	Button::~Button() {
	}

	void Button::update(sf::RenderWindow &window) {
		auto mousePos = sf::Mouse::getPosition(window);
		auto shapeSize = shape.getSize();

		if (input::wasPressed("click") && util::isInside(static_cast<sf::Vector2f>(mousePos), position, shapeSize)) {
			doClick();
		}
	}

	void Button::doClick() {
		if (doClickFunction) {
			doClickFunction();
		} else {
			std::cout << "Clicked\n";
			
			std::mt19937 mt(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
			std::uniform_int_distribution<int> rng(0, 255);
			auto r = static_cast<sf::Uint8>(rng(mt));
			auto g = static_cast<sf::Uint8>(rng(mt));
			auto b = static_cast<sf::Uint8>(rng(mt));
			shape.setFillColor(sf::Color{r, g, b, 255});
		}
	}

	void Button::draw(sf::RenderWindow &window) {
		shape.setPosition(position);
		window.draw(shape);
	}

	void Button::setDoClick(std::function<void(void)> func) {
		doClickFunction = func;
	}
}