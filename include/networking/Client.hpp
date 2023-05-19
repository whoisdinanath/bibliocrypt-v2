#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

// int client(char *ip_address, int PORT, char *QUERY);

class TcpClient
{
private:
    std::string m_server_ip_address;
    int m_server_port;
    int m_socket;
    sockaddr_in m_server_socketAddress;
    socklen_t m_server_socketAddress_len;
    std::string m_server_response;
    std::string m_query;
    std::string m_incomingMessage;

public:
    TcpClient(std::string server_ip_address, int server_port);
    ~TcpClient();
    int startClient();
    void closeClient();
    void sendQuery(std::string query);
    std::string receiveResponse();
    void printResponse();
};

#endif // __CLIENT_HPP__