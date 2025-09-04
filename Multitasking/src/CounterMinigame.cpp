#include "CounterMinigame.h"

#include <imgui.h>

#include <Cabrankengine/Core/Application.h>
#include <Cabrankengine/Core/Window.h>
#include <Cabrankengine/Renderer/RenderCommand.h>

using namespace cabrankengine;

namespace multitasking {

    void CounterMinigame::onUpdate(cabrankengine::Timestep delta) {
        if (!m_Active)
            return;

        RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
        RenderCommand::clear();
    }

    void CounterMinigame::onImGuiRender() {
        if (!m_Active)
            return;

        printCounter();
        drawButton();
        renderSettings();
	}

    void CounterMinigame::printCounter() const {
        auto windowWidth = Application::get().getWindow().getWidth();
        std::string counterStr = std::string("Counter: ") + std::to_string(m_Counter);

        ImVec2 pos = ImGui::GetWindowPos();
        ImGui::GetForegroundDrawList()->AddText(ImVec2(pos.x + windowWidth / 2, pos.y + 10.f), IM_COL32_WHITE, counterStr.c_str());
    }

    void CounterMinigame::drawButton() {
        auto windowWidth = Application::get().getWindow().getWidth();
        ImVec2 pos = ImGui::GetWindowPos();
        ImGui::SetNextWindowPos(ImVec2(pos.x + windowWidth / 2, pos.y + 50.f), ImGuiCond_Always, ImVec2(0.5f, 0.5f)); // pos absoluta
        ImGui::SetNextWindowBgAlpha(0.0f); // fondo transparente

        ImGuiWindowFlags flags =
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_AlwaysAutoResize;

        ImGui::Begin("CounterButtonWindow", nullptr, flags);

        ImGui::BeginDisabled(m_Counter == m_Goal);
        if (ImGui::Button("QUIERO MÁS")) {
            m_Counter++;
            if (m_Counter == m_Goal && m_WinLoseCallback)
                m_WinLoseCallback(true);
        }
        ImGui::EndDisabled();

        ImGui::End();
    }

#ifdef CE_DEBUG
    void CounterMinigame::renderSettings() {
        ImGui::Begin("Settings");

        ImGui::InputInt("Counter", &m_Counter);
        ImGui::InputInt("Goal", &m_Goal);

        ImGui::End();
    }
#else
    void CounterMinigame::renderSettings() {}
#endif
}
