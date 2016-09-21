#include <PhysicsObject.hpp>

PhysicsObject::PhysicsObject() : origin{0, 0} {
}

PhysicsObject::~PhysicsObject() {
}

void PhysicsObject::setVelocity(sf::Vector2f vel) {
	velocity = vel;
}

sf::Vector2f PhysicsObject::getVelocity() const {
	return velocity;
}

void PhysicsObject::setFriction(float fric) {
	friction = fric;
}

float PhysicsObject::getFriction() const {
	return friction;
}

void PhysicsObject::fixedUpdate(Gamemode *gm) {
	const float timeStep = gm->getFixedTimeStep();
	position += velocity * timeStep;
	velocity *= powf(friction, timeStep); // TODO: How to friction independed of frame rate, halp
}

std::vector<sf::Vector2f> PhysicsObject::getPoints() const {
	return points;
};

std::vector<sf::Vector2f> PhysicsObject::getPointsGlobal() const {
	std::vector<sf::Vector2f> ret{points.size()};

	for (size_t i=0; i < points.size(); ++i) {
		// Transform the point into world space
		ret[i] = points[i] + position - origin;
	}

	return ret;
};

std::vector<sf::Vector2f> PhysicsObject::getNormals() const {
	return normals;
}

void PhysicsObject::calcNormals() {
	size_t pointsSize = points.size();
	normals.resize(pointsSize);
	normals.shrink_to_fit();

	for (size_t first = 0; first < pointsSize; ++first) {
		// Get next point and limits(wraps) to range [0, pointSize)
		auto second = (first + 1) % pointsSize;
		
		// Calculate the normal and normalize it
		normals[first] = util::vector::normalize({points[first].x - points[second].x, points[second].y - points[first].y});
	}
}

sf::Vector2f PhysicsObject::getOrigin() const {
	return origin;
}

namespace { // TODO: Move into utility class or something
	class Projection {
		public:
			Projection(float min, float max) : min(min), max(max) {
			}

			bool overlaps(const Projection &b) {
				return !(min > b.max || b.min > max);
			}

			float getOverlap(const Projection &b) {
				return std::min(max, b.max) - std::max(min, b.min);
			}

			float min;
			float max;
	};

	Projection project(const sf::Vector2f &axis, const std::vector<sf::Vector2f> &points) {
		float min = util::vector::dot(axis, points[0]);
		float max = min;

		for (int i = 1; i < points.size(); ++i) {
			float d = util::vector::dot(axis, points[i]);
			if (d < min) {
				min = d;
			} else if (d > max) {
				max = d;
			}
		}

		return {min, max};
	}
}

bool PhysicsObject::collidesWith(const PhysicsObject &other) const {
	const auto &otherPoints = other.getPointsGlobal();
	const auto &thisPoints = getPointsGlobal(); // TODO: Delete this whenever you cache the points and just use that variable
	const auto &otherNormals = other.getNormals();
	const auto numNormals1 = otherNormals.size();
	const auto numNormals2 = normals.size();
	const auto numTotalNormals = numNormals1 + numNormals2;

	for (size_t i = 0; i < numTotalNormals; ++i) {
		// Get an axis from one of the objects normals
		const auto &axis = i < numNormals1 ? otherNormals[i] : normals[i - numNormals1];

		// Project the points of each object onto axis
		Projection thisProj = project(axis, thisPoints);
		Projection otherProj = project(axis, otherPoints);
		
		if (!thisProj.overlaps(otherProj)) {
			return false;
		}
	}

	return true;
}

CollisionData PhysicsObject::getCollision(const PhysicsObject &other) const {
	const auto &otherPoints = other.getPointsGlobal();
	const auto &thisPoints = getPointsGlobal(); // TODO: Delete this whenever you cache the points and just use that variable
	const auto &otherNormals = other.getNormals();
	const auto numNormals1 = otherNormals.size();
	const auto numNormals2 = normals.size();
	const auto numTotalNormals = numNormals1 + numNormals2;

	CollisionData data{true, FLT_MAX, {0, 0}};

	for (size_t i=0; i < numTotalNormals; ++i) {
		// Get an axis from one of the objects normals
		const auto &axis = i < numNormals1 ? otherNormals[i] : normals[i - numNormals1];
	
		// Project the points of each object onto axis
		Projection thisProj = project(axis, thisPoints);
		Projection otherProj = project(axis, otherPoints);
	
		float overlap = thisProj.getOverlap(otherProj);

		// Check if the projections overlap
		if (overlap > 0.0f) {
			if (overlap < data.distance) {
				data.distance = overlap;
	
				// Make sure the axis is in the correct direction
				sf::Vector2f dirVector = getPosition() - other.getPosition();
				if (util::vector::dot(dirVector, axis) < 0.0f) {
					data.axis = -axis;
				} else {
					data.axis = axis;
				}
			}
		} else {
			data.collided = false;
		}
	}

	return data;
}