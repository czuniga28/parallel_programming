// Copyright Modificaciones Taller 2023 <paula.camachogonzalez@ucr.ac.cr>
#include "HttpDispatcher.hpp"

int HttpDispatcher::run() {
  // Inicia la ejecución para consumir datos de la cola
  this->consumeForever();
  return EXIT_SUCCESS;
}

std::string HttpDispatcher::extractKey(const reqRes_t& data) const {
  // Extrae la clave (key) a partir de la URI en la solicitud HTTP
  std::string uri = data.httpRequest.getURI();
  std::string key;
  if (uri == "/") {
    key = uri;
  } else if (uri.find("goldbach") != std::string::npos) {
    if (uri.length() >= 9) {
      key = uri.substr(1, 8);
    }
  } else if (uri.find("fact") != std::string::npos) {
    if (uri.length() >= 5) {
      key = uri.substr(1, 4);
    }
  }
  return key;
}

void HttpDispatcher::consume(reqRes_t data) {
  // Consume los datos y los encola en la cola correspondiente
  // basándose en la clave (key)
  const std::string& key = this->extractKey(data);
  const auto& itr = this->toQueues.find(key);
  if ( itr != this->toQueues.end() ) {
    itr->second->enqueue(data);
  }
}

void HttpDispatcher::stop() {
  // Detiene el proceso de consumo de datos
  // encolando un elemento de parada (vacío)
  reqRes_t stop;
  this->consumingQueue->enqueue(stop);
  this->waitToFinish();
}
