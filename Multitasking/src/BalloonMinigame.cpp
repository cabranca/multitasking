#include "BalloonMinigame.h"

#include <imgui.h>

#include <Cabrankengine/Core/AudioEngine.h>
#include <Cabrankengine/Core/Application.h>
#include <Cabrankengine/Core/Input.h>
#include <Cabrankengine/Core/Logger.h>
#include <Cabrankengine/Core/Window.h>
#include <Cabrankengine/Renderer/RenderCommand.h>
#include <Cabrankengine/Renderer/Renderer2D.h>

using namespace glm;
using namespace cabrankengine;

namespace multitasking {

	BalloonMinigame::BalloonMinigame() {
		m_Balloon.Texture = Texture2D::create("assets/textures/balloon.png");
	}

	void BalloonMinigame::onUpdate(Timestep delta) {
		if (m_Active && Input::isMouseButtonPressed(Mouse::Button0)) {
			checkMouseHit();
		}
		updatePosition(delta);
		checkCollision();
		render();
	}

#ifdef CE_DEBUG
	void BalloonMinigame::onImGuiRender() {
		if (!m_Active)
			return;

		ImGui::Begin("Settings");

		ImGui::InputFloat("Gravity", &c_Gravity);
		ImGui::InputFloat("Fall Velocity", &c_FallVelocity);
		ImGui::InputFloat("Hit Force", &c_HitForce);
		ImGui::InputFloat("Drag", &c_Drag);

		ImGui::End();
	}
#else
	void BalloonMinigame::onImGuiRender() {}
#endif

	void BalloonMinigame::checkMouseHit() {
		auto& window = Application::get().getWindow();
		float windowWidth = (float)window.getWidth();
		float windowHeight = (float)window.getHeight();
		auto [mouseX, mouseY] = Input::getMousePosition();

		auto mouseNormalCoords = vec2((mouseX - windowWidth / 2.f), (-mouseY + windowHeight / 2.f)) / (windowHeight / 2.f);

		vec2 diff(m_Balloon.Position - mouseNormalCoords);
		float distance = sqrt(dot(diff, diff));
		if (distance < m_Balloon.Radius) {
			m_Balloon.Velocity = diff * c_HitForce;
			AudioEngine::playAudio("assets/sounds/balloon.wav", false);
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
		if (abs(m_Balloon.Position.x) + m_Balloon.Radius > 16.f / 9.f) {
			m_Balloon.Position.x = clamp(m_Balloon.Position.x, -16.f / 9.f + m_Balloon.Radius, 16.f / 9.f - m_Balloon.Radius);
			m_Balloon.Velocity.x *= -1.f;
		}

		if (m_Balloon.Position.y - m_Balloon.Radius < -1.f) {
			m_WinLoseCallback(false);
		}
			
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


