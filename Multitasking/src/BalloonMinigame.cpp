#include "BalloonMinigame.h"

#include <Cabrankengine/Core/Input.h>
#include <Cabrankengine/Core/Logger.h>
#include <Cabrankengine/Renderer/RenderCommand.h>
#include <Cabrankengine/Renderer/Renderer2D.h>

using namespace glm;
using namespace cabrankengine;

namespace multitasking {

	BalloonMinigame::BalloonMinigame() {
		m_Balloon.Texture = Texture2D::create("assets/textures/balloon.png");
	}

	void BalloonMinigame::onUpdate(Timestep delta) {
		if (Input::isMouseButtonPressed(Mouse::Button0)) {
			checkMouseHit();
		}
		updatePosition(delta);
		checkCollision();
		render();
	}

	void BalloonMinigame::onImGuiRender() {
	}

	void BalloonMinigame::checkMouseHit() {
		auto [mouseX, mouseY] = Input::getMousePosition();

		CE_TRACE("Mouse position in Viewport coordinates: [{0}, {1}]", mouseX, mouseY);

		auto mouseNormalCoords = vec2((mouseX - 800.f), (-mouseY + 450.f)) / 450.f;

		CE_TRACE("Mouse Position in normal coordinates: [{0}, {1}]", mouseNormalCoords.x, mouseNormalCoords.y);

		vec2 diff(m_Balloon.Position - mouseNormalCoords);
		float distance = sqrt(dot(diff, diff));
		if (distance < m_Balloon.Radius) {
			m_Balloon.Velocity = diff * c_HitForce;
		}
	}

	void BalloonMinigame::updatePosition(Timestep delta) {
		if (m_Balloon.Velocity.y > 0.f)
			m_Balloon.Velocity.y += c_Gravity * delta;
		else
			m_Balloon.Velocity.y = c_FallVelocity;

		
		m_Balloon.Velocity.x *= (1.0f - c_Drag * delta);
		if (abs(m_Balloon.Velocity.x) < 0.01f)
			m_Balloon.Velocity.x = 0.0f;

		m_Balloon.Position += m_Balloon.Velocity * static_cast<float>(delta);
	}

	void BalloonMinigame::checkCollision() {

	}

	void BalloonMinigame::render() {
		if (!m_Active)
			return;

		RenderCommand::setClearColor({ 0.2, 0.2, 0.2, 1.f });
		RenderCommand::clear();

		Renderer2D::beginScene(m_Camera->getCamera());

		Renderer2D::drawQuad(m_Balloon.Position, vec2(m_Balloon.Radius), m_Balloon.Texture);

		Renderer2D::endScene();
	}
}


