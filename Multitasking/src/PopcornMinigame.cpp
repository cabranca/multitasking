#include "PopcornMinigame.h"

#include <Cabrankengine/Core/Input.h>
#include <Cabrankengine/Renderer/RenderCommand.h>
#include <Cabrankengine/Renderer/Renderer2D.h>
#include <cstdlib>
#include <random>

constexpr float PI = 3.14159265358979323846f; // Define PI constant if not available
std::mt19937 rng{ std::random_device{}() };
std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * PI);
std::uniform_real_distribution<float> popcornAngleDist(70.0f, 110.0f);
std::uniform_real_distribution<float> popcornSpeedDist(3.0f, 5.0f);

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
		updatePopcorn(delta);
		render();
	}

	void PopcornMinigame::onImGuiRender() {
	}

	void PopcornMinigame::updatePopcorn(Timestep delta) {
		for (int i = 0; i < m_Popcorn.size(); i++) {
			m_Popcorn[i].Velocity.y += GRAVITY * delta;
			m_Popcorn[i].Position += m_Popcorn[i].Velocity * static_cast<float>(delta);
		}
	}

	bool PopcornMinigame::checkMouseCollision() {
		auto [mouseX, mouseY] = Input::getMousePosition();

		auto mouseNormalCoords = vec2((mouseX - 800.f), (-mouseY + 450.f)) / 450.f;

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


