// Copyright 2023 <yeashua.ramirez@ucr.ac.cr>
#ifndef NumeroF_HPP
#define NumeroF_HPP

// includes necesarios:
  #include <cstdint>
  #include <iostream>
  #include <tuple>
  #include <string>
  #include <vector>
  #include "common.hpp"
  #include "HttpResponse.hpp"
  #include "HttpRequest.hpp"

class FactInfo;

/// @struct NumeroF
/// @brief Estructura que representa un número para cálculos de factorización.
struct NumeroF {
  DECLARE_RULE4(NumeroF, default);

 public:
  /// @brief Número para cálculos de factorización prima.
  int64_t numero;

  /// @brief Posición del número en la secuencia de cálculos.
  int64_t posicion;

  /// @brief Total de bases utilizadas en los cálculos.
  int64_t totalBases = 0;

  /// @brief Dirección al objeto FactInfo relacionado con este número.
  FactInfo* direccionRequest;

 public:
  /// @brief Constructor por defecto para uso basico
  NumeroF() : numero(0), posicion(-20),
  direccionRequest(nullptr) {}

  /// @brief Constructor para casos en los que trabajar
  /// numeros indp
  /// @param numero Numero a trabajar
  /// @param posicion Posicion
  /// @param direccionRequest puntero a direccionRequest original
  NumeroF(int64_t numero, int64_t posicion,
  FactInfo* direccionRequest) : numero(numero),
  posicion(posicion), direccionRequest(direccionRequest) {
  }

  /// @brief Comparador de NumeroFs
  /// @param otroNumeroF NumeroF a comparar
  /// @return FALSE cuando son distintos, TRUE iguales
  bool operator == (const NumeroF& otroNumeroF)
  const {
    // cada uno de los elementos deben ser iguales
    if (this->numero == otroNumeroF.numero &&
    this->posicion == otroNumeroF.posicion &&
    this->direccionRequest == otroNumeroF.direccionRequest &&
    this->totalBases == otroNumeroF.totalBases) {
      return true;
    }
    return false;
  }
};

#endif  // NumeroF_HPP
