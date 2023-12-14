// Copyright Modificaciones Taller 2023 <paula.camachogonzalez@ucr.ac.cr>
#ifndef STRUCTS_HPP
#define STRUCTS_HPP
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Socket.hpp"

/**
 * @struct reqRes
 * @brief Estructura que representa HttpRequest y HttpResponse.
 *
 */
typedef struct reqRes {
  /// @brief HttpRequest
  HttpRequest httpRequest;
  /// @brief HttpResponse
  HttpResponse httpResponse;

  public:
  /**
   * @brief Constructor de la estructura reqRes.
   * @param request Objeto HttpRequest para la solicitud
   * @param response Objeto HttpResponse para la respuesta
   */
  reqRes(HttpRequest request = HttpRequest(Socket())
  , HttpResponse response = HttpResponse(Socket()))
  : httpRequest(request)
  , httpResponse(response) {}

   /**
   * @brief Operador de igualdad.
   * @param other La otra estructura reqRes a comparar.
   * @return Verdadero si son iguales, falso en caso contrario.
   */
  inline bool operator==(const reqRes & other) const {
    return this->httpRequest == other.httpRequest
     && this->httpResponse == other.httpResponse;
  }
} reqRes_t;

#endif
