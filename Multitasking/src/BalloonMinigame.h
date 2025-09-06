#pragma once

#include <glm/glm.hpp>

#include <Cabrankengine/Renderer/Texture.h>

#include "Minigame.h"

namespace multitasking {

	class BalloonMinigame : public Minigame {
	public:
		BalloonMinigame();

		virtual void onUpdate(cabrankengine::Timestep delta) override;
		virtual void onImGuiRender() override;

	private:
		void checkMouseHit();
		void updatePosition(cabrankengine::Timestep delta);
		void checkCollision();
		void render();

		struct Balloon {
			glm::vec2 Position = { 0.f, 0.f };
			glm::vec2 Velocity = { 0.f, 0.f };
			float Radius = 0.2f;
			cabrankengine::Ref<cabrankengine::Texture2D> Texture = nullptr;
		};

		Balloon m_Balloon;

		float c_Gravity = -10.f;
		float c_FallVelocity = -0.15f;
		float c_HitForce = 15.f;
		float c_Drag = 4.f; // coeficiente (0 = sin resistencia, 1 = se frena instantáneo)
	};
}
