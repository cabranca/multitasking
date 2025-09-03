#include <Cabrankengine.h>

#include <array>

#include <Cabrankengine/Core/EntryPoint.h>

#include "BalloonMinigame.h"
#include "CounterMinigame.h"
#include "GameManager.h"

namespace multitasking {

	class MultitaskingApplication : public cabrankengine::Application {
		public:
			MultitaskingApplication() {
				m_minigames[0] = new CounterMinigame();
				pushLayer(m_minigames[0]);
				m_minigames[1] = new BalloonMinigame();
				pushLayer(m_minigames[1]);
				pushLayer(new GameManager(m_minigames));
			}

		private:
			std::array<Minigame*, 2> m_minigames;
	};
}

cabrankengine::Application* cabrankengine::createApplication() {
	return new multitasking::MultitaskingApplication();
}
