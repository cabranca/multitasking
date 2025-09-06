#include "GameManager.h"

#include <memory>
#include <imgui.h>

#include <Cabrankengine/Core/AudioEngine.h>
#include <Cabrankengine/Core/Application.h>
#include <Cabrankengine/Core/Core.h>
#include <Cabrankengine/Core/Logger.h>
#include <Cabrankengine/Core/Window.h>
#include<Cabrankengine/Events/KeyEvent.h>
#include <Cabrankengine/Renderer/OrthographicCameraController.h>

using namespace cabrankengine;

namespace multitasking {

	GameManager::GameManager(std::array<Minigame*, 3> minigames) :
	m_CurrentTabIndex(0), m_minigames(minigames) {
		m_Camera = std::make_shared<OrthographicCameraController>(1600.0f / 900.0f);
		for (auto game : m_minigames) {
			game->setCamera(m_Camera);
			game->setWinLoseCallback([&](bool win) {
				m_FinalMessage = win ? "GANASTE" : "PERDISTE";
				for (auto& minigame : m_minigames) minigame->finishGame();
				});
		}
		m_minigames[m_CurrentTabIndex]->setActive(true);
		AudioEngine::playAudio("assets/sounds/elevator_music.mp3", true);
	}

	void GameManager::onUpdate(Timestep delta) {
		// Update timer
	}

	void GameManager::onImGuiRender() {
		if (m_FinalMessage.empty()) return;

		auto& window = Application::get().getWindow();
		float windowWidth = (float)window.getWidth();
		float windowHeight = (float)window.getHeight();

		// calcular tamaño del texto con la fuente actual
		ImFont* font = ImGui::GetFont();
		ImVec2 textSize = font->CalcTextSizeA(font->LegacySize * m_FontScale, FLT_MAX, 0.0f, m_FinalMessage.c_str());

		// centrar en pantalla
		ImVec2 pos(
			(windowWidth - textSize.x) * 0.5f,
			(windowHeight - textSize.y) * 0.5f
		);

		// dibujar texto
		ImGui::GetForegroundDrawList()->AddText(
			font,
			font->LegacySize * m_FontScale,
			pos,
			IM_COL32_WHITE,
			m_FinalMessage.c_str()
		);
	}

	void GameManager::onEvent(Event& event) {
		if (!m_FinalMessage.empty()) return;

		EventDispatcher e(event);
		e.dispatch<KeyPressedEvent>(BIND_EVENT_FN(&GameManager::changeTab, this));
	}

	bool GameManager::changeTab(KeyPressedEvent& event) {
		bool res = false;
		m_minigames[m_CurrentTabIndex]->setActive(false);

		if (event.getKeyCode() == Key::Q) {
			m_CurrentTabIndex = --m_CurrentTabIndex % m_minigames.size();
			res = true;
		}
		else if (event.getKeyCode() == Key::E) {
			m_CurrentTabIndex = ++m_CurrentTabIndex % m_minigames.size();
			res = true;
		}

		m_minigames[m_CurrentTabIndex]->setActive(true);
		return res;
	}
}