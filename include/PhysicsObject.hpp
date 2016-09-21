#pragma once

// C++ STD
#include <iostream>
#include <vector>

// SFML
#include <SFML/Graphics.hpp>

// ArcadeExtreme
#include <util/util.hpp>
#include <util/vector/vector.hpp>
#include <CollisionData.hpp>
#include <GameObject.hpp>

// TODO: Document

class PhysicsObject : public GameObject {
	public:
		PhysicsObject();
		virtual ~PhysicsObject();

		virtual void fixedUpdate(Gamemode* gm) override;
		
		void setVelocity(sf::Vector2f vel);
		sf::Vector2f getVelocity() const;

		void setFriction(float fric);
		float getFriction() const;

		std::vector<sf::Vector2f> getPoints() const;
		std::vector<sf::Vector2f> getPointsGlobal() const;
		std::vector<sf::Vector2f> getNormals() const;
		sf::Vector2f getOrigin() const;

		bool collidesWith(const PhysicsObject& other) const;
		CollisionData getCollision(const PhysicsObject& other) const;


	protected:
		float friction;
		sf::Vector2f velocity;
		sf::Vector2f origin;
		std::vector<sf::Vector2f> points;
		std::vector<sf::Vector2f> normals;

		void calcNormals();
};