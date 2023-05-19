#include <gl-window/bookWindow.hpp>

void book_window()
{

    ImGui::Begin("Books", &stateVars::show_books_window, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    title_section();
    // title at centre of the window
    spaceSection(3);

    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Books").x) / 2);
    ImGui::Text("Books");

    // // text input
    // spaceSection(3);

    // separatorSection(2);
    spaceSection(3);

    ImGui::Columns(4, "HEADINGS");
    ImGui::Separator();
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Book Name");
    ImGui::NextColumn();
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Author");
    ImGui::NextColumn();
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "ISBN");
    ImGui::NextColumn();
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Ownership ID");
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Separator();

    for (int i = 1; i < int(globalVars::m_book_data.size()); i++)
    {
        for (int j = 0; j < int(4); j++)
        {
            ImGui::NextColumn();
            ImGui::Text("%s", (globalVars::m_book_data[i][j]).c_str());
            // ImGui::BeginTooltip();
            // ImGui::Text("%s", (globalVars::m_book_data[i][j]).c_str());
            // ImGui::EndTooltip();
        }
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Separator();
    }

    ImGui::End();
}
// how to make text bold in ImGui
// ImGui::TextColored(ImVec4(1, 1, 0, 1), "This is a text");
// ImGui::TextColored(ImVec4(1, 1, 0, 1), "This is a text");
