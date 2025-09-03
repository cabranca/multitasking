#include "BalloonMinigame.h"

#include <Cabrankengine/Core/Input.h>
#include <Cabrankengine/Renderer/RenderCommand.h>

using namespace glm;
using namespace cabrankengine;

namespace multitasking {

	void BalloonMinigame::onUpdate(Timestep delta) {
		if (Input::isMouseButtonPressed(Mouse::Button0)) {
			checkCollision();
		}
		updatePosition(delta);
		render();
	}

	void BalloonMinigame::onImGuiRender() {
	}

	void BalloonMinigame::checkCollision() {
		auto [mouseX, mouseY] = Input::getMousePosition();

		// Transform mouse coordinates from viewport to normal
		// Or balloon coordinates from normal to viewport (I think this is easier).
		vec2 diff(m_Balloon.Position - vec2(mouseX, mouseY));
		float distance = sqrt(dot(diff, diff));
		if (distance < m_Balloon.Radius) {
			m_Balloon.Velocity = normalize(diff) * distance * c_HitForce;
		}
	}

	void BalloonMinigame::updatePosition(Timestep delta) {
		if (m_Balloon.Velocity.y > 0.f)
			m_Balloon.Velocity.y += c_Gravity * delta;
		else
			m_Balloon.Velocity.y = c_FallVelocity;

		m_Balloon.Position += m_Balloon.Velocity * static_cast<float>(delta);
	}

	void BalloonMinigame::render() {
		RenderCommand::setClearColor({ 0.2, 0.2, 0.2, 1.f });
		RenderCommand::clear();
	}
}


