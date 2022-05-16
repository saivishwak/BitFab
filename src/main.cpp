/*
 * @file main.cpp
 * @author saivishwak
 * @brief 
 * @version 0.1
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <string>
#include <thread>
#include <signal.h>
#include <fstream>
#include <chrono>
#include <filesystem>
#include "net/P2PServer.h"
#include "http/HttpServer.h"
#include "db/Db.h"
#include "utils/Config.hpp"
#include <json/json.h>
#include "message/Message.hpp"
#include <spdlog/spdlog.h>

const std::string CONFIG_PATH = "../../config.json";

void sighandler(int signum, int* socketFD) {
    spdlog::info("Caught signal ", signum, *socketFD);
    // Terminate program
    exit(signum);
}

int main(int argc, char* argv[]) {
    // Let's check if port number is supplied or not..
    spdlog::info("Welcome to BlazeCoin!");

    /*if (argc < 2) {
        spdlog::error("Need minimum of 1 arg .. run program as 'program <port>'\n");
        return -1;
    }*/
    Utils::Config* constants = new Utils::Config(std::string(CONFIG_PATH));

    // Handle user interruption
    signal(SIGINT, (void (*)(int))sighandler);

    //int portNum = atoi(argv[1]);
    int portNum = constants->rootNode["p2pDefaultPort"].asInt();
    const unsigned int backLog = 8;  // number of connections allowed on the incoming queue
    net::P2PServer* P2pServer = new net::P2PServer(portNum, backLog);

    //http::HttpServer* httpServer = new http::HttpServer(AF_INET, SOCK_STREAM, 0 , constants->rootNode["httpDefaultPort"].asInt(), INADDR_ANY, 50);

    std::thread p2pServerThread = P2pServer->spawnStart();
    p2pServerThread.detach();

    //std::thread HttpServerThread = httpServer->spawnStart();
    //HttpServerThread.detach();

    //make call to the known_hosts
    for (auto x : constants->seedPorts) {
        if (x != portNum) {
            //do something
            std::thread clientThread([=] {P2pServer->connectToPeer(x);});
            clientThread.detach();
        }
    }

    std::thread loopThread([&P2pServer] {while (true) { std::this_thread::sleep_for(std::chrono::milliseconds(1000));spdlog::info("No of peers connected: {}", P2pServer->peers.size()); };});
    loopThread.detach();

    while (1) {
        //do nothing  just stoping the main thread
    }

    return 0;
}
