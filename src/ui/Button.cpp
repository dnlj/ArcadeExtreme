#include <ui/Button.hpp>


namespace ui {
	Button::Button() : Button(100, 50) {
	};

	Button::Button(int width, int height) :
			shape{{static_cast<float>(width), static_cast<float>(height)}},
			doClickFunction{},
			text{} {

		shape.setFillColor(sf::Color::Cyan);

		text.setFont(util::getFont());
		text.setCharacterSize(32);
		text.setFillColor(sf::Color::White);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(2);
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
		text.setPosition(position);

		window.draw(shape);
		window.draw(text);
	}

	void Button::setDoClick(std::function<void(void)> func) {
		doClickFunction = func;
	}

	sf::Vector2f Button::getSize() const {
		return shape.getSize();
	}

	void Button::setText(const std::string& str) {
		text.setString(str);

		const auto& rectSize = shape.getSize();
		const auto& textSize = text.getLocalBounds();
		sf::Vector2f origin{};

		// NOTE: I divide by 2.8 here instead of 2.0 because of the abnormal line height.
		// Different fonts may need different factors.
		origin.x = -(rectSize.x - textSize.width) / 2.0f;
		origin.y = -(rectSize.y - textSize.height) / 2.8f;

		text.setOrigin(origin);
	}
}