#include <gl-window/mainWindow.hpp>

void title_section()
{
    // set up the main window size
    ImGui::SetWindowSize(ImVec2(1280, 720));
    // set up the main window position
    ImGui::SetWindowPos(ImVec2(0, 0));

    // centre the title and set the font size

    // ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("BiblioCrypt").x) / 2);
    // ImGui::Text("BiblioCrypt");

    // // seperator line
    // ImGui::Spacing();
    // ImGui::Separator();
    // ImGui::Separator();
    // // adding some space in between
    // ImGui::Spacing();
    spaceSection(3);
    // Book tab
    // settimg the cursor position to center the button
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 260) / 2);

    // set to same line

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 1.0f, 1.00f));
    if (ImGui::Button("Library"))
    {
        stateVars::show_library_window = true;
        stateVars::show_initial_window = false;
        stateVars::show_books_window = false;
        stateVars::show_main_window = false;
        stateVars::show_transactions_window = false;
        stateVars::show_blockchain_window = false;
    }
    ImGui::SameLine();
    // blue color for active

    if (ImGui::Button("Books"))
    {
        // change the buttons background color

        stateVars::show_books_window = true;
        stateVars::show_main_window = false;
        stateVars::show_initial_window = false;
        stateVars::show_library_window = false;
        stateVars::show_transactions_window = false;
        stateVars::show_blockchain_window = false;
    }

    // same line
    ImGui::SameLine();
    if (ImGui::Button("Transactions"))
    {
        stateVars::show_transactions_window = true;
        stateVars::show_main_window = false;
        stateVars::show_initial_window = false;
        stateVars::show_library_window = false;
        stateVars::show_blockchain_window = false;
        stateVars::show_books_window = false;
    }

    // set to same line
    ImGui::SameLine();
    if (ImGui::Button("BlockChain"))
    {
        stateVars::show_main_window = false;
        stateVars::show_blockchain_window = true;
        stateVars::show_initial_window = false;
        stateVars::show_library_window = false;
        stateVars::show_books_window = false;
        stateVars::show_transactions_window = false;
    }
    ImGui::PopStyleColor();
    ImGui::Spacing();
    ImGui::Spacing();
}

// void main_window()
// {
//     // trying to use the state variable as extern variable to see if it works

//     ImGui::Begin("Main");
//     title_section();

//     ImGui::End();
// }