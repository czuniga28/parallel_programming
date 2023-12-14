// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Modificaciones hechas en 2023 <juliana.martinezaguilar@ucr.ac.cr>

#ifndef HOMEPAGEWEBAPP_HPP
#define HOMEPAGEWEBAPP_HPP

#include "HomepageConsumer.hpp"
#include "HttpApp.hpp"

/**
@brief A web application for home page
*/
class HomeWebApp : public HttpApp {
  /// Objects of this class cannot be copied
  DISABLE_COPY(HomeWebApp);

 public:
  /// Constructor
  HomeWebApp();
  /// Destructor
  ~HomeWebApp();

  /**
  * @brief Obtiene una instancia de la aplicación web de home.
  * @return Referencia a la instancia de homewebapp.
  */
  static HomeWebApp& getInstance();
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
  /// @brief Pointer to a HomepageConsumer for handling related HTTP requests.
  HomepageConsumer* homeConsumer;

 protected:
  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  /// @return true If this application handled the request, false otherwise
  /// Sends the homepage as HTTP response
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);
};

#endif  // FACTWEBAPP_HPP
