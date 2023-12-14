// Copyright 2023 <paula.camachogonzalez@ucr.ac.cr>
#ifndef FACTORIZACIONPRIMA_HPP
#define FACTORIZACIONPRIMA_HPP

#include <iostream>
#include <tuple>
#include <vector>
#include "common.hpp"
#include "CribaEratostenes.hpp"
#include "NumeroF.hpp"
#include "Assembler.hpp"

/**
 * @class FactorizacionPrima
 * @brief Clase que realiza la factorización prima de números.
 *
 */
class FactorizacionPrima :
public virtual Assembler<NumeroF, NumeroF> {
DISABLE_COPY(FactorizacionPrima);

 private:
  /// @brief numeros a factorizar
  std::vector<int64_t> factorizados;
  /// @brief vectores de tuplas obtenidos al factorizar
  std::vector<std::vector<std::tuple<int64_t, int64_t>>> factorizaciones;

 public:
  /// @brief Constructor por defecto
  FactorizacionPrima() = default;

  /// @brief destructor por defecto
  ~FactorizacionPrima() = default;


 public:
  /// @brief Realiza las factorizaciones para n numeros
  void factorizar(std::vector<int64_t> numeros);

  /// @brief Solicitud de numeros factorizados, NO respuestas
  /// @return numeros factorizados en un principio
  inline std::vector<int64_t> getFactorizados() {
    return this->factorizados;
  }
  /// @brief solicitud de factorizaciones, SI son las respuestas
  /// @return factorizaciones
  inline std::vector<std::vector<std::tuple<int64_t, int64_t>>>
      getFactorizaciones() {
    return this->factorizaciones;
  }

  /// @brief Impresion de los resultados
  /// @warning SOLO usarse en debugging, NO en web
  void imprimirFactorizacionPrima();

  int run() override;
  void consume(NumeroF numeroF) override;
};

#endif  // FACTORIZACIONPRIMA_HPP
