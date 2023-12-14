// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#ifndef GOLDBACHHTML_HPP
#define GOLDBACHHTML_HPP

#include "Consumer.hpp"
#include "GoldbachInfo.hpp"

/**
 * @brief Clase que despacha solicitudes de GoldbachInfo.
 *
 * Esta clase es un dispatcher que consume objetos GoldbachInfo
 * e imprime sus resultados definitivos.
 */
class GoldbachHtml : public virtual Consumer<GoldbachInfo*> {
 public:
  /// @brief Constructor por defecto.
  GoldbachHtml();

  /**
   * @brief Ejecuta el dispatcher de solicitudes.
   * @return Código de retorno de la ejecución.
   */
  int run() override;

 protected:
  /**
   * @brief Consume un objeto (GoldbachInfo) e imprime sus resultados
   * definitivos.
   * @param goldbachInfo Puntero al objeto a consumir.
   */
  void consume(GoldbachInfo *goldbachInfo) override;
};

#endif  // GOLDBACHHTML_HPP

