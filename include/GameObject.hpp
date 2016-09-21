#pragma once

// SFML
#include <SFML/Graphics.hpp>

// ArcadeExtreme
#include <Gamemode.hpp>

/**
 * @brief The base class for a GameObject.
 * 
 * A GameObect represents any object in the game world.
 */
class GameObject {
	public:
		GameObject();
		virtual ~GameObject();

		/**
		 * @brief Called at a fixed rate that is determined by the Gamemode.
		 * 
		 * This method should be called at a rate of Gamemode::fixedTimeStep. @n
		 * It is the Gamemode's job to call this method. @n
		 * The default implementation does nothing. @n
		 * GameObject::fixedUpdate is called before both GameObject::update and GameObject::draw. @n
		 * @p *gm is not stored by the GameObject. @n
		 * 
		 * @param[in] gm - The gamemode that this GameObject is in.
		 * @return void
		 */
		virtual void fixedUpdate(Gamemode* gm);

		/**
		 * @brief Called once per frame.
		 *
		 * It is the Gamemode's job to call this method once per frame. @n
		 * The default implementation does nothing. @n
		 * GameObject::update is called after GameObject::fixedUpdate and before GameObject::draw. @n
		 * @p *gm is not stored by the GameObject. @n
		 *
		 * @param[in] gm - The gamemode that this GameObject is in.
		 * @param[in] dt - Delta time, the time that has passed since the last frame.
		 * @return void
		 */
		virtual void update(Gamemode* gm, const float dt);

		/**
		 * @brief Called once per frame. Should be used to do any rendering this object requires.
		 *
		 * It is the Gamemode's job to call this method once per frame. @n
		 * GameObject::draw is called after both GameObject::fixedUpdate and GameObject::update. @n
		 * @p *gm is not stored by the GameObject. @n
		 *
		 * @param[in] gm - The gamemode that this GameObject is in.
		 * @return void
		 */
		virtual void draw(Gamemode* gm) = 0;
		
		/**
		 * @brief Sets the position of the GameObject.
		 *
		 * @param[in] pos - The position to set the GameObject to.
		 * @return void
		 */
		void setPosition(sf::Vector2f pos);

		/**
		* @brief Gets the position of the GameObject.
		* 
		* @return sf::Vector2f
		*/
		sf::Vector2f getPosition() const;

	protected:
		sf::Vector2f position;
		bool enabled;
};