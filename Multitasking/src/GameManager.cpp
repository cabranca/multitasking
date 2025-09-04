#include "GameManager.h"

#include <memory>

#include <Cabrankengine/Core/Core.h>
#include<Cabrankengine/Events/KeyEvent.h>
#include <Cabrankengine/Renderer/OrthographicCameraController.h>

using namespace cabrankengine;

namespace multitasking {

	GameManager::GameManager(std::array<Minigame*, 2> minigames) : m_CurrentTabIndex(0), m_minigames(std::move(minigames)) {
		m_Camera = std::make_shared<OrthographicCameraController>(1600.0f / 900.0f);
		for (auto game : m_minigames) {
			game->setCamera(m_Camera);
		}
		m_minigames[m_CurrentTabIndex]->setActive(true);
	}

	void GameManager::onUpdate(Timestep delta) {
		// Update timer
	}

	void GameManager::onEvent(Event& event) {
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