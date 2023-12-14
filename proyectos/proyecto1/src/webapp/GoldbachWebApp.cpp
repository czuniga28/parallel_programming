// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Modificaciones hechas en 2023 <juliana.martinezaguilar@ucr.ac.cr>
// <paula.camachogonzalez@ucr.ac.cr>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include "GoldbachRequestCompleto.hpp"
#include "GoldbachHtml.hpp"
#include "ConjeturaGoldbach.hpp"
#include "GoldbachWebApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "HttpServer.hpp"


GoldbachWebApp::GoldbachWebApp() {
}

GoldbachWebApp::~GoldbachWebApp() {
}

// Singleton
GoldbachWebApp& GoldbachWebApp::getInstance() {
  static GoldbachWebApp instance;
  return instance;
}


void GoldbachWebApp::start() {
  // TODO(you): Start producers, consumers, assemblers...
  size_t cantidadT = HttpServer::getInstance().getWorkers();
  // key
  this->key = "goldbach";

  // instanciar Analizador
  this->anaUri = new GoldbachAnaUri();
  this->anaUri->createOwnQueue();


  // solvers
  this->solvers.resize(cantidadT);
  for (size_t i = 0; i < cantidadT; i++) {
  this->solvers[i] = new ConjeturaGoldbach();
    if (i == 0) {
      //! this->solvers[i]->createOwnQueue();
      this->solvers[i]->setConsumingQueue(&this->colaDeNumeros);
      this->solvers[i]->setProducingQueue(&this->colaDeResultados);
    } else {
     this->solvers[i]->setConsumingQueue(this->solvers[0]->getConsumingQueue());
     this->solvers[i]->setProducingQueue(&this->colaDeResultados);
    }
  }

  this->anaUri->setProducingQueue(this->solvers[0]->getConsumingQueue());
  // cola de entrada
  this->entranceQueue = this->anaUri->getConsumingQueue();
  this->anaUri->startThread();
  for (size_t i = 0; i < cantidadT; i++) {
    this->solvers[i]->startThread();
  }
  this->verificadores.emplace_back(new GoldbachRequestCompleto());
  this->verificadores[0]->setConsumingQueue(&this->colaDeResultados);
  this->verificadores[0]->setProducingQueue(&this->colaDeRequest);
  this->verificadores[0]->startThread();

  this->dispatchers.emplace_back(new GoldbachHtml());
  this->dispatchers[0]->setConsumingQueue(&this->colaDeRequest);
  this->dispatchers[0]->startThread();
}

void GoldbachWebApp::stop() {
  int64_t limite = this->solvers.size();
  for (int64_t index = 0; index < limite; index++) {
    this->colaDeNumeros.enqueue(NumeroG());
  }

  for (int64_t index = 0; index < limite; index++) {
    this->solvers[index]->waitToFinish();
    delete(this->solvers[index]);
  }

  this->colaDeResultados.enqueue(NumeroG());
  this->verificadores[0]->waitToFinish();
  delete(this->verificadores[0]);

  this->colaDeRequest.enqueue(nullptr);
  this->dispatchers[0]->waitToFinish();
  delete(this->dispatchers[0]);
}

bool GoldbachWebApp::handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  // If the home page was asked for a "fact?number="
  if (httpRequest.getMethod() == "GET" && httpRequest.getURI() == "/") {
     this->serveHomepage(httpRequest, httpResponse);
  }

  return false;
}

// TODO(you): Fix code redundancy in the following methods

bool GoldbachWebApp::serveHomepage(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.1");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Goldbach Conjeture";
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <form method=\"get\" action=\"/goldbach\">\n"
    << "    <label for=\"number\">Number</label>\n"
    << "    <input type=\"number\" name=\"number\" required/>\n"
    << "    <button type=\"submit\">Goldbach</button>\n"
    << "  </form>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}

