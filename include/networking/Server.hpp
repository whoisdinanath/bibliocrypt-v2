#ifndef __SERVER_HPP__
#define __SERVER_HPP__
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <blockchain/BlockChain.hpp>
#include <blockchain/Transaction.hpp>
#include <blockchain/SmartContract.hpp>
#include <blockchain/Utils.hpp>
#include <networking/Json.hpp>
#include <networking/Server.hpp>
namespace Chain
{
    extern Blockchain BIBLIOCHAIN;
    extern std::vector<Transaction> m_transactionPool;
    extern int noNodes;

}
class TcpServer
{
public:
    TcpServer(std::string ip_address, int port);
    ~TcpServer();
    int startServer();
    void closeServer();
    void acceptConnection(int &new_socket);
    void sendResponse();
    void startListen();
    void buildResponse(std::string request);
    // void pushTransaction(Transaction);
    // std::vector<Transaction> getTransactionPool();
    // int getChainSize();

private:
    std::string m_ip_address;
    int m_port;
    int m_socket;
    int m_new_socket;
    std::string m_incomingMessage;
    sockaddr_in m_socketAddress;
    sockaddr_in m_clientSocketAddress;
    socklen_t m_socketAddress_len;
    socklen_t m_clientSocketAddress_len;
    std::string m_serverMessage;
    // Blockchain m_myChain;
    // std::vector<Transaction> transactionPool;
};

#endif // __SERVER_HPP__