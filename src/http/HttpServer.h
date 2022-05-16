/**
 * @file HttpServer.h
 * @author saivishwak
 * @brief
 * @version 0.1
 * @date 2022-05-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <iostream>
#include <sys/socket.h>
#include <spdlog/spdlog.h>
#include <netinet/in.h>
#include <map>
#include <optional>
#include <sstream>
#include "../net/Socket.h"
#include "../message/Message.hpp"
#include "../utils/Utils.h"
//#include "Poco/Net/HTTPRequest.h"


namespace http {
  /**
   * @brief Class for HTTP Server
   *
   */
  class HttpServer {
  private:
    net::Socket* socket;
    int backlog;

    /**
     * @brief Private method called internnaly when spawnStart
     *
     */
    void start();

  public:
    HttpServer(int domain, int service, int protocol, int port, u_long interface, int backlog);
    ~HttpServer();

    /**
     * @brief Method to handle incoming requests
     *
     * @param socket
     */
    void incomingRequestHandler(int socket);
    /**
     * @brief Method to start server from thread
     *
     * @return std::thread
     */
    std::thread spawnStart();
  };

  //typedef std::function<bool(HTTPRequest* req, const std::string&)> HTTPRequestHandler;

}