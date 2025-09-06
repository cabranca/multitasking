#include "CounterMinigame.h"

#include <imgui.h>

#include <Cabrankengine/Core/AudioEngine.h>
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

        if (m_FinishedGame)
            return;

        printCounter();
        drawButton();
        renderSettings();
	}

    void CounterMinigame::printCounter() const {
        auto& window = Application::get().getWindow();
        float windowWidth = (float)window.getWidth();
        float windowHeight = (float)window.getHeight();

        std::string counterStr = "Counter: " + std::to_string(m_Counter);

        // calcular tamaño del texto con la fuente actual
        ImFont* font = ImGui::GetFont();
        ImVec2 textSize = font->CalcTextSizeA(font->LegacySize * m_FontScale, FLT_MAX, 0.0f, counterStr.c_str());

        // centrar en pantalla
        ImVec2 pos(
            (windowWidth - textSize.x) * 0.5f,
            (windowHeight - textSize.y) * 0.5f
        );

        // dibujar texto
        ImGui::GetForegroundDrawList()->AddText(
            font,
            font->LegacySize * m_FontScale,
            pos,
            IM_COL32_WHITE,
            counterStr.c_str()
        );
    }

    void CounterMinigame::drawButton() {
        auto& window = Application::get().getWindow();
        float windowWidth = (float)window.getWidth();
        float windowHeight = (float)window.getHeight();

        // Escala del botón (ej: 2x más grande)
        float scale = 2.0f;
        ImVec2 buttonSize(120.0f * scale, 40.0f * scale); // tamaño base * escala

        // Centrar el botón en pantalla
        ImVec2 pos(
            (windowWidth - buttonSize.x) * 0.5f,
            (windowHeight - buttonSize.y) * 0.5f + 100.0f // desplazamiento vertical extra si querés
        );

        ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
        ImGui::SetNextWindowBgAlpha(0.0f); // fondo transparente

        ImGuiWindowFlags flags =
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_AlwaysAutoResize;

        ImGui::Begin("CounterButtonWindow", nullptr, flags);

        // Escalar fuente dentro de esta ventana
        ImGui::SetWindowFontScale(scale);

        ImGui::BeginDisabled(m_Counter == m_Goal);
        if (ImGui::Button("QUIERO MÁS", buttonSize)) {
            AudioEngine::playAudio("assets/sounds/click.wav", false);
            m_Counter++;
            if (m_Counter == m_Goal && m_WinLoseCallback) {
                m_WinLoseCallback(true);
                
            }
        }
        ImGui::EndDisabled();

        ImGui::End();
    }

#ifdef CE_DEBUG
    void CounterMinigame::renderSettings() {
        ImGui::Begin("Settings");

        ImGui::InputInt("Counter", &m_Counter);
        ImGui::InputInt("Goal", &m_Goal);
        ImGui::InputFloat("Font Scale", &m_FontScale);

        ImGui::End();
    }
#else
    void CounterMinigame::renderSettings() {}
#endif
}
