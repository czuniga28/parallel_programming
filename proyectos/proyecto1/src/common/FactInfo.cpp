// Copyright 2023 <yeashua.ramirez@ucr.ac.cr>
#include "FactInfo.hpp"
#include <tuple>

// Asignacion de response y request para
// trabajar Factorizacion
FactInfo::FactInfo(HttpResponse& response, HttpRequest& request) :
  response(response), request(request) {}

FactInfo::~FactInfo() {
  //! innecesario?
}

// Condiciones de parada con esto:
FactInfo::FactInfo() : factorizacionesTotalCantidad(-20), trabajados(-20),
  response(Socket()), request(Socket()) {}

bool FactInfo::operator ==
(const FactInfo& otroFactInfo) const {
  if (this->factorizacionesTotalCantidad ==
  otroFactInfo.factorizacionesTotalCantidad &&
  this->trabajados == otroFactInfo.trabajados) {
    return true;
  }
  return false;
}

void FactInfo::setFactorizacion(std::vector<std::tuple<int64_t, int64_t>> fact,
int64_t posicion) {
  // std::cout<<"posicion "<<posicion<<std::endl;
  this->factorizaciones[posicion] = fact;
  // this->sumas.push_back(suma);
}

int64_t FactInfo::getNumero(int64_t posicion) {
  return this->numeros[posicion];
}

int64_t FactInfo::getCantidadNumeros() {
  return this->numeros.size();
}

bool FactInfo::hemosTerminado(NumeroF& numeroF) {
  this->trabajados += 1;
  this->basesCantidades[numeroF.posicion] = numeroF.totalBases;
  this->factorizacionesTotalCantidad += numeroF.totalBases;
  return (numeroF.direccionRequest->trabajados ==
    (int64_t)numeroF.direccionRequest->numeros.size());
}

void FactInfo::setNumeros(std::vector<int64_t>& numeros) {
  this->numeros.reserve(numeros.size());
  int64_t limite = numeros.size();
  for (int64_t index = 0; index < limite; index++) {
    this->numeros.emplace_back(numeros[index]);
  }
  // std::cout<<"se han reservado en goldbachinfo "
  // <<numeros.size()<<std::endl;
  // this->sumas.reserve(numeros.size());
  this->factorizaciones.resize(numeros.size());
  this->basesCantidades.reserve(numeros.size());
}

void FactInfo::impresionResultadosDefinitivos() {
  // std::cout<<"imprimiendo fact"<<std::endl;
  std::string title = "";
  std::string body = "";
  std::vector<int64_t> valores =
  this->numeros;
  std::vector<std::vector<std::tuple<int64_t, int64_t>>> resultados =
  this->factorizaciones;

  title += "Prime factorization of ";
  for (size_t i = 0;  i < valores.size(); i++) {
    title += std::to_string(valores[i]);
    // Colocar una coma y espacio para separación en caso de que no sea ultimo
    if (i != valores.size() - 1) {
      title += ", ";
    }
    body += "  <h2>" + std::to_string(valores[i]) + "</h2>\n";
    body += "  <p>" + std::to_string(valores[i]) + " : ";
    if (valores[i] == 1 || valores[i] == 0) {  // Caso no se puede factorizar
      body += "NA";
    } else if (valores[i] < 0) {  // Caso negativo
      body += "invalid number";
    } else {  // Resto de los casos
      for (size_t j = 0; j < resultados[i].size(); j++) {
        body += std::to_string(std::get<0>(resultados[i][j]));
        // Si el exponente del factor primo es > 1 colocarlo en body
        if (std::get<1>(resultados[i][j]) != 1) {
          body += "<sup>" + std::to_string(std::get<1>(resultados[i][j]));
          body += "</sup>";
        }
        body += " ";  // Separar factores con espacio
      }
    }
    body += "</p>\n";
  }

  this->impresionAuxiliar(title, body);
}

void FactInfo::impresionAuxiliar(std::string title,
    std::string body) {
  //! Preguntar a Juliana
  // std::cout<<"imprimiendo 2 fact"<<std::endl;

  this->response.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << body
    << "  <hr><p><a href=\"/\">Back</a></p>\n"
    << "</html>\n";

    this->response.send();
}
