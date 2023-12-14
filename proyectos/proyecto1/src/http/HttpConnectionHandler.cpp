// Copyright 2023 <yeshua.ramirez@ucr.ac.cr>
#include "HttpConnectionHandler.hpp"
#include <vector>

// Metodos heredados:
// Cada HttpConnectionHandler hace esta rutina y no interfiere con solicitudes
// extra que se pueden hacer, como lo hacia en la version original
// HandleClientConnection: esto es solo un copy paste de ese rutina vieja,
// modificada para que reciba sockets y no clients, para, asi, trabajar los
// hilos. Ademas de haberse
// eliminado el ultimo break
void HttpConnectionHandler::consume(Socket data) {
  // While the same client asks for HTTP requests in the same connection
// !HttpRequest httpRequest(data);
  while (true) {
    // Create an object that parses the HTTP request from the socket
    HttpRequest httpRequest(data);
    // !httpRequest(data);
    // If the request is not valid or an error happened
    if (!httpRequest.parse()) {
      // Non-valid requests are normal after a previous valid request. Do not
      // close the connection yet, because the valid request may take time to
      // be processed. Just stop waiting for more requests
      break;
    }

    HttpResponse httpResponse(data);
    // A complete HTTP client request was received. Create an object for the
    reqRes_t rq(httpRequest, httpResponse);
    // Give subclass a chance to respond the HTTP request
    // const bool handled = this->handleHttpRequest(rq.httpRequest,
    // rq.httpResponse);

    // If subclass did not handle the request or the client used HTTP/1.0
    if (httpRequest.getHttpVersion() == "HTTP/1.0") {
      // The socket will not be more used, close the connection
      data.close();
      break;
    }
    produce(rq);
  }
}
// Trabajara siempre que se pueda consumir
int HttpConnectionHandler::run() {
    this->consumeForever();
    return EXIT_SUCCESS;
}

// Metodos que se pideron mover desde HttpServer:


bool HttpConnectionHandler::handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  // Print IP and port from client
  const NetworkAddress& address = httpRequest.getNetworkAddress();
  Log::append(Log::INFO, "connection",
    std::string("connection established with client ") + address.getIP()
    + " port " + std::to_string(address.getPort()));

  // Print HTTP request
  Log::append(Log::INFO, "request", httpRequest.getMethod()
    + ' ' + httpRequest.getURI()
    + ' ' + httpRequest.getHttpVersion());

  return this->route(httpRequest, httpResponse);
}

bool HttpConnectionHandler::route(HttpRequest& httpRequest, HttpResponse&
httpResponse) {
  // Traverse the chain of applications
  for (size_t index = 0; index < this->applications->size(); ++index) {
    // If this application handles the request
    HttpApp* app = (*this->applications)[index];  // agregado *
    // delante this, porque
    // no dejaba asignarlo: se desreferencia
    if (app->handleHttpRequest(httpRequest, httpResponse)) {
      return true;
    }
  }

  // Unrecognized request
  return this->serveNotFound(httpRequest, httpResponse);
}

bool HttpConnectionHandler::serveNotFound(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setStatusCode(404);
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Not found";
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace} h1 {color: red}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <p>The requested resouce was not found on this server.</p>\n"
    << "  <hr><p><a href=\"/\">Homepage</a></p>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}
