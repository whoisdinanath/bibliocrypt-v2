#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <errno.h>
#include <fstream>
#include <networking/Server.hpp>

using json = nlohmann::json;
const int BUFFER_SIZE = 4096;
// void log(const std::string &message)
// {
//     std::cout << message << std::endl;
// }

// void exitWithError(const std::string &errorMessage)
// {

//     std::cout << "Error: ";
//     log(errorMessage);
//     exit(1);
// }

TcpServer::TcpServer(std::string ip_address, int port) : m_ip_address(ip_address), m_port(port), m_socket(), m_new_socket(), m_incomingMessage(), m_socketAddress(), m_socketAddress_len(sizeof(m_socketAddress)), m_clientSocketAddress_len(sizeof(m_clientSocketAddress))
{
    m_socketAddress.sin_family = AF_INET;
    m_socketAddress.sin_port = htons(m_port);
    m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.std::string::c_str());
    if (startServer() != 0)
    {
        std::ostringstream ss;
        ss << "Failed to start server with PORT: " << ntohs(m_socketAddress.sin_port);
        exitWithError(ss.str());
    }
}
TcpServer::~TcpServer()
{
    closeServer();
}

int TcpServer::startServer()
{
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0)
    {
        exitWithError("cannot create server...\n");
        // std::cout << strerror(errno) << "cannot create server..." << std::endl;
        return 1;
    }
    int reuse = 1;
    if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
    {
        std::cerr << "Error setting socket option" << std::endl;
        return 1;
    }
    if (bind(m_socket, (sockaddr *)&m_socketAddress, m_socketAddress_len) < 0)
    {
        exitWithError("cannot connet socket to address...\n");
        // std::cout << strerror(errno) << "cannot connet socket to address...\n"
        //           << std::endl;
        return 1;
    }
    return 0;
}

void TcpServer::closeServer()
{
    close(m_socket);
    close(m_new_socket);
    exit(0);
}

void TcpServer::startListen()
{
    if (listen(m_socket, 20) < 0)
    {
        exitWithError("socket listen failed");
        // std::cout << strerror(errno) << "socket listen failed" << std::endl;
    }

    // std::ostringstream ss;
    // ss << "\n*** Listening on ADDRESS: "
    //    << inet_ntoa(m_socketAddress.sin_addr)
    //    << " PORT: " << ntohs(m_socketAddress.sin_port)
    //    << " ***\n\n";
    // log(ss.str());

    int bytesRecieved;
    while (true)
    {
        // log("====== Waiting for a new connection ======\n\n\n");
        acceptConnection(m_new_socket);

        char buffer[BUFFER_SIZE] = {0};

        bytesRecieved = read(m_new_socket, buffer, BUFFER_SIZE);
        if (bytesRecieved < 0)
        {
            exitWithError("Failed to read bytes from client socket connection");
            // std::cout << strerror(errno) << "Failed to read bytes from client socket connection" << std::endl;
        }
        // std::cout << "Bytes recieved: " << buffer << std::endl;
        std::ostringstream ss;
        buildResponse(buffer);
        sendResponse();
        close(m_new_socket);
    }
}

void TcpServer::acceptConnection(int &new_socket)
{
    new_socket = accept(m_socket, (sockaddr *)&m_clientSocketAddress, &m_clientSocketAddress_len);
    // std::cout << inet_ntoa(m_clientSocketAddress.sin_addr) << std::endl;
    if (new_socket < 0)
    {
        std::ostringstream ss;
        ss << "Server failed to accept incoming connection from ADDRESS: "
           << inet_ntoa(m_clientSocketAddress.sin_addr) << "; PORT: "
           << ntohs(m_clientSocketAddress.sin_port);
        log(ss.str());
        // std::cout << strerror(errno) << ss.str() << std::endl;
    }
}

