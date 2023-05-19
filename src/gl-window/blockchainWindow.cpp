#include <gl-window/blockchainWindow.hpp>

void blockchain_window()
{
    ImGui::Begin("Blockchain", &stateVars::show_blockchain_window /*, ImGuiWindowFlags_NoResize*/);
    title_section();

    spaceSection(3);

    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("BlockChain").x) / 2);
    // // ImGui::PushFont(fonts::font_20);
    ImGui::Text("BlockChain");
    // // ImGui::PopFont();

    // // text input
    spaceSection(3);
    // separatorSection(2);
    // spaceSection(3);
    // 4 vertical rectangular boxes of size 1/4 of the window in same line

    ImGui::BeginChild("Chains", ImVec2(0, ImGui::GetWindowHeight() / 1.5f), true, ImGuiWindowFlags_HorizontalScrollbar);

    for (int i = int(Chain::BIBLIOCHAIN.getLength()); i > 0; i--)
    {
        ImGui::BeginChild(getName("Block", i - 1).c_str(), ImVec2(ImGui::GetWindowWidth() / 4 - 10, ImGui::GetWindowHeight() - 18), true, ImGuiWindowFlags_None);
        // title at centre
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Block x").x) / 2);
        ImGui::Text(getName("Block", i).c_str());
        separatorSection(1);
        // globalVars::BIBLIOCHAIN.getBlock(0).toString();
        Block block = Chain::BIBLIOCHAIN.getBlock(i - 1);

        ImGui::TextWrapped("Prev. Hash: ");
        ImGui::TextWrapped(block.getPreviousHash().c_str());
        spaceSection(1);
        ImGui::TextWrapped("Merkle Hash: ");
        ImGui::TextWrapped(block.getMerkleHash().c_str());
        spaceSection(1);
        ImGui::TextWrapped("Time Stamp: ");
        ImGui::TextWrapped(block.getTimestamp().c_str());
        spaceSection(3);
        separatorSection(2);
        spaceSection(3);
        ImGui::TextWrapped("Block Hash: ");
        ImGui::TextWrapped(block.getHash().c_str());
        spaceSection(1);
        ImGui::TextWrapped("Miner Address: ");
        ImGui::TextWrapped(block.getMinerAddress().c_str());
        spaceSection(1);
        ImGui::TextWrapped("Transactions: ");
        for (int j = 0; j < int(block.getTransaction().size()); j++)
        {
            ImGui::Text(block.getTransaction()[j].representation().c_str());
            spaceSection(1);
        }

        ImGui::EndChild();

        ImGui::SameLine();
    }

    ImGui::EndChild();
    spaceSection(3);
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Users").x) / 2);
    ImGui::Text("Users");
    spaceSection(3);
    // begin child whose size is adjusted according to the content inside it
    ImGui::BeginChild("Users");
    ImGui::SetWindowSize(ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() / 1.5f));

    ImGui::Columns(2, "HEADINGS");
    ImGui::Separator();
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "USER ADDRESS");
    ImGui::NextColumn();
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "OWNERSHIP ADDRESS");
    separatorSection(2);
    spaceSection(3);

    for (int i = 1; i < int(globalVars::m_user_data.size()); i++)
    {
        ImGui::NextColumn();
        ImGui::Text("%s", (globalVars::m_user_data[i][2]).c_str());
        ImGui::NextColumn();
        ImGui::Text("%s", (globalVars::m_user_data[i][4]).c_str());

        separatorSection(2);
        spaceSection(1);
    }
    ImGui::EndChild();

    ImGui::End();
}

// calculate imgui text size of 64 characters
