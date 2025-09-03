#pragma once

#include <array>

#include <Cabrankengine/Core/Layer.h>
#include <Cabrankengine/Events/KeyEvent.h>

#include "CounterMinigame.h"


namespace multitasking {

	class GameManager : public cabrankengine::Layer {
		public:
			GameManager(std::array<Minigame*, 2> minigames);

			virtual void onUpdate(cabrankengine::Timestep delta) override;
			virtual void onEvent(cabrankengine::Event& event) override;

		private:
			bool changeTab(cabrankengine::KeyPressedEvent& event);

			std::array<Minigame*, 2> m_minigames;
			int m_CurrentTabIndex;
	};
}
