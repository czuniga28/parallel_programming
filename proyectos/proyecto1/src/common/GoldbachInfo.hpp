// Copyright 2023 <yeashua.ramirez@ucr.ac.cr>
#ifndef GoldbachInfo_HPP
#define GoldbachInfo_HPP
#include <iostream>
#include <string>
#include <vector>
#include "NumeroG.hpp"


/**
 * @class GoldbachInfo
 * @brief Clase para conocer los datos de solicitudes de conjetura.
 *
*/
class GoldbachInfo {
  DISABLE_COPY(GoldbachInfo);

  /// @brief Vector que almacena números para cálculos de Goldbach.
  std::vector<int64_t> numeros;

  /// @brief Total de sumas calculadas.
  int64_t sumasTotalCantidad = 0;

  /// @brief Número de trabajos realizados.
  int64_t trabajados = 0;

  /// @brief Respuesta HTTP relacionada con los cálculos de Goldbach.
  HttpResponse response;

  /// @brief Solicitud HTTP relacionada con los cálculos de Goldbach.
  HttpRequest request;

  /// @brief Vector de vectores de vectores que almacena sumas calculadas.
  std::vector<std::vector<std::vector<int64_t>>> sumas;

  /// @brief Vector que almacena cantidades de sumas.
  std::vector<int64_t> sumasCantidades;

 public:
  /// @brief Constructor para trabajar casos
  /// @param response response de Http
  /// @param request request de Http
  GoldbachInfo(HttpResponse& response,
  HttpRequest& request);

  /// @brief Destructor por defecto
  ~GoldbachInfo();

  /// @brief Constructor para casos de parada
  GoldbachInfo();

 public:
  /// @brief Para insercion de sumas
  /// @param suma suma a insertar
  /// @param posicionSuma posicion de la suma
  void setSuma(std::vector<std::vector<int64_t>> suma, int64_t posicionSuma);
  //! puntero?

  int64_t getNumero(int64_t posicion);

  /// @brief Cantidad de sumas en el request
  /// @return cantidad de sumas
  int64_t getCantidadNumeros();

  /// @brief Comparador de GoldbachInfos
  /// @param otroGoldbachInfo objeto a comparar
  /// @return True iguales, false no son igules
  bool operator == (const GoldbachInfo& otroGoldbachInfo) const;

  /// @brief Agrega numeros para GoldbachInfo
  /// @param numeros vector de numeros a agregar
  void setNumeros(std::vector<int64_t>& numeros);

  /// @brief Saber si se ha culminado el trabajo
  /// @param NumeroG consulta
  /// @return true si se ha terminado, false si no
  bool hemosTerminado(NumeroG& NumeroG);

  /// @brief impresion de resultados finales
  void impresionResultadosDefinitivos();
  /// @brief auxiliar para impresion de resultados finales
  void impresionAuxiliar(std::string title,
    std::string body);
};

#endif  // GoldbachInfo_HPP
