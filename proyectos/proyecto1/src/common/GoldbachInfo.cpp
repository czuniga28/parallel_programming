// Copyright 2023 <yeashua.ramirez@ucr.ac.cr>
#include "GoldbachInfo.hpp"
#include <vector>

// Asignacion de response y request para
// trabajar Goldbach
GoldbachInfo::GoldbachInfo(HttpResponse& response,
HttpRequest& request) :
response(response), request(request) {
}

GoldbachInfo::~GoldbachInfo() {
  //! innecesario?
}

// Condiciones de parada con esto:
GoldbachInfo::GoldbachInfo() :
sumasTotalCantidad(-20), trabajados(-20),
response(Socket()), request(Socket()) {
}


bool GoldbachInfo::operator ==
(const GoldbachInfo& otroGoldbachInfo) const {
  if (this->sumasTotalCantidad ==
  otroGoldbachInfo.sumasTotalCantidad &&
  this->trabajados == otroGoldbachInfo.trabajados) {
    return true;
  }
  return false;
}

void GoldbachInfo::setSuma(std::vector<std::vector<int64_t>> suma,
    int64_t posicion) {
  // std::cout << "posicion " << posicion << std::endl;
  this->sumas[posicion] = suma;
  // this->sumas.push_back(suma);
}

int64_t GoldbachInfo::getNumero(int64_t posicion) {
  return this->numeros[posicion];
}

int64_t GoldbachInfo::getCantidadNumeros() {
  return this->numeros.size();
}

bool GoldbachInfo::hemosTerminado(NumeroG& NumeroG) {
  this->trabajados += 1;
  this->sumasCantidades[NumeroG.posicion] =
  NumeroG.totalSumas;
  this->sumasTotalCantidad += NumeroG.totalSumas;
  return (NumeroG.direccionRequest->trabajados ==
  (int64_t)NumeroG.direccionRequest->numeros.size());
}

void GoldbachInfo::setNumeros(std::vector<int64_t>& numeros) {
  this->numeros.reserve(numeros.size());
  int64_t limite = numeros.size();
  for (int64_t index = 0; index < limite; index++) {
    this->numeros.emplace_back(numeros[index]);
  }
  // std::cout << "se han reservado en goldbachinfo " << numeros.size() <<
  // std::endl;
  // this->sumas.reserve(numeros.size());
  this->sumas.resize(numeros.size());
  this->sumasCantidades.reserve(numeros.size());
}

void GoldbachInfo::impresionResultadosDefinitivos() {
  // std::cout << "imprimiendo 1" << std::endl;
  std::string title = "";
  std::string body = "";
  std::vector<int64_t> valores = this->numeros;
  std::vector<std::vector<std::vector<int64_t> >> resultados =
  this->sumas;
  title += "Goldbach's conjeture of ";
  body += "  <h2> Total: " + std::to_string(valores.size()) + " numbers ";
  body += std::to_string(this->sumasTotalCantidad) + " sums </h2>\n";
  for (size_t i = 0;  i < valores.size(); i++) {
    title += std::to_string(valores[i]);
    // Colocar una coma y espacio para separación en caso de que no sea ultimo
    if (i != valores.size() - 1) {
      title += ", ";
    }
    body += "  <h2>" + std::to_string(valores[i]) + "</h2>\n";
    body += "  <p>" + std::to_string(valores[i]) + " : ";
    // Caso 1: Valores en los que no se cumple la conjetura
    if (-5 <= valores[i] && valores[i] <= 5) {
      body += "NA";
    } else if (valores[i] > 5) {  // Caso positivo: Mostrar número de sumas
      //! body += std::to_string(resultados[i].size()) + " sums";
      // body += std::to_string(this->sumasTotalCantidad) + " sums";
      body += std::to_string(this->sumasCantidades[i]) + " sums";
    } else {  // Casos negativos menores o igual a -5
      for (size_t j = 0; j < resultados[i].size(); j++) {
        for (size_t k = 0; k < resultados[i][j].size(); k++) {
          body += std::to_string(resultados[i][j][k]) + "";
          if (k != resultados[i][j].size() - 1) {
            body += " + ";
          }
        }
        if (j != resultados[i].size() - 1) {
          body += ",";  // Separar factores con coma
        }
        body += " ";
      }
    }
    body += "</p>\n";
  }

  this->impresionAuxiliar(title, body);
}

void GoldbachInfo::impresionAuxiliar(std::string title,
    std::string body) {
  // std::cout << "imprimiendo 2" << std::endl;
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
