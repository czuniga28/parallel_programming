// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Modificaciones hechas en 2023 <juliana.martinezaguilar@ucr.ac.cr>
//  <yeshua.ramirez@ucr.ac.cr>
#ifndef FACTWEBAPP_HPP
#define FACTWEBAPP_HPP

#include <string>
#include <tuple>
#include <vector>

#include "HttpApp.hpp"
#include "FactAnaUri.hpp"

#include "FactInfo.hpp"
#include "FactorizacionPrima.hpp"

#include "Queue.hpp"

class FactRequestCompleto;
class FactHtml;

/**
@brief A web application that calculates prime factors
*/
class FactWebApp : public HttpApp {
  /// Objects of this class cannot be copied
  DISABLE_COPY(FactWebApp);

 private:
  /// @brief Despachador para las respuestas de HTML
  std::vector<FactHtml*> dispatchers;
  /// @brief  Verificar si toda la solicitud fue completada
  std::vector<FactRequestCompleto*> verificadores;
  /// @brief  colas de trabajo:
  Queue<NumeroF> colaDeNumeros;
  Queue<NumeroF> colaDeResultados;
  Queue<FactInfo*> colaDeRequest;
  /// @brief  Analizador de URI
  FactAnaUri* anaUri;
  /// @brief  Solver para la solicitud hecha
  std::vector<FactorizacionPrima*> solvers;

 public:
  /**
  * @brief Obtiene una instancia de la aplicación web de factorización.
  * @return Referencia a la instancia de FactWebApp.
  */
  static FactWebApp& getInstance();

  /// Constructor
  FactWebApp();
  /// Destructor
  ~FactWebApp();
  /// Called by the web server when the web server is started
  void start() override;
  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  /// @return true If this application handled the request, false otherwise
  /// and another chained application should handle it
  bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) override;
  /// Called when the web server stops, in order to allow the web application
  /// clean up and finish as well
  void stop() override;

 protected:
  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  /// @return true If this application handled the request, false otherwise
  /// Sends the homepage as HTTP response
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);
};

#endif  // FACTWEBAPP_HPP