void TcpServer::buildResponse(std::string request)
{
    // switch tasks according to request
    std::string response = "";
    std::stringstream ss_response;
    json request_json, response_json;
    // let's open the data files so we can read and write to them
    std::fstream book_file;
    std::fstream user_file;
    book_file.open("assets/book.csv", std::ios::in | std::ios::out);
    user_file.open("assets/data.csv", std::ios::in | std::ios::out);
    // request is in json format
    std::cout << request << std::endl;
    std::cout << "request recieved" << std::endl;
    request_json = json::parse(request);
    std::cout << "request parsed" << std::endl;
    if (request_json["method"].get<std::string>() == "GET")
    {
        std::cout << "request method is GET" << std::endl;
        std::cout << "request query is " << request_json["query"].get<std::string>() << std::endl;
        if (request_json["query"].get<std::string>() == "get_data")
        {
            std::cout << "request query is get_data" << std::endl;
            response_json["status_code"] = "200";
            std::cout << "status code set" << std::endl;
            ss_response << user_file.rdbuf();
            response_json["user"] = ss_response.str();
            ss_response.str("");
            ss_response << book_file.rdbuf();
            response_json["book"] = ss_response.str();
            ss_response.str("");
            response_json["chain"] = Chain::BIBLIOCHAIN.toJsonStr();

            // std::cout << "response is " << response << std::endl;
            std::cout << request_json["data"][1] << std::endl;
            // std::cout << request_json["data"][2] << std::endl;
            bool is_new_node = bool(request_json["data"][1]);

            if (is_new_node)
            {
                std::cout << "new node" << std::endl;
                Chain::noNodes++;
                response_json["noNodes"] = Chain::noNodes;
                std::cout << Chain::noNodes << std::endl;
            }
            response = response_json.dump();
        }

        else if (request_json["query"].get<std::string>() == "get_pool")
        {
            std::cout << "request query is get_pool" << std::endl;
            if (!Chain::m_transactionPool.empty())
            {
                std::cout << "pool is not empty" << std::endl;
                json j_temp = json::array();
                for (auto i : Chain::m_transactionPool)
                {
                    std::cout << i.toJson() << std::endl;
                    j_temp.push_back(i.toJson());
                }
                response_json["status_code"] = "200";
                response_json["transactions"] = j_temp;
                response = response_json.dump();
            }
            else
            {
                std::cout << "pool is empty" << std::endl;
                response_json["status_code"] = "101";
                response_json["message"] = "No transactions in pool";
                std::cout << "response is " << response << std::endl;
                response = response_json.dump();
            }
        }

        else if (request_json["query"].get<std::string>() == "get_chain")
        {
            std::cout << "request query is get_chain" << std::endl;
            response_json["status_code"] = "200";
            response_json["chain"] = Chain::BIBLIOCHAIN.toJsonStr();
            std::cout << "chain is " << Chain::BIBLIOCHAIN.toJsonStr() << std::endl;
            response = response_json.dump();
        }
    }
    else if (request_json["method"].get<std::string>() == "POST")
    {
        if (request_json["query"].get<std::string>() == "add_block")
        {
            Block block = Block(request_json["block"]);
            Chain::BIBLIOCHAIN.addBlock(block);
            Chain::m_transactionPool.clear();
            response_json["status_code"] = "200";
            response_json["message"] = "Block added successfully";
            response = response_json.dump();
            // Chain::m_user_data = read_user_data("./assets/data.csv");
            // Chain::m_book_data = read_book_data("./assets/book.csv");
        }
        else if (request_json["query"].get<std::string>() == "add_transaction")
        {
            std::cout << "Query Recieved" << std::endl;
            Transaction transaction = Transaction(request_json["transaction"]);
            Chain::m_transactionPool.push_back(transaction);
            std::vector<int> encodedQuery = transaction.getEncodedQuery();
            std::vector<std::string> decrypted = SmartContract::getqueryfromenc(encodedQuery);
            SmartContract::update_files(decrypted);
            response_json["status_code"] = "777";
            response_json["message"] = "Transaction added to pool";
            response = response_json.dump();
            // Chain::m_user_data = read_user_data("./assets/data.csv");
            // Chain::m_book_data = read_book_data("./assets/book.csv");
        }
        else if (request_json["query"].get<std::string>() == "add_user")
        {
            ofstream user_file("./assets/data.csv", ios::app);
            if (!user_file.is_open())
            {
                // log("Error opening file");
                // std::cout << strerror(errno) << "Error opening file" << std::endl;
            }
            else
            {

                json user = request_json["user"];
                std::cout << user["ID"].get<std::string>() << "," << user["private_key"].get<std::string>() << "," << user["public_key"].get<std::string>() << "," << user["token"].get<int>() << "," << user["ownership_id"].get<std::string>() << std::endl;
                user_file << user["ID"].get<std::string>() << "," << user["private_key"].get<std::string>() << "," << user["public_key"].get<std::string>() << "," << user["token"].get<int>() << "," << user["ownership_id"].get<std::string>() << std::endl;

                response_json["status_code"] = "555";
                response_json["message"] = "User added successfully";
                response = response_json.dump();
                // Chain::m_user_data = read_user_data("./assets/data.csv");
                // Chain::m_book_data = read_book_data("./assets/book.csv");
            }
            user_file.close();
        }
    }
    std::cout << "response is " << response << std::endl;
    m_serverMessage = response;
    std::cout << "response set" << std::endl;
    book_file.close();
    user_file.close();
}

