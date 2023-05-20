#include <gl-window/transactionWindow.hpp>

void transaction_window()
{
    ImGui::Begin("Transactions", &stateVars::show_transactions_window, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    title_section();
    // title at centre of the window
    spaceSection(3);

    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Transactions").x) / 2);
    ImGui::Text("Transactions");

    // text input
    spaceSection(3);

    separatorSection(2);
    spaceSection(3);

    ImGui::Columns(5, "HEADINGS");
    ImGui::Separator();
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Transaction Representation");
    ImGui::NextColumn();
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Book_Hash");
    ImGui::NextColumn();
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Data_Hash");
    ImGui::NextColumn();
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "From");
    ImGui::NextColumn();
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "To");
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Separator();

    // create a transaction vector and add all the transaction from blockchain not only the global pool to it
    std::vector<Transaction> transactionVector;
    for (auto i : Chain::m_transactionPool)
    {
        transactionVector.push_back(i);
    }
    for (int i = Chain::BIBLIOCHAIN.getLength() - 1; i > 0; i--)
    {
        for (auto j : Chain::BIBLIOCHAIN.getBlock(i).getTransaction())
        {
            transactionVector.push_back(j);
        }
    }

    for (auto i : transactionVector)
    {
        std::vector<std::string> query = i.getqueryfromenc();
        ImGui::NextColumn();
        ImGui::Text("%s", (i.representation()).c_str());
        if (ImGui::IsItemHovered())
        {

            ImGui::BeginTooltip();
            if (query[0] == "GET" || query[0] == "GIVE" || query[0] == "DONATE")
            {
                ImGui::Text("%s", (
                                      "Transaction ID: " + i.representation() + "\n" +
                                      "Book Hash: " + i.getUpdatedBookHash() + "\n" +
                                      "Data Hash: " + i.getUpdatedCertHash() + "\n" +
                                      "Type: " + "LIBRARY" + "\n" +
                                      "Sender: " + query[4] + "\n" +
                                      "Query: " + query[0] + "\n" +
                                      "Book ISBN: " + query[1] + "\n" +
                                      //   "Ownership ID: " + query[4] + "\n" +
                                      "Timestamp: " + *(query.end() - 2) + "\n")
                                      .c_str());
            }
            else
            {
                ImGui::Text("%s", (
                                      "Transaction ID: " + i.representation() + "\n" +
                                      "Book Hash: " + i.getUpdatedBookHash() + "\n" +
                                      "Data Hash: " + i.getUpdatedCertHash() + "\n" +
                                      "Type: " + "USER CREATE" + "\n" +
                                      "User ID: " + query[0] + "\n" +
                                      "Public Key: " + query[2] + "\n" +
                                      "Ownership ID: " + query[4] + "\n")
                                      .c_str());
            }
            ImGui::EndTooltip();
        }
        ImGui::NextColumn();
        ImGui::Text("%s", (i.getUpdatedBookHash()).c_str());
        ImGui::NextColumn();
        ImGui::Text("%s", (i.getUpdatedCertHash()).c_str());

        if (query[0] == "GET")
        {
            ImGui::NextColumn();
            ImGui::Text("%s", "00000000");
            ImGui::NextColumn();
            ImGui::Text("%s", (query[4].c_str()));
        }
        else if (query[0] == "GIVE")
        {
            ImGui::NextColumn();
            ImGui::Text("%s", (query[4]).c_str());
            ImGui::NextColumn();
            ImGui::Text("%s", "00000000");
        }
        else if (query[0] == "DONATE")
        {
            ImGui::NextColumn();
            ImGui::Text("%s", (query[4]).c_str());
            ImGui::NextColumn();
            ImGui::Text("%s", "00000000");
        }
        else
        {
            ImGui::NextColumn();
            ImGui::Text("%s", (query[2]).c_str());
            ImGui::NextColumn();
            ImGui::Text("%s", (query[2]).c_str());
        }
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Separator();
    }

    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Transactions").x) / 2);
    ImGui::Text("Transactions");
    ImGui::Spacing();
    ImGui::End();
}