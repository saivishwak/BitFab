/**
 * @file HttpServer.cpp
 * @author saivishwak
 * @brief 
 * @version 0.1
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "HttpServer.h"

http::HttpServer::HttpServer(int domain, int service, int protocol, int port, u_long interface, int backlog) {
  this->backlog = backlog;
  this->socket = new net::Socket(domain, service, protocol, port, interface, true);
  spdlog::info("Http server initialzed ...");
}

http::HttpServer::~HttpServer() {
  delete this->socket;
}

std::thread http::HttpServer::spawnStart() {
    spdlog::info("Spawning HTTP Server Thread ...");
    return std::thread([=] { this->start(); });
}

void http::HttpServer::start() {
  // Bind to the port
  int bindSocketConnection = this->socket->connectToNetwork();
  this->socket->testConnection(bindSocketConnection, "Error while binding the socket");

  // start listening for connections on our socket
  int listenR = listen(this->socket->getSock(), this->backlog);
  this->socket->testConnection(listenR, "Error while Listening on socket");

  sockaddr_storage client_addr;
  socklen_t client_addr_size = sizeof(client_addr);

  while (true) {
    struct sockaddr_in clnt;
    socklen_t clnt_len = sizeof(clnt);
    int acceptFD = accept(this->socket->getSock(), (struct sockaddr*)&client_addr, &client_addr_size);
    
    if (acceptFD == -1) {
      spdlog::error("Error while Accepting on HTTP socket\n");
      continue;
    }
    else {
      spdlog::info("Accepted new connection {}", acceptFD);
      std::thread th1([=] { this->incomingRequestHandler(acceptFD); });
      th1.detach();
    }
  }

  close(this->socket->getSock());
  delete this->socket;
  return;
}

void http::HttpServer::incomingRequestHandler(int newSocket){
  std::thread::id thread_id = std::this_thread::get_id();
    spdlog::info("HTTP incomingRequestHandler thread spwaned");
    char buffer[4096];

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int n = read(newSocket, buffer, sizeof(buffer));
        if (n < 0) {
            spdlog::error("Error in reading HTTP Request from socket");
            break;
        }
        if (n == 0) {
            spdlog::info("HTTP Client disconnected");
            break;
        }

        spdlog::info("Message from client : {} - {}", newSocket, buffer);
        std::string res = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
        // std::string res = "Message from server - " + std::string(buffer) + "\n";
        // int bytes_sent = send(socket, res.data(), res.length(), 0);
        // msg::Block b = msg::Message::unmarshall(std::string(buffer));
        // switch (Utils::hashit(b.getType())) {
        // case Utils::ePing: {
        //   //Do dothin
        // }
        // default:
        // {
        //     // Do nothing
        // }
        // }
        int bytes_sent = send(newSocket, res.data(), res.length(), 0);
        close(newSocket);
    }
    close(newSocket);
    return;
}