// Copyright 2023 <yeashua.ramirez@ucr.ac.cr>
#ifndef NumeroG_HPP
#define NumeroG_HPP

// includes necesarios:
  #include <cstdint>
  #include <iostream>
  #include <string>
  #include <vector>
  #include "common.hpp"
  #include "HttpResponse.hpp"
  #include "HttpRequest.hpp"

class GoldbachInfo;

/// @struct NumeroG
/// @brief Estructura que representa un número para cálculos de Goldbach.
struct NumeroG {
  DECLARE_RULE4(NumeroG, default);

 public:
  /// @brief Número para cálculos de Goldbach.
  int64_t numero;

  /// @brief Posición del número en la secuencia de cálculos de Goldbach.
  int64_t posicion;

  /// @brief Total de sumas calculadas con este número.
  int64_t totalSumas = 0;

  /// @brief Dirección al objeto GoldbachInfo relacionado con este número.
  GoldbachInfo* direccionRequest;

 public:
  /// @brief Constructor por defecto para uso basico
  NumeroG() : numero(0), posicion(-20),
  direccionRequest(nullptr) {}

  /// @brief Constructor para casos en los que trabajar
  /// numeros indp
  /// @param numero Numero a trabajar
  /// @param posicion Posicion
  /// @param direccionRequest puntero a direccionRequest original
  NumeroG(int64_t numero, int64_t posicion,
  GoldbachInfo* direccionRequest) : numero(numero),
  posicion(posicion), direccionRequest(direccionRequest) {
  }

  /// @brief Comparador de NumeroGs
  /// @param otroNumeroG NumeroG a comparar
  /// @return FALSE cuando son distintos, TRUE iguales
  bool operator == (const NumeroG& otroNumeroG)
  const {
    // cada uno de los elementos deben ser iguales
    if (this->numero == otroNumeroG.numero &&
    this->posicion == otroNumeroG.posicion &&
    this->direccionRequest == otroNumeroG.direccionRequest &&
    this->totalSumas == otroNumeroG.totalSumas) {
      return true;
    }
    return false;
  }
};

#endif  // NumeroG_HPP
