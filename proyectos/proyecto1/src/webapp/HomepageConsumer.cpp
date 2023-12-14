// Copyright 2023 <juliana.martinez@ucr.ac.cr>
#include "HomepageConsumer.hpp"
#include <iostream>

void HomepageConsumer::consume(reqRes_t data) {
  if (data.httpRequest.getMethod() == "GET" &&
      data.httpRequest.getURI() == "/") {
    this->serveHomepage(data.httpRequest, data.httpResponse);
  }
}

void HomepageConsumer::consumeForever() {
    assert(this->consumingQueue);
    while (true) {
      // Get the next data to consume, or block while queue is empty
      const reqRes_t& data = this->consumingQueue->dequeue();
      // If data is the stop condition, stop the loop
      if ( data.httpRequest.getURI() == "" ) {
        break;
      }
      // Process this data
      this->consume(data);
      if (data.httpRequest.getURI() != "/") {
        this->producingQueue->enqueue(data);
      }
    }
  }

// Trabajara siempre que se pueda consumir
int HomepageConsumer::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

bool HomepageConsumer::serveHomepage(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.1");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Goldbach & Factorization";
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <form method=\"get\" action=\"/fact\">\n"
    << "    <button type=\"submit\">Prime factorization</button>\n"
    << "  </form>\n"
    << "  <form method=\"get\" action=\"/goldbach\">\n"
    << "    <button type=\"submit\">Goldbach's conjeture</button>\n"
    << "  </form>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}
