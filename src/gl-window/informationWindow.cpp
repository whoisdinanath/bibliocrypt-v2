#include <gl-window/informationWindow.hpp>

void book_window()
{

    ImGui::Begin("Informations", &stateVars::show_information_window, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    title_section();
    // title at centre of the window
    spaceSection(3);
    ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize("Books  Users").x / 2);
    // set button color to sky blue
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.55f, 0.6f, 0.6f));
    if (ImGui::SmallButton("Books"))
    {
        stateVars::show_book_tab = true;
        stateVars::show_user_tab = false;
    }
    ImGui::SameLine();
    if (ImGui::SmallButton("Users"))
    {
        stateVars::show_book_tab = false;
        stateVars::show_user_tab = true;
    }
    ImGui::PopStyleColor();

    if (stateVars::show_user_tab)
    {

        spaceSection(3);
        ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize("Users").x / 2);
        ImGui::Text("Users");
        spaceSection(3);
        separatorSection(2);

        ImGui::Columns(2, "HEADINGS");
        ImGui::Separator();
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "USER ADDRESS");
        ImGui::NextColumn();
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "OWNERSHIP ADDRESS");
        separatorSection(2);
        spaceSection(1);

        for (int i = 1; i < int(globalVars::m_user_data.size()); i++)
        {
            ImGui::NextColumn();
            ImGui::Text("%s", (globalVars::m_user_data[i][2]).c_str());
            ImGui::NextColumn();
            ImGui::Text("%s", (globalVars::m_user_data[i][4]).c_str());

            separatorSection(2);
            spaceSection(1);
        }
    }
    if (stateVars::show_book_tab)
    {

        spaceSection(3);
        ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize("Books").x / 2);
        ImGui::Text("Books");
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
    }

    // end the columns
    // ImGui::SetColumnOffset(0, 0);

    ImGui::End();
}
