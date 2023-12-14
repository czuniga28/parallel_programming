// Copyright 2023 <yeashua.ramirez@ucr.ac.cr>
#ifndef FACTINFO_HPP
#define FACTINFO_HPP
#include <string>
#include <iostream>
#include <mutex>
#include <vector>
#include <tuple>
#include "NumeroF.hpp"

/**
 * @class FactInfo
 * @brief Clase para conocer los datos de solicitudes de factorizaciones.
 *
*/
class FactInfo {
  DISABLE_COPY(FactInfo);
  /// @brief Vector que almacena números para cálculos de factorización prima.
  std::vector<int64_t> numeros;
  /// @brief Total de factorizaciones calculadas.
  int64_t factorizacionesTotalCantidad = 0;
  /// @brief Número de trabajos realizados.
  int64_t trabajados = 0;
  /// @brief Respuesta HTTP relacionada con los cálculos de factorización prima.
  HttpResponse response;
  /// @brief Solicitud HTTP relacionada con los cálculos de factorización prima.
  HttpRequest request;
  /// @brief Vector que almacena cantidades de bases para las factorizaciones.
  std::vector<int64_t> basesCantidades;
  /// @brief Vector de vectores de tuplas que almacena las factorizaciones
  /// calculadas.
  std::vector<std::vector<std::tuple<int64_t, int64_t>>> factorizaciones;

 public:
/// @brief Constructor para trabajar casos
/// @param response response de Http
/// @param request request de Http
FactInfo(HttpResponse& response,
HttpRequest& request);
/// @brief Destructor por defecto
~FactInfo();
/// @brief Constructor para casos de parada
FactInfo();

 public:
    /// @brief Para insercion de factorizaciones
    /// @param factorizacion factorizacion a insertar
    /// @param posicionFact posicion de la factorizacion
    void setFactorizacion(std::vector<std::tuple<int64_t, int64_t>> fact,
     int64_t posicionFact);  //! puntero?
    int64_t getNumero(int64_t posicion);
    /// @brief Cantidad de sumas en el request
    /// @return cantidad de sumas
    int64_t getCantidadNumeros();
    /// @brief Comparador de FactInfos
    /// @param otroFactInfo objeto a comparar
    /// @return True iguales, false no son igules
    bool operator == (const FactInfo& otroFactInfo) const;

    /// @brief Agrega numeros para FactInfo
    /// @param numeros vector de numeros a agregar
    void setNumeros(std::vector<int64_t>& numeros);

    /// @brief Saber si se ha culminado el trabajo
    /// @param NumeroF consulta
    /// @return true si se ha terminado, false si no
    bool hemosTerminado(NumeroF& numeroF);

    /// @brief impresion de resultados finales
    void impresionResultadosDefinitivos();
    /// @brief auxiliar para impresion de resultados finales
    void impresionAuxiliar(std::string title,
      std::string body);
};

#endif  // FACTINFO_HPP
