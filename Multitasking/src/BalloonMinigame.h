#pragma once

#include <glm/glm.hpp>

#include "Minigame.h"

namespace multitasking {

	class BalloonMinigame : public Minigame {
	public:
		virtual void onUpdate(cabrankengine::Timestep delta) override;
		virtual void onImGuiRender() override;

	private:
		void checkCollision();
		void updatePosition(cabrankengine::Timestep delta);
		void render();

		struct Balloon {
			glm::vec2 Position;
			glm::vec2 Velocity;
			float Radius;
		};

		Balloon m_Balloon;
	};
}
