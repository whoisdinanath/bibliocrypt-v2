#ifndef __GLOBAL_VARS_HPP__
#define __GLOBAL_VARS_HPP__
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <cryptography/User.hpp>
#include <blockchain/Transaction.hpp>
#include <networking/Client.hpp>
#include <networking/Server.hpp>
#include <blockchain/BlockChain.hpp>
#include <blockchain/SmartContract.hpp>
#include <memory>
#include <blockchain/Utils.hpp>
#include <chrono>
#include <atomic>

namespace globalVars
{
    extern std::unique_ptr<TcpServer> m_server;
    extern std::string OTHER_SERVER_IP;
    extern int OTHER_SERVER_PORT;
    extern std::string MY_SERVER_IP;
    extern int MY_SERVER_PORT;
    extern std::unique_ptr<User> global_user;
    extern std::vector<std::vector<std::string>> m_user_data;
    extern std::vector<std::vector<std::string>> m_book_data;
    extern char QUERY[1024];
    extern std::string response;
    extern json j_request;
    extern json j_response;
    extern bool exit_flag;
}

void server();



#endif // __GLOBAL_VARS_HPP__