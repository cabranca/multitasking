#include "PopcornMinigame.h"

#include <Cabrankengine/Core/AudioEngine.h>
#include <Cabrankengine/Core/Application.h>
#include <Cabrankengine/Core/Input.h>
#include <Cabrankengine/Core/Window.h>
#include <Cabrankengine/Renderer/RenderCommand.h>
#include <Cabrankengine/Renderer/Renderer2D.h>
#include <cstdlib>
#include <random>

constexpr float PI = 3.14159265358979323846f; // Define PI constant if not available
std::mt19937 rng{ std::random_device{}() };
std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * PI);
std::uniform_real_distribution<float> popcornAngleDist(60.0f, 120.0f);
std::uniform_real_distribution<float> popcornSpeedDist(3.0f, 6.0f);

using namespace glm;
using namespace cabrankengine;

namespace multitasking {

	PopcornMinigame::PopcornMinigame() {
		popcornMachineTexture = Texture2D::create("assets/textures/popcorn_machine.png");
		popcornTexture = Texture2D::create("assets/textures/popcorn.png");
	}

	void PopcornMinigame::onUpdate(Timestep delta) {
		if (m_Active && Input::isMouseButtonPressed(Mouse::Button0) && checkMouseCollision()) {
			spawnPopcorn(delta);
		}
		updatePopcornPosition(delta);
		processPopcornCollision();
		render();
	}

	void PopcornMinigame::onImGuiRender() {
	}

	void PopcornMinigame::updatePopcornPosition(Timestep delta) {
		for (auto& p : m_Popcorn) {
			if (!p.isOnGround) {
				p.Velocity.y += GRAVITY * delta;
			}
			p.Position += p.Velocity * static_cast<float>(delta);
		}
	}

	void PopcornMinigame::processPopcornCollision() {
		for (auto& p : m_Popcorn) {
			// If colliding with left or right wall, bounce back
			if (abs(p.Position.x) + p.CollisionRadius > 16.f / 9.f) {
				p.Position.x = clamp(p.Position.x, -16.f / 9.f + p.CollisionRadius, 16.f / 9.f - p.CollisionRadius);
				p.Velocity.x *= -0.7f;
			}
			// If colliding with floor, clamp position and remove velocity
			if (p.Position.y + p.CollisionRadius < -1.f) {
				p.Position.y = clamp(p.Position.y, -1.f + p.CollisionRadius, 1.f - p.CollisionRadius);
				p.Velocity = vec2(0.f);
				p.isOnGround = true;
			}
		}
	}

	bool PopcornMinigame::checkMouseCollision() {
		auto& window = Application::get().getWindow();
		float windowWidth = (float)window.getWidth();
		float windowHeight = (float)window.getHeight();
		auto [mouseX, mouseY] = Input::getMousePosition();

		auto mouseNormalCoords = vec2((mouseX - windowWidth / 2.f), (-mouseY + windowHeight / 2.f)) / (windowHeight / 2.f);

		vec2 diff(m_PopcornMachine.Position - mouseNormalCoords);
		float distance = sqrt(dot(diff, diff));
		
		if (distance < m_PopcornMachine.CollisionRadius) {
			return true;
		}
		return false;
	}

	void PopcornMinigame::spawnPopcorn(Timestep delta) {
		Popcorn p{};
		p.Position = m_PopcornMachine.Position;
		p.Rotation = angleDist(rng);

		float angle = popcornAngleDist(rng);
		float speed = popcornSpeedDist(rng);

		p.Velocity.x = cos(radians(angle)) * speed;
		p.Velocity.y = sin(radians(angle)) * speed;

		m_Popcorn.push_back(p);
		AudioEngine::playAudio("assets/sounds/popcorn.mp3", false);
	}

	void PopcornMinigame::render() {
		if (!m_Active) return;

		RenderCommand::setClearColor({ 0.2, 0.2, 0.2, 1.f });
		RenderCommand::clear();

		Renderer2D::beginScene(m_Camera->getCamera());
		
		Renderer2D::drawRotatedQuad(m_PopcornMachine.Position, m_PopcornMachine.TextureSize, m_PopcornMachine.Rotation, popcornMachineTexture);
		for (Popcorn p : m_Popcorn) {
			Renderer2D::drawRotatedQuad(p.Position, p.TextureSize, p.Rotation, popcornTexture);
		}

		Renderer2D::endScene();
	}
}


