// Copyright 2023 <yeshua.ramirez@ucr.ac.cr>
#include "FactAnaUri.hpp"
#include <iostream>
#include <tuple>

void FactAnaUri::consume(reqRes_t data) {
  if (data.httpRequest.getMethod() == "GET" &&
  data.httpRequest.getURI() == "/fact?") {
     this->serveHomepage(data.httpRequest, data.httpResponse);
  }
  // If the request starts with "fact/" is for this web app
  if (data.httpRequest.getURI().rfind("/fact/fact", 0) == 0) {
    this->analizarUri(data.httpRequest, data.httpResponse);
  }
}
// Trabajara siempre que se pueda consumir
int FactAnaUri::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

bool FactAnaUri::serveHomepage(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.1");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Prime factorization";
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <form method=\"get\" action=\"/fact/fact\">\n"
    << "    <label for=\"numbers\">Numbers</label>\n"
    << "    <input type=\"text\" name=\"numbers\" required/>\n"
    << "    <button type=\"submit\">Factorize</button>\n"
    << "  </form>\n"
    << "  <hr><p><a href=\"/\">Back</a></p>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}


void FactAnaUri::analizarUri(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");
  // Permitir el ingreso a impresión de factorización si entran uno o más
  // números enteros separados por comas
  std::smatch matches;
  std::regex inQuery("^/fact/fact(/|\\?numbers=)((-?\\d+)(%2C(-?\\d+))*)$");
  if (std::regex_search(httpRequest.getURI(), matches, inQuery)) {
    assert(matches.length() >= 3);
    // match[2] almacena el resto de la cadena posteriores a fact?number=
    // Declarar vector a utilizar
    std::vector<int64_t> valores;
    std::vector<std::vector<std::tuple<int64_t, int64_t>>> resultados;
    // Separar los valores de la URL
    separarValoresURL(matches[2], &valores);
    // Instancia de factorización

    FactInfo *request = new FactInfo(httpResponse, httpRequest);
    request->setNumeros(valores);
    int64_t limite = request->getCantidadNumeros();
    for (int64_t index = 0; index < limite; index++) {
      NumeroF numeroF(request->getNumero(index),
      index, request);
      // Encolar nuevo número
      // this->colaDeNumeros.enqueue(numeroF);  //! this->produce(numeroF);
      this->producingQueue->enqueue(numeroF);
    }
  } else {
    // Build the body for an invalid request
    crearCuerpoInvalidRequest(httpResponse);
  }
}


void FactAnaUri::separarValoresURL(std::string strValores,
std::vector<int64_t>* valores) {
    int64_t matches_count = 0;
    std::smatch matches;
    // Valore por buscar son enteros positivos o negativos
    std::regex inQuery("-\\d+|\\d+");
    while (std::regex_search(strValores, matches , inQuery)) {
      // Agregar al vector únicamente valores que no conforme el %2C(,)
      if (matches_count % 2 == 0) {
        int64_t actual_number = stoll(matches[0]);
        valores->push_back(actual_number);
      }
      // Cadena pasa a ser la subcadena posterior al número encontrado
      strValores = matches.suffix().str();
      matches_count++;
    }
  }

void FactAnaUri::crearCuerpoInvalidRequest(HttpResponse& httpResponse) {
  std::string title = "Invalid request";
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
    << "  <h1 class=\"err\">" << title << "</h1>\n"
    << "  <p>Invalid request for factorization</p>\n"
    << "  <hr><p><a href=\"/\">Back</a></p>\n"
    << "</html>\n";
    httpResponse.send();
}
