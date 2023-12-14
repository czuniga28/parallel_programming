// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#ifndef GOLDBAHCREQUESTCOMPLETO_HPP
#define GOLDBAHCREQUESTCOMPLETO_HPP

#include "Assembler.hpp"
#include "NumeroG.hpp"
#include "GoldbachInfo.hpp"

/**
 * @brief Clase que maneja solicitudes completas de Goldbach.
 *
 * Esta clase actúa como ensamblador (assembler) que consume objetos NumeroG,
 * verifica si han terminado y produce objetos tipo GoldbachInfo.
 */
class GoldbachRequestCompleto : public virtual Assembler<NumeroG,
  GoldbachInfo*> {
 public:
  /// @brief Constructor por defecto.
  GoldbachRequestCompleto();

  /**
   * @brief Ejecuta la clase como hilo (thread).
   * @return No retorna un valor específico.
   */
  int run() override;

 protected:
  /**
   * @brief Consume un objeto tipo NumeroG y produce un objeto GoldbachInfo si
   * se cumple la condición.
   * @param numeroG El objeto numero a consumir.
   */
  void consume(NumeroG numeroG) override;
};

#endif  // GOLDBAHCREQUESTCOMPLETO_HPP

