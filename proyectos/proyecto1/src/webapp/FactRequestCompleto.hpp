// Copyright 2023 <paula.camachogonzalez@ucr.ac.cr>
#ifndef FACTREQUESTCOMPLETO_HPP
#define FACTREQUESTCOMPLETO_HPP

#include "Assembler.hpp"
#include "NumeroF.hpp"

/**
 * @brief Clase que maneja solicitudes completas de factorización.
 *
 * Esta clase actúa como un ensamblador (assembler) que consume objetos NumeroF,
 * verifica si han terminado y produce objetos FactInfo.
 */
class FactRequestCompleto : public virtual Assembler<NumeroF, FactInfo*> {
 public:
  /// @brief Constructor por defecto.
  FactRequestCompleto();

  /**
   * @brief Ejecuta la clase como un hilo (thread).
   * @return No retorna un valor específico.
   */
  int run() override;

 protected:
  /**
   * @brief Consume un objeto NumeroF y produce un objeto FactInfo
   * @param numeroF El objeto NumeroF (factorial) a consumir.
   */
  void consume(NumeroF numeroF) override;
};

#endif  // FACTREQUESTCOMPLETO_HPP

