#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <errno.h>
#include <networking/Json.hpp>
#include <networking/Client.hpp>

using json = nlohmann::json;
using namespace std;

int BUFFER_SIZE = 4096;

TcpClient::TcpClient(std::string server_ip_address, int server_port)
{

    m_server_ip_address = server_ip_address;
    m_server_port = server_port;
}

TcpClient::~TcpClient()
{
    closeClient();
}

int TcpClient::startClient()
{
    sleep(1);
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0)
    {
        std::cout << strerror(errno) << "cannot create client..." << std::endl;
        return 1;
    }

    m_server_socketAddress.sin_family = AF_INET;
    m_server_socketAddress.sin_port = htons(m_server_port);
    m_server_socketAddress.sin_addr.s_addr = inet_addr(m_server_ip_address.std::string::c_str());
    m_server_socketAddress_len = sizeof(m_server_socketAddress);
    while (connect(m_socket, (struct sockaddr *)&m_server_socketAddress, m_server_socketAddress_len) != 0)
    {
        std::cout << strerror(errno) << std::endl;
        std::cout << "Trying Again....!" << std::endl;
        sleep(2);
    }
    return 0;
}

// int TcpClient::startClient()
// {
//     sleep(1);
//     m_socket = socket(AF_INET, SOCK_STREAM, 0);
//     if (m_socket < 0)
//     {
//         std::cout << strerror(errno) << "cannot create client..." << std::endl;
//         return 1;
//     }

//     m_server_socketAddress.sin_family = AF_INET;
//     m_server_socketAddress.sin_port = htons(m_server_port);
//     m_server_socketAddress.sin_addr.s_addr = inet_addr(m_server_ip_address.std::string::c_str());
//     m_server_socketAddress_len = sizeof(m_server_socketAddress);

//     // set socket to non - blocking mode
//     int flags = fcntl(m_socket, F_GETFL, 0);
//     if (flags < 0)
//     {
//         std::cout << strerror(errno) << std::endl;
//         return 1;
//     }
//     if (fcntl(m_socket, F_SETFL, flags | O_NONBLOCK) < 0)
//     {
//         std::cout << strerror(errno) << std::endl;
//         return 1;
//     }

//     // connect with timeout
//     int result;
//     struct timeval tv;
//     fd_set wfds;

//     result = connect(m_socket, (struct sockaddr *)&m_server_socketAddress, m_server_socketAddress_len);
//     if (result == 0)
//     {
//         // connection success
//         return 0;
//     }
//     else if (errno != EINPROGRESS)
//     {
//         // connection error
//         std::cout << strerror(errno) << std::endl;
//         return 1;
//     }

//     // wait for socket to become ready for writing, with timeout of 4-5 seconds
//     FD_ZERO(&wfds);
//     FD_SET(m_socket, &wfds);
//     tv.tv_sec = 4;
//     tv.tv_usec = 0;
//     result = select(m_socket + 1, NULL, &wfds, NULL, &tv);
//     if (result == 0)
//     {
//         // timeout
//         std::cout << "Connection timed out" << std::endl;
//         close(m_socket);
//         return 1;
//     }
//     else if (result < 0)
//     {
//         // select error
//         std::cout << strerror(errno) << std::endl;
//         close(m_socket);
//         return 1;
//     }
//     else
//     {
//         // socket is ready for writing
//         int error = 0;
//         socklen_t len = sizeof(error);
//         if (getsockopt(m_socket, SOL_SOCKET, SO_ERROR, &error, &len) < 0 || error != 0)
//         {
//             // connection error
//             std::cout << strerror(errno) << std::endl;
//             close(m_socket);
//             return 1;
//         }
//         else
//         {
//             // connection success
//             return 0;
//         }
//     }
// }

void TcpClient::sendQuery(std::string query)
{
    startClient();
    m_query = query;
    int sentBytes;
    sentBytes = strlen(m_query.std::string::c_str());
    if (write(m_socket, m_query.std::string::c_str(), sentBytes) != sentBytes)
        std::cout << strerror(errno) << std::endl;
    // std::cout << "Query Sent Successfully!" << std::endl;
}

// void TcpClient::sendQuery(std::string query)
// {
//     if (startClient() != 0)
//     {
//         return;
//     }

//     m_query = query;
//     int sentBytes;
//     sentBytes = strlen(m_query.std::string::c_str());
//     if (write(m_socket, m_query.std::string::c_str(), sentBytes) != sentBytes)
//     {
//         std::cout << strerror(errno) << std::endl;
//         return;
//     }

//     std::cout << "Query Sent Successfully!" << std::endl;
// }

std::string TcpClient::receiveResponse()
{
    int receivedBytes;
    char buffer[BUFFER_SIZE];
    m_incomingMessage = "";
    while ((receivedBytes = read(m_socket, buffer, BUFFER_SIZE)) > 0)
    {
        // std::cout << buffer << std::endl;
        buffer[receivedBytes] = '\0';
        m_incomingMessage += buffer;
    }
    if (receivedBytes < 0)
    {
        m_incomingMessage = "";
        std::cout << strerror(errno) << std::endl;
    }

    return m_incomingMessage;
}
// std::string TcpClient::receiveResponse()
// {
//     int receivedBytes;
//     char buffer[BUFFER_SIZE];
//     m_incomingMessage = "";

//     // set the timeout
//     struct timeval tv;
//     tv.tv_sec = 4; // 4 seconds
//     tv.tv_usec = 0;
//     setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof tv);

//     while ((receivedBytes = read(m_socket, buffer, BUFFER_SIZE)) > 0)
//     {
//         std::cout << buffer;
//         buffer[receivedBytes] = '\0';
//         m_incomingMessage += buffer;
//     }
//     if (receivedBytes < 0)
//     {
//         if (errno == EWOULDBLOCK || errno == EAGAIN)
//         {
//             std::cout << "Connection timed out." << std::endl;
//         }
//         else
//         {
//             std::cout << strerror(errno) << std::endl;
//         }
//     }

//     return m_incomingMessage;
// }

void TcpClient::printResponse()
{
    // std::cout << m_incomingMessage << std::endl;
}

void TcpClient::closeClient()
{
    close(m_socket);
}
