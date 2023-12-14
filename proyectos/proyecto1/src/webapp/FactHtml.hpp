// Copyright 2023 <paula.camachogonzalez@ucr.ac.cr>
#ifndef FACTHTML_HPP
#define FactHtml_HPP

#include "Consumer.hpp"
#include "FactInfo.hpp"

/**
 * @brief Clase que despacha solicitudes de FactInfo.
 *
 * Esta clase es un despachador que consume objetos FactInfo
 * e imprime sus resultados definitivos.
 */
class FactHtml : public virtual Consumer<FactInfo*> {
 public:
  /// @brief Constructor por defecto.
  FactHtml();

  /**
   * @brief Ejecuta el despachador de solicitudes.
   * @return Código de retorno de la ejecución.
   */
  int run() override;

 protected:
  /**
   * @brief Consume un objeto FactInfo e imprime sus resultados definitivos.
   * @param factInfo Puntero al objeto FactInfo a consumir.
   */
  void consume(FactInfo *factInfo) override;
};

#endif  // FACTHTML_HPP
