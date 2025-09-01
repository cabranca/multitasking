#pragma once

#include <functional>

#include <Cabrankengine/Core/Layer.h>

namespace multitasking {

	class Minigame : public cabrankengine::Layer {
		public:
			using Callback = std::function<void()>;

			void setWinCallback(Callback callback) { m_WinCallback = std::move(callback); }
			void setActive(bool active) { m_Active = active; }

		protected:
			Callback m_WinCallback; // this method must be called when the goal is reached.
			bool m_Active = false;
	};
}
