// Copyright 2023 <yeshua.ramirez@ucr.ac.cr>
#ifndef HTTPCONNECTIONHANDLER_HPP
#define HTTPCONNECTIONHANDLER_HPP
#include <vector>

#include <cassert>  // copiados de HttpServer
#include <stdexcept>
#include <string>
#include "Assembler.hpp"
#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"
#include "Socket.hpp"
#include "Structs.hpp"
#include "Queue.hpp"

/**
 * @class HttpConnectionHandler
 * @brief A class for handling HTTP connections.
 *
 * This class is responsible for managing incoming HTTP connections and routing HTTP requests to web applications.
 *
 */
class HttpConnectionHandler : public Assembler<Socket, reqRes_t>{
 private:
  std::vector<HttpApp*> * applications;

 public:
  /// @brief This method consume a Socket.
  /// @details To cosume a request and a response are created
  /// and are given to the webApp.
  /// @param client socket with current connection to client.
  void consume(Socket data) override;

  /// @brief Method to start a thread.
  /// @details This class inherits from Thread.
  /// This methods is called by the method startThread.
  /// @return A code of error if there was any error.
  int run() override;

  /// @brief Gets a httpRequest and proceeds to check if one of the
  /// applications can handle it or not.
  /// @param httpRequest Request to be processed
  /// @param httpResponse httpResponse corresponding to the httpRequest
  /// @return Its return value can be true or false, depending of the return
  /// value of route()
  bool handleHttpRequest(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /// @brief Checks within the vector of applications if one of the apps can
  /// do something with the request
  /// @param httpRequest Request to be processed
  /// @param httpResponse httpResponse corresponding to the httpRequest
  /// @return True if an application can handle the request, false if not
  bool route(HttpRequest & httpRequest, HttpResponse & httpResponse);
  bool serveNotFound(HttpRequest& httpRequest, HttpResponse& httpResponse);
};

#endif  // HTTPCONNECTIONHANDLER_HPP
