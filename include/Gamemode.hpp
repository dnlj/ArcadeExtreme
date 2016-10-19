#pragma once

// C++ STD
#include <vector>
#include <memory>

// SFML
#include <SFML/Graphics.hpp>

/**
 * @brief
 */
class Gamemode {
	public:
		Gamemode(sf::RenderWindow& window, float fixedTimeStep);
		virtual ~Gamemode();

		/**
		 * @brief A general purpose method for updating things at a fixed rate.
		 *
		 * This method should be called at a rate of Gamemode::fixedTimeStep by the program. @n
		 * This method should be used to call GameObject::fixedUpdate on all GameObject's
		 * that belong to this Gamemode. @n
		 * Gamemode::fixedUpdate should called before both Gamemode::update and Gamemode::draw. @n
		 *
		 * @return void
		 */
		virtual void fixedUpdate() = 0;

		/**
		 * @brief A general purpose method for updating things once per frame.
		 *
		 * This method should be called once per frame by the program. @n
		 * Gamemode::update should be called after Gamemode::fixedUpdate and before Gamemode::draw. @n
		 * This method should be used to call GameObject::update on all GameObject's
		 * that belong to this Gamemode. @n
		 * 
		 * @param[in] dt - Delta time, the time that has passed since the last frame.
		 * @return void
		 */
		virtual void update(const float dt) = 0;

		/**
		 * @brief Called once per frame. Should be used to do all rendering for this Gamemode.
		 *
		 * This method should be called once per frame by the program. @n
		 * It is the Gamemode's job to call this method once per frame. @n
		 * Gamemode::draw should be called after both Gamemode::fixedUpdate and Gamemode::update. @n
		 *
		 * @return void
		 */
		virtual void draw() = 0;

		/**
		 * @brief Gets the window that uses this Gamemode.
		 *
		 * @return sf::RenderWindow& - The window that uses this Gamemode.
		 */
		sf::RenderWindow& getWindow() const;

		/**
		 * @brief Gets the Gamemode::fixedUpdate increments.
		 * 
		 * @return float - The Gamemode::fixedUpdate increments.
		 */
		float getFixedTimeStep() const;

		/**
		 * @brief
		 * 
		 */
		void setPaused(bool paused);

	protected:
		sf::RenderWindow &window;
		const float fixedTimeStep;
		bool paused;
};