void TcpServer::sendResponse()
{
    long bytesSent;

    bytesSent = write(m_new_socket, m_serverMessage.std::string::c_str(), m_serverMessage.size());

    if (bytesSent == int(m_serverMessage.size()))
    {
        // log("------ Server Response sent to client ------\n\n");
    }
    else
    {
        // log("Error sending response to client");
    }
}

// create a json object for a book transaction in blockchain library

// open a file in read mode

// if (request.substr(0, 4) == "NODE")
// {

//     json myChain = json::parse(request.substr(4));
//     m_myChain.replaceChain(myChain);
//     response = "OK";
//     std::cout << "Updated the chain in server!" << std::endl;
// }
// else if (request == "GET LATESTCHAIN")
// {
//     // send the info to other nodes
//     response = m_myChain.toJsonStr();
// }
// else if (request == "GET DATABASE")
// {
//     ifstream data_file("data.csv"), book_file("book.csv");
//     if (!data_file.is_open() || !book_file.is_open())
//     {
//         throw runtime_error("file not found");
//     }
//     ostringstream book_str;
//     ostringstream data_str;
//     book_str << book_file.rdbuf();
//     data_str << data_file.rdbuf();
//     response = book_str.str() + "|BIBLIOCHAIN|" + data_str.str();
//     book_file.clear();
//     data_file.clear();
//     data_file.close();
//     book_file.close();
// }
// else if (request.substr(0, 15) == "ADD TRANSACTION")
// {

//     json j_temp = json::parse(request.substr(15));
//     Transaction t_tmp(j_temp);
//     transactionPool.push_back(t_tmp);
//     response = "TRANSACTION ADDED";
// }
// else if (request == "SYNC POOL")
// {
//     if (!transactionPool.empty())
//     {

//         json j_temp = json::array();
//         for (auto i : transactionPool)
//         {

//             j_temp.push_back(i.toJson());
//         }
//         response = j_temp.dump();
//     }
//     else
//     {
//         response = "POOL EMPTY";
//     }
// }
// else if (request == "CLEAR POOL")
// {
//     transactionPool.clear();
//     response = "POOL CLEARED";
// }

// else if (request.substr(0, 8) == "ADD USER")
// {
//     json var = json::parse(request.substr(9));
//     std::ofstream data_file("data.csv", std::ios_base::app);
//     data_file << std::string(var["ID"]) << "," << std::string(var["private_key"]) << "," << std::string(var["public_key"]) << "," << var["token"] << "," << std::string(var["ownership_id"]) << endl;
//     response = "USER ADDED";
//     // json var = json::parse(request.substr(9));
//     // std::string ID = var["ID"];
//     // std::string private_key = var["private_key"];
//     // std::string public_key = var["public_key"];
//     // std::string token = var["token"];
//     // std::string ownership_id = var["ownership_id"];
//     // std::ofstream data_file("data.csv", std::ios_base::app);
//     // data_file << ID << "," << private_key << "," << public_key << "," << token << "," << ownership_id << std::endl;
// }
// else if (request.substr(0, 12) == "UPDATE FILES")
// {
//     std::string data = request.substr(request.find("|DATA|") + 6);
//     std::string others_book = data.substr(0, data.find("|BIBLIOCHAIN|"));
//     std::string others_data = data.substr(data.find("|BIBLIOCHAIN|") + 13);
//     std::ofstream book_file;
//     book_file.open("book.csv", std::ios::out | std::ios::trunc);
//     book_file << others_book;
//     std::ofstream data_file;
//     data_file.open("data.csv", std::ios::out | std::ios::trunc);
//     data_file << others_data;
//     book_file.close();
//     data_file.close();
//     response = "UPDATED FILES";
// }