#include <gl-window/errorWindow.hpp>

void error_window(std::string error_message, bool &show_error)
{
    ImGui::Begin("Error", &show_error, ImGuiWindowFlags_AlwaysAutoResize);

    // set position at top left below menu bar
    ImGui::SetWindowPos(ImVec2(0, 20));

    ImGui::Text(error_message.c_str());
    // close button
    if (ImGui::Button("Close"))
    {
        show_error = false;
        ImGui::CloseCurrentPopup();
    }
    ImGui::End();
}
