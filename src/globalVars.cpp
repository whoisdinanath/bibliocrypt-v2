#include <globalVars.hpp>

namespace globalVars
{
    std::string MY_SERVER_IP = "0.0.0.0";
    int MY_SERVER_PORT = 8080;
    std::unique_ptr<TcpServer> m_server = std::make_unique<TcpServer>(
        MY_SERVER_IP, MY_SERVER_PORT);
    std::string OTHER_SERVER_IP = "0.0.0.0";
    int OTHER_SERVER_PORT = 8000;
    std::unique_ptr<User> global_user = std::make_unique<User>();
    // TcpClient client;
    std::vector<std::vector<std::string>> m_user_data = read_user_data("./assets/data.csv");
    std::vector<std::vector<std::string>> m_book_data = read_book_data("./assets/book.csv");
    char QUERY[1024] = "";
    std::string response = "";
    json j_response = json::object();
    json j_request = json::object();
    bool exit_flag = false;
} // namespace globalVars

namespace Chain
{
    Blockchain BIBLIOCHAIN(0);
    std::vector<Transaction> m_transactionPool;
    int noNodes = 1;

}

void server()
{
    while (1)
    {
        if (globalVars::exit_flag)
        {
            exit(0);
        }
        globalVars::m_server->startListen();
    }
}