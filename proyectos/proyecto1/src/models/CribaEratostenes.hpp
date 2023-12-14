// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#ifndef CRIBAERATOSTENES_HPP
#define CRIBAERATOSTENES_HPP

#include <cstring>
#include <iostream>
#include <vector>
#include "common.hpp"

/**
 * @brief Proveedor de numeros primos usando
 * Criba de Eratostenes
*/
class CribaEratostenes {
  DISABLE_COPY(CribaEratostenes);

 private:
  /// numeros primos con los que trabajar
  std::vector<int64_t> numerosPrimos;

 public:
  /// @brief constructor, no hace mucho
  CribaEratostenes() : numerosPrimos() {}
  /// @brief destructor por defecto
  ~CribaEratostenes() = default;

 public:
  /// @brief con criba de Eratostenes, calcula los primos
  /// que hay por debajo de un n
  /// @param numMax para calcular primos debajos de numMax
  void calcularPrimos(int64_t numMax);

  /// @brief obtener primos calculados con criba
  /// @return vector de int64_ts con primos
  std::vector<int64_t> getNumerosPrimos();

  /// @brief Muestra por pantalla los numeros primos
  /// usado solo para depuracion en caso de errores,
  /// no para web
  void imprimirNumerosPrimos();
};

#endif  // CRIBAERATOSTENES_HPP
