#include <gl-window/libraryWindow.hpp>

void library_window()
{
    // library windows with close button at the top
    ImGui::Begin("Library", &stateVars::show_library_window, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    // menu bar

    title_section();
    // title at centre of the window
    spaceSection(3);

    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Library").x) / 2);
    ImGui::Text("Library");

    // text input
    spaceSection(3);

    // separatorSection(2);
    // spaceSection(3);
    ImGuiStyle &style = ImGui::GetStyle();
    const float label_width = ImGui::CalcTextSize("QUERY").x + style.ItemInnerSpacing.x;

    ImGui::PushItemWidth(ImGui::GetWindowWidth() / 2 - label_width);
    ImGui::AlignTextToFramePadding(); // Align text label to the left
    // center the text input
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() / 2) / 2);
    ImGui::Text("QUERY: ");
    ImGui::SameLine();
    static char buf[1024] = "";
    ImGui::InputText("##", buf, IM_ARRAYSIZE(buf));

    ImGui::PopItemWidth();
    spaceSection(3);
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Submit").x) / 2);
    if (ImGui::Button("Submit"))
    {
        // std::cout << "BUF: " << buf << std::endl;
        strcpy(globalVars::QUERY, buf);
        std::cout << "QUERY: " << globalVars::QUERY << std::endl;
        memset(buf, 0, sizeof(buf));
        // std::cout << "BUF: " << buf << std::endl;
    }
    spaceSection(3);

    // 4 vertical rectangular boxes of size 1/4 of the window in same line
    // each box will have a button and a text
    std::vector<std::string> box_title = {
        "Instructions",
        "Donate Book",
        "Borrow Book",
        "Return Book",
    };
    std::vector<std::string> box_text = {
        "\n 1. To view all books, click on the 'Books' tab in the title bar.\n\n 2. To see the list of transactions, click on the 'Transactions' tab in the title bar. \n\n 3. To view blockchain information, click on the 'Blockchain' tab in the title bar. \n\n 4. You should have enough tokens to perform any of the query operations. \n\n Tokens Required and Gain: \n\t a. GET Book (Borrow) : 1 token loss \n\t b. GIVE Book (Return) : 1 token loss \n\t c. DONATE Book : 1 token gain \n\n The OWNERSHIP ID of library is '00000000' which is the id to which all books in library will be owned. Ownership ID of the users whill be sha256 hash of the user's public key. \n\n Note: All the transactions are stored in the blockchain.",
        "To donate a book, follow these steps:\n\n1. Insert your query into the query box provided.\n\n2. Click on the submit button to submit your query.\n\n3. Use the following format for your query: DONATE|<book-isbn>|<book-name>|<author-name>.\n\n4. For example, your query should look like this: DONATE|123456789|The Alchemist|Paulo Coelho.\n\n5. By donating a book, you will earn 1 token.\n\n6. The ownership of the book will be transferred to the library's default OWNERSHIP_ID.\n\n7. Please note that the book will be added to the library only if it is not already present in the library.\n\nBy following these instructions, you can easily donate a book to the library.",
        "To borrow a book, please follow these steps:\n\n1. Insert your query into the query box provided.\n\n2. Click on the submit button to submit your query.\n\n3. Use the following format for your query: GET|<book-isbn>.\n\n4. For example, your query should look like this: GET|123456789.\n\n5. When you borrow a book, you will have 1 token deducted from your account.\n\n6. The ownership of the book will be transferred from the library to you as the user.\n\n7. It is important to note that you can borrow a book only if it is present in the library and is not already borrowed by someone else.\n\nBy following these guidelines, you can successfully borrow a book from the library.",
        "To return a book, please follow these steps:\n\n1. Insert your query into the query box provided.\n2. Click on the submit button to submit your query.\n\n3. Use the following format for your query: GIVE|<book-isbn>.\n\n4. For example, your query should look like this: GIVE|123456789.\n\n5. After returning the book, you will earn 1 token.\n\n6. The ownership of the book will be transferred from you as the user to the library.\n\n7. It is important to note that you can return a book only if it is present in the library and is currently borrowed by you.\n\nBy following these guidelines, you can successfully return a book to the library.",
    };

    // box 1
    for (int i = 0; i < 4; i++)
    {
        ImGui::BeginChild(i + 1, ImVec2(ImGui::GetWindowWidth() / 4 - 10, ImGui::GetWindowHeight() / 1.45f), true);
        // title at centre
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(box_title[i].c_str()).x) / 2);
        ImGui::Text("%s", box_title[i].c_str());
        spaceSection(1);
        separatorSection(1);
        spaceSection(1);
        // wrap text size to 1/4 of the window
        ImGui::TextWrapped("%s", box_text[i].c_str());

        // ImGui::Text("%s", box_text[i].c_str());

        ImGui::EndChild();

        ImGui::SameLine();
    }

    ImGui::End();
}
