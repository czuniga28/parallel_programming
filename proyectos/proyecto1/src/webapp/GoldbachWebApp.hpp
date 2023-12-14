// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Modificaciones hechas en 2023  <juliana.martinezaguilar@ucr.ac.cr>
//  <paula.camachogonzalez@ucr.ac.cr>

#ifndef GOLDBACHTWEBAPP_HPP
#define GOLDBACHWEBAPP_HPP

#include <string>
#include <vector>

#include <tuple>

#include "HttpApp.hpp"
#include "GoldbachAnaUri.hpp"

#include "GoldbachInfo.hpp"
#include "ConjeturaGoldbach.hpp"

#include "Queue.hpp"

class GoldbachRequestCompleto;
class GoldbachHtml;

/**
@brief A web application that calculates goldbach conjecture
*/
class GoldbachWebApp : public HttpApp {
  /// Objects of this class cannot be copied
  DISABLE_COPY(GoldbachWebApp);

 private:
  /// @brief Despachador para las respuestas de HTML
  std::vector<GoldbachHtml*> dispatchers;
  /// @brief  Verificar si toda la solicitud fue completada
  std::vector<GoldbachRequestCompleto*> verificadores;
  /// @brief  colas de trabajo:
  Queue<NumeroG> colaDeNumeros;
  Queue<NumeroG> colaDeResultados;
  Queue<GoldbachInfo*> colaDeRequest;
  /// @brief  Analizador de URI
  GoldbachAnaUri* anaUri;
  /// @brief  Solver para la solicitud hecha
  std::vector<ConjeturaGoldbach*> solvers;

 public:
  /**
  * @brief Obtiene una instancia de la aplicación web de conjectura.
  * @return Referencia a la instancia de Goldbach.
  */
  static GoldbachWebApp& getInstance();
  /// Constructor
  GoldbachWebApp();
  /// Destructor
  ~GoldbachWebApp();
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

#endif  // GOLDBACHWEBAPP_HPP
