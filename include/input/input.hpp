#pragma once

#include <unordered_map>

#include <SFML/Graphics.hpp>

/**
 * @brief Contains input related functions
 * 
 * Allows you to create and get the state of a bind
 * 
 * Example usage:
 * @code
 * // When the program/settings are loaded
 * input::bind("jump", sf::Keyboard::Space)
 * 
 * // Later
 * if (input::wasPressed("jump")) {
 *		// do jump
 * }
 * @endcode
 */
namespace input {
	namespace detail {
		extern std::unordered_map<std::string, sf::Keyboard::Key> keyBinds;
		extern std::unordered_map<std::string, sf::Mouse::Button> mouseBinds;
		extern std::unordered_map<std::string, bool> pressed;
		extern std::unordered_map<std::string, bool> lastFrame;
	}
	
	/**
	 * @brief Associates a name and a keyboard key.
	 *
	 * @param name The name of the bind.
	 * @param key The keyboard key to bind to.
	 * @return void
	 */
	void bind(const std::string& name, sf::Keyboard::Key key);

	/**
	 * @brief Associates a name and a mouse button.
	 *
	 * @param name The name of the bind.
	 * @param button The mouse button to bind to.
	 * @return void
	 */
	void bind(const std::string& name, sf::Mouse::Button button);

	/**
	 * @brief Determines if a bind is currently pressed.
	 *
	 * Returns true if the bind is currently pressed otherwise returns false.
	 *
	 * @param name The name of the bind.
	 * @return bool
	 */
	bool isPressed(const std::string& name);

	/**
	 * @brief Determines if a bind was pressed this frame.
	 *
	 * Returns true if the bind was pressed this frame otherwise returns false.
	 *
	 * @param name The name of the bind.
	 * @return bool
	 */
	bool wasPressed(const std::string& name);

	/**
	 * @brief Determines if a bind was released this frame.
	 *
	 * Returns true if the bind is currently pressed otherwise returns false.
	 *
	 * @param name The name of the bind.
	 * @return bool
	 */
	bool wasReleased(const std::string& name);


	/**
	* @brief Used to update the input for the current frame.
	*
	* Updates all the bind/key pair information for the frame.
	* Should be called once per frame to ensure the bind information is kept current.
	*
	* @return void
	*/
	void update();
}