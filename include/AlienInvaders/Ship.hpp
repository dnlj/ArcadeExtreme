#pragma once

#include <PhysicsObject.hpp>

namespace AlienInvaders {
	class Ship : public PhysicsObject {
		public:
			virtual void fixedUpdate(Gamemode* gm) override;
			virtual void update(Gamemode* gm, const float dt) override;
			virtual void draw(Gamemode* gm) override;
		private:
	};
}