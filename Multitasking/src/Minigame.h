#pragma once

#include <functional>

#include <Cabrankengine/Core/Layer.h>
#include <Cabrankengine/Renderer/OrthographicCameraController.h>

namespace multitasking {

	class Minigame : public cabrankengine::Layer {
		public:
			using Callback = std::function<void(bool)>;

			void setWinLoseCallback(Callback callback) { m_WinLoseCallback = std::move(callback); }
			void setActive(bool active) { m_Active = active; }
			void finishGame() { m_FinishedGame = true; }
			void setCamera(const cabrankengine::Ref<cabrankengine::OrthographicCameraController>& camera) { m_Camera = camera; }

		protected:
			Callback m_WinLoseCallback; // this method must be called when the goal is reached.
			bool m_Active = false;
			bool m_FinishedGame = false;
			
			cabrankengine::Ref<cabrankengine::OrthographicCameraController> m_Camera;
	};
}
