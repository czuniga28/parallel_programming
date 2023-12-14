// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Modificaciones hechas en 2023 <juliana.martinezaguilar@ucr.ac.cr>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

#include "HomeWebApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Structs.hpp"

HomeWebApp::HomeWebApp() {
}

HomeWebApp::~HomeWebApp() {
}

// Singleton
HomeWebApp& HomeWebApp::getInstance() {
  static HomeWebApp instance;
  return instance;
}

void HomeWebApp::start() {
  this->key = "/";
  // instanciar Analizador
  this->homeConsumer = new HomepageConsumer();
  this->homeConsumer->createOwnQueue();
  // TODO(you): Start producers, consumers, assemblers...
  // Establecer e iniciar cola de consumo
  this->entranceQueue = this->homeConsumer->getConsumingQueue();
  this->homeConsumer->startThread();
}

void HomeWebApp::stop() {
  this->homeConsumer->getConsumingQueue()->enqueue(reqRes_t());
  this->homeConsumer->waitToFinish();
  delete this->homeConsumer;
}

bool HomeWebApp::handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  // If the home page was asked
  if (httpRequest.getMethod() == "GET" && httpRequest.getURI() == "/") {
    return this->serveHomepage(httpRequest, httpResponse);
  }
  // Unrecognized request
  return false;
}

bool HomeWebApp::serveHomepage(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
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
