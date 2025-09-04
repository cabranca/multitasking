#pragma once

#include <functional>

#include <Cabrankengine/Core/Layer.h>
#include <Cabrankengine/Renderer/OrthographicCameraController.h>

namespace multitasking {
	class GameManager;

	class Minigame : public cabrankengine::Layer {
		public:
			using Callback = std::function<void()>;

			void setWinCallback(Callback callback) { m_WinCallback = std::move(callback); }
			void setActive(bool active) { m_Active = active; }
			void setCamera(const cabrankengine::Ref<cabrankengine::OrthographicCameraController>& camera) { m_Camera = camera; }

		protected:
			Callback m_WinCallback; // this method must be called when the goal is reached.
			bool m_Active = false;
			
			cabrankengine::Ref<cabrankengine::OrthographicCameraController> m_Camera;
	};
}
