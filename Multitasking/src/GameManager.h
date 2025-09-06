#pragma once

#include <array>

#include <Cabrankengine/Core/Layer.h>
#include <Cabrankengine/Events/KeyEvent.h>
#include <Cabrankengine/Renderer/OrthographicCameraController.h>

#include "Minigame.h"


namespace multitasking {

	class GameManager : public cabrankengine::Layer {
		public:
			GameManager(std::array<Minigame*, 3> minigames);

			virtual void onUpdate(cabrankengine::Timestep delta) override;
			virtual void onImGuiRender() override;
			virtual void onEvent(cabrankengine::Event& event) override;

			cabrankengine::OrthographicCamera& getCamera() { return m_Camera->getCamera(); }

		private:
			bool changeTab(cabrankengine::KeyPressedEvent& event);

			std::array<Minigame*, 3> m_minigames;
			int m_CurrentTabIndex;

			cabrankengine::Ref<cabrankengine::OrthographicCameraController> m_Camera;

			float m_FontScale = 10.f;
			std::string m_FinalMessage = "";
	};
}
