// Copyright 2023 <yeashua.ramirez@ucr.ac.cr>
#ifndef CONJETURAGOLDBACH_HPP
#define CONJETURAGOLDBACH_HPP

#include <vector>
#include <iostream>
#include "Assembler.hpp"
#include "NumeroG.hpp"
#include "common.hpp"
#include "CribaEratostenes.hpp"

/// @brief Se encarga de crear objetos
/// que responden a la conjetura de Goldbach
/// a partir de un vector de int64_ts
class ConjeturaGoldbach :
public virtual Assembler<NumeroG, NumeroG> {
  // desabilitacion de 4 de 5, regla de los 5, ver en common
  DISABLE_COPY(ConjeturaGoldbach);

 private:
  /// @brief cada subindice tiene un numero al que
  /// se le desea aplicar la conjetura
  std::vector<int64_t> sumas;
  /// @brief cada vector de vectores tiene el resultado el o los
  /// resultados en un vector para el numero buscado
  std::vector<std::vector<std::vector<int64_t>>> sumandos;
  /// @brief Contador de sumas encontradas
  int64_t sumasEncontradas = 0;

 public:
  /// @brief Constructor por defecto
  ConjeturaGoldbach() = default;

  /// @brief Destructor por defecto
  ~ConjeturaGoldbach() = default;

 public:
  /// @brief subrutina que hace los calculos correspondientes a
  /// a la conjetura
  /// @param suma numero a trabajar
  /// @param sumas numeros que se quieren trabajar con la conjetura
  void trabajarConjeturaGoldbach(std::vector<int64_t> sumas);

  /// @brief trabaja conjetura para impares
  /// @return vector de vectores de vectores soluciones posibles
  std::vector<std::vector<int64_t>> sumaPrimosImpares(int64_t suma);

  /// @brief trabaja conjetura para pares
  /// @param suma numero a trabajar
  /// @return vector de vectores de vectores con soluciones posibles
  std::vector<std::vector<int64_t>> sumaPrimosPares(int64_t suma);

  /// @brief Conseguir los resultados
  /// @return vector de vectores de vectores, el segundo vector mas profundo
  /// tiene vectores en los que, en cada uno, estan los sumandos de cada
  /// numero (aveces puede ser mas de una suma, por eso la estructura
  /// elegida)
  inline std::vector<std::vector<std::vector<int64_t>>> getSumandos() {
    return this->sumandos;
  }

  /// @brief solicitud de numeros calculados, no respuestas
  /// @return numeros calculados
  inline std::vector<int64_t> getSumas() {
    return this->sumas;
  }

  /// @brief Impresion de resultados, no se usa en web, solo en debugging
  /// @warning Solo usar en debugging, NO para web
  void imprimirConjeturaGoldbach();

  /// @brief imprime vectores de la conjetura independientemente
  /// @param sumaPrimos vector a imprimir
  /// @param imprimir saber si el usuario quiere o no ver las sumas
  void ImprimirSumaPrimos(std::vector<std::vector<int64_t>> sumaPrimos,
    bool imprimir);

  /// @brief Acceder a sumas encontradas con Goldbach
  /// @return total de sumas encontradas
  int64_t getSumasEncontradas();

  int run() override;
  void consume(NumeroG numeroG) override;
};

#endif  // CONJETURAGOLDBACH_HPP
