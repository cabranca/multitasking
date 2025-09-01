#pragma once

#include <Cabrankengine/Events/Event.h>

#include "Minigame.h"


namespace multitasking {

	// This minigame constists in click a button to increase the counter until it reaches the goal
	class CounterMinigame : public Minigame {
		public:
			virtual void onUpdate(cabrankengine::Timestep delta) override;
			virtual void onImGuiRender() override;

		private:
			void printCounter() const;
			void drawButton();
			void renderSettings();

			int m_Counter = 0; // Current state of the counter
			int m_Goal = 100; // Goal to reach incrementing the counter
	};
}
