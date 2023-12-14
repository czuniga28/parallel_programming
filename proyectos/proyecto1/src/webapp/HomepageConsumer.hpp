// Copyright 2023 <yeshua.ramirez@ucr.ac.cr>
#ifndef HOMEPAGE_HPP
#define HOMEPAGE_HPP

#include <vector>
#include <cassert>
#include <stdexcept>
#include <string>
#include <regex>

#include "Assembler.hpp"
#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"
#include "Socket.hpp"
#include "Structs.hpp"
#include "Queue.hpp"

#include "Util.hpp"
#include "FactInfo.hpp"
#include "NumeroF.hpp"

/**
 * @class HomepageConsumer
 * @brief Clase para consumir y procesar solicitudes y respuestas
 * relacionadas con la página de inicio para las webapp.
 */
class HomepageConsumer : public Assembler<reqRes_t, reqRes>{
 public:
  /**
   * @brief Método principal para ejecutar el consumidor de la página de inicio.
   * @return código de error
   */
  int run() override;

  /**
   * @brief Método para consumir y procesar solicitudes y respuestas
    relacionadas con la página de inicio.
   * @param data Los datos de solicitud y respuesta a procesar.
   */
  void consume(reqRes_t data) override;

  /**
   * @brief Método para consumir y servir la página de inicio de manera continua.
   */
  void consumeForever() override;

  /**
   * @brief Método para servir la página de inicio de una aplicación web.
   * @param httpRequest La solicitud HTTP recibida.
   * @param httpResponse La respuesta HTTP a enviar.
   * @return si la página de inicio se sirve con éxito.
   */
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);
};

#endif  // HOMEPAGE_HPP
