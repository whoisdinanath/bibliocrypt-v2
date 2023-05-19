#include <gl-window/gl_init.hpp>

// defining the state variables

inline void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}
void spaceSection(int n)
{
    for (int i = 0; i < n; i++)
    {
        ImGui::Spacing();
    }
}
void separatorSection(int n)
{
    for (int i = 0; i < n; i++)
    {
        ImGui::Separator();
    }
}

void initGLwindow()
{

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return;

        // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 + GLSL 150
    const char *glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#else
    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create window with graphics context
    GLFWwindow *window = glfwCreateWindow(1280, 720, "BiblioCrypt", NULL, NULL);
    if (window == NULL)
        return;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // gl window init
    bool err = glewInit() != GLEW_OK;
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    io.Fonts->AddFontFromFileTTF("./assets/fonts/fcb.ttf", 16.0f);
    io.Fonts->AddFontFromFileTTF("./assets/fonts/fcm.ttf", 18.0f);
    io.Fonts->AddFontFromFileTTF("./assets/fonts/fcr.ttf", 20.0f);
    io.Fonts->AddFontFromFileTTF("./assets/fonts/vmb.ttf", 22.0f);
    io.Fonts->AddFontFromFileTTF("./assets/fonts/vmr.ttf", 24.0f);
    io.Fonts->AddFontFromFileTTF("./assets/fonts/vmm.ttf", 18.0f);

    // IM_ASSERT(fonts::font_20 != NULL);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    // bool show_demo_window = true;

    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // library_func();

        // if (show_demo_window)
        //     ImGui::ShowDemoWindow(&show_demo_window);

        if (stateVars::show_error)
        {
            error_window(stateVars::error_message, stateVars::show_error);
        }

        if (stateVars::show_initial_window)
        {
            ImGui::Begin("BiblioCrypt", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
            // std::cout << "showing initial window" << std::endl;
            // set window size
            // ImGui::SetWindowSize(ImVec2(300, 100));
            // ImGui::SetWindowPos(ImVec2(500, 200));
            // full screen
            ImGui::SetWindowSize(ImVec2(1280, 720));
            ImGui::SetWindowPos(ImVec2(0, 0));
            // child window at the centre of the window
            ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x - 300) / 2, (ImGui::GetWindowSize().y - 200) / 2));
            ImGui::BeginChild("Initial", ImVec2(300, 100), true, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

            // title at centre of the window
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("BiblioCrypt").x) / 2);
            ImGui::Text("BiblioCrypt");
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Are you a initial node?").x) / 2);
            ImGui::Text("Are you a initial node?");
            spaceSection(3);
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Yes   No?").x) / 2);
            if (ImGui::Button("Yes"))
            {
                stateVars::show_initial_window = false;
                stateVars::show_register_window = true;
                stateVars::initialNode = true;
            }
            ImGui::SameLine();
            if (ImGui::Button("No"))
            {
                stateVars::show_initial_window = false;
                stateVars::show_login_window = true;
            }

            ImGui::EndChild();

            ImGui::End();
        }
        // register window
        if (stateVars::show_register_window)
        {

            stateVars::show_initial_window = false;
            ImGui::Begin("Register", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
            // full screen
            ImGui::SetWindowSize(ImVec2(1280, 720));
            ImGui::SetWindowPos(ImVec2(0, 0));

            // child window at the centre of the window
            ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x - 300) / 2, (ImGui::GetWindowSize().y - 200) / 2));

            ImGui::BeginChild("Register", ImVec2(300, 200), true, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

            // globalVars::BIBLIOCHAIN = std::make_unique<Blockchain>();
            if (ImGui::Button("Back"))
            {
                stateVars::show_register_window = false;
                stateVars::show_initial_window = true;
            }

            static char username[128];
            ImGui::Text("Welcome to BiblioCrypt!");
            spaceSection(1);
            ImGui::InputText("ID", username, IM_ARRAYSIZE(username));
            ImGui::Text("format: THA[0-9]{3}[A-Z]{3}[0-9]{3}");
            spaceSection(1);
            if (ImGui::Button("Join"))
            {
                if (User::check_if_user_exists(username))
                {
                    stateVars::show_login_window = true;
                    stateVars::show_error = true;
                    stateVars::error_message = "User already exists, Please Login!";
                    stateVars::show_register_window = false;
                }
                else
                {
                    try
                    {

                        globalVars::global_user = std::make_unique<User>(username);
                        std::cout << globalVars::global_user->ID << " User Created..." << std::endl;
                        stateVars::show_secrets_window = true;
                        stateVars::show_register_window = false;
                        std::cout << stateVars::initialNode << std::endl;
                        if (Chain::noNodes > 1)
                        {
                            globalVars::j_request = {
                                {"method", "POST"},
                                {"query", "add_user"},
                                {"user", globalVars::global_user->toJson()}};
                            TcpClient s_client = TcpClient(globalVars::OTHER_SERVER_IP, globalVars::OTHER_SERVER_PORT);
                            s_client.sendQuery(globalVars::j_request.dump());
                            globalVars::response = s_client.receiveResponse();
                            if (globalVars::response != "")
                            {
                                globalVars::j_response = json::parse(globalVars::response);
                                if (globalVars::j_response["status_code"] == "555")
                                {
                                    std::cout << "User added to the blockchain" << std::endl;
                                }
                            }
                            else
                            {
                                std::cout << "No nodes available" << std::endl;
                            }
                            s_client.closeClient();
                        }
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                        stateVars::show_error = true;
                        stateVars::error_message = e.what();
                        memset(username, 0, sizeof(username));
                        stateVars::show_register_window = true;
                    }
                }
            }

            // seperator line
            separatorSection(1);
            spaceSection(1);
            ImGui::Text("Not a initial node?");
            spaceSection(1);
            if (ImGui::Button("Login"))
            {
                stateVars::show_register_window = false;
                stateVars::show_login_window = true;
                stateVars::show_initial_window = false;
                stateVars::initialNode = false;
            }
            ImGui::EndChild();

            ImGui::End();
        }

        if (stateVars::show_secrets_window)
        {

            ImGui::Begin("Credentials", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
            // full screen
            ImGui::SetWindowSize(ImVec2(1280, 720));
            ImGui::SetWindowPos(ImVec2(0, 0));

            // child window at the centre of the window
            ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x - 500) / 2, (ImGui::GetWindowSize().y - 150) / 2));

            ImGui::BeginChild("Credentials", ImVec2(500, 150), true, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

            ImGui::Text("Welcome to BiblioCrypt!");
            ImGui::Text("Here are your credentials, please save them somewhere safe.");
            spaceSection(2);
            separatorSection(2);
            spaceSection(2);
            ImGui::Text("Private Key: %s", globalVars::global_user->private_key.c_str());
            ImGui::Text("Public Key: %s", globalVars::global_user->public_key.c_str());
            if (ImGui::Button("Continue"))
            {
                stateVars::show_secrets_window = false;
                stateVars::show_library_window = true;
            }
            ImGui::EndChild();
            ImGui::End();
        }

        if (stateVars::show_login_window)
        {
            try
            {
                if (Chain::noNodes <= 1)
                {
                    globalVars::j_request = {
                        {"method", "GET"},
                        {"query", "get_data"},
                        {"data", {"newNode", true}},
                    };
                    std::cout << "J_REQUEST: " << globalVars::j_request.dump() << std::endl;

                    TcpClient s_client = TcpClient(globalVars::OTHER_SERVER_IP, globalVars::OTHER_SERVER_PORT);
                    s_client.sendQuery(globalVars::j_request.dump());
                    globalVars::response = s_client.receiveResponse();
                    std::cout << "New Node Added" << std::endl;
                    if (globalVars::response != "")
                    {
                        std::cout << "SERVER_RESPONSE: " << globalVars::response << std::endl;
                        globalVars::j_response = json::parse(globalVars::response);
                        std::string user_data = globalVars::j_response["user"].get<std::string>();
                        std::string book_data = globalVars::j_response["book"].get<std::string>();
                        std::cout << "BOOK and USER data success." << std::endl;
                        Chain::noNodes = globalVars::j_response["noNodes"].get<int>();
                        std::cout << "No of Nodes: " << Chain::noNodes << std::endl;
                        // blockchain data is already in json string format
                        std::string blockchain_data = globalVars::j_response["chain"].get<std::string>();
                        // open the book.csv and data.csv to write the data
                        std::ofstream user_file("./assets/data.csv");
                        std::ofstream book_file("./assets/book.csv");
                        if (!user_file.is_open())
                        {
                            std::cout << "Error opening file" << std::endl;
                            exit(1);
                        }
                        if (!book_file.is_open())
                        {
                            std::cout << "Error opening file" << std::endl;
                            exit(1);
                        }
                        // write the data to the file
                        user_file << user_data;
                        book_file << book_data;
                        Chain::BIBLIOCHAIN.replaceChain(json::parse(blockchain_data));
                        // close the file
                        user_file.close();
                        book_file.close();
                        std::cout << "No Nodes: " << Chain::noNodes << std::endl;
                        std::cout << "Data Received" << std::endl;
                    }
                    else
                    {
                        throw std::runtime_error("No nodes available, so you need to initialize a node.");
                    }
                    globalVars::j_request = {
                        {"method", "GET"},
                        {"query", "get_pool"},
                    };
                    s_client.sendQuery(globalVars::j_request.dump());
                    globalVars::response = s_client.receiveResponse();
                    if (globalVars::response != "")
                    {
                        std::cout << "transaction pool received" << std::endl;
                        globalVars::j_response = json::parse(globalVars::response);
                        if (globalVars::j_response["status_code"] == "200")
                        {
                            json j_temp = globalVars::j_response["transactions"];
                            // add the trans to globalVars::m_transactionPool
                            Chain::m_transactionPool.clear();
                            for (auto it = j_temp.begin(); it != j_temp.end(); ++it)
                            {
                                std::string trans = it->dump();
                                json j2_temp = json::parse(trans);
                                Transaction transaction = Transaction(j2_temp);
                                Chain::m_transactionPool.push_back(transaction);
                            }
                        }
                        std::cout << "transaction pool added" << std::endl;
                    }
                    else
                    {
                        throw std::runtime_error("No nodes available, so you need to initialize a node.");
                    }
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                stateVars::show_error = true;
                stateVars::error_message = e.what();
                stateVars::show_login_window = false;
                stateVars::show_register_window = true;
            }

            ImGui::Begin("Login", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
            // full screen
            ImGui::SetWindowSize(ImVec2(1280, 720));
            ImGui::SetWindowPos(ImVec2(0, 0));
            // child window at the centre of the window
            ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x - 300) / 2, (ImGui::GetWindowSize().y - 200) / 2));
            ImGui::BeginChild("Login", ImVec2(300, 200), true, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

            if (ImGui::Button("Back"))
            {
                stateVars::show_login_window = false;
                stateVars::show_initial_window = true;
            }
            static char username[128];
            static char password[128];
            // strcpy(username, "THA078BRI020");
            // strcpy(password, "CpEWOQAAAAA=");
            ImGui::InputText("ID", username, IM_ARRAYSIZE(username));
            ImGui::InputText("Secret Key", password, IM_ARRAYSIZE(password));
            spaceSection(1);
            if (ImGui::Button("Login"))
            {
                if (login(username, password))
                {
                    std::cout << globalVars::global_user->ID << " logged in successfully!" << std::endl;
                    stateVars::show_login_window = false;
                    stateVars::show_library_window = true;
                }
                else
                {
                    std::cout << "Wrong username or password!" << std::endl;
                    stateVars::show_error = true;
                    stateVars::error_message = "Wrong username or password!";
                    // clear input fields
                    memset(username, 0, sizeof(username));
                    memset(password, 0, sizeof(password));
                    stateVars::show_login_window = true;
                }
            }
            // if (stateVars::show_error)
            // {
            //     error_window(stateVars::error_message, stateVars::show_error);
            // }
            spaceSection(1);
            separatorSection(1);
            ImGui::Text("Are you a new user?");
            spaceSection(1);
            if (ImGui::Button("Register"))
            {
                stateVars::show_login_window = false;
                stateVars::show_register_window = true;
            }
            ImGui::EndChild();

            ImGui::End();
        }

        // if (stateVars::show_main_window)
        // {
        //     main_window();
        // }
        if (stateVars::show_books_window)
        {
            book_window();
        }
        if (stateVars::show_library_window)
        {
            library_window();
        }
        if (stateVars::show_transactions_window)
        {
            transaction_window();
        }
        if (stateVars::show_blockchain_window)
        {
            blockchain_window();
        }

        // Rendering
        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    // ImGui::DestroyContext();
    globalVars::exit_flag = true;
    glfwDestroyWindow(window);
    glfwTerminate();
}
