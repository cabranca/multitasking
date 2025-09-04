#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <Cabrankengine/Core/Timestep.h>
#include <Cabrankengine/Renderer/Texture.h>

#include "Minigame.h"

namespace multitasking {

	class PopcornMinigame : public Minigame {
	public:
		PopcornMinigame();

		virtual void onUpdate(cabrankengine::Timestep delta) override;
		virtual void onImGuiRender() override;

	private:
		void updatePopcorn(cabrankengine::Timestep delta);
		bool checkMouseCollision();
		void spawnPopcorn(cabrankengine::Timestep delta);
		void render();

        struct PopcornMachine {
            glm::vec2 Position;
			float Rotation = 0.f;
            float CollisionRadius = 0.4f;
            glm::vec2 TextureSize = glm::vec2(0.4f);
        };

		struct Popcorn {
			glm::vec2 Position;
			float Rotation;
			glm::vec2 Velocity ;
            float CollisionRadius = 0.1f;
			glm::vec2 TextureSize = glm::vec2(0.1f);
		};

		cabrankengine::Ref<cabrankengine::Texture2D> popcornTexture;
		cabrankengine::Ref<cabrankengine::Texture2D> popcornMachineTexture;

        PopcornMachine m_PopcornMachine;
        std::vector<Popcorn> m_Popcorn;

	    float GRAVITY = -9.8f;
	};
}
