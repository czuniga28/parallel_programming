// Copyright 2023 <yeshua.ramirez@ucr.ac.cr>
#ifndef FACTANAURI_HPP
#define FACTANAURI_HPP

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
 * @class FactAnaUri
 * @brief Clase para analizar y procesar solicitudes HTTP mediante el URI.
 *
 * Esta clase se encarga de analizar las URI de las solicitudes HTTP, de
 * separar valores de una URI y mostrar html en caso
 * de solicitudes inválidas.
 */
class FactAnaUri : public Assembler<reqRes_t, NumeroF>{
 public:
  /**
   * @brief Método principal para ejecutar el analizador de URI.
   * @return código de error si se produce una excepción.
   */
  int run() override;

  /**
   * @brief Método para consumir y procesar datos de solicitud y respuesta.
   * @param data Los datos de solicitud y respuesta a procesar.
   */
  void consume(reqRes_t data) override;

  /**
   * @brief Método para servir la página de inicio de la aplicación.
   * @param httpRequest La solicitud HTTP recibida.
   * @param httpResponse La respuesta HTTP a enviar.
   * @return la página de inicio con éxito
   */
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /**
   * @brief Método para analizar la URI de una solicitud y dirigirla.
   * @param httpRequest La solicitud HTTP recibida.
   * @param httpResponse La respuesta HTTP a enviar.
   */
  void analizarUri(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /**
   * @brief Método para separar valores de una URL y almacenarlos en un vector.
   * @param strValores La cadena que contiene los valores de la URL.
   * @param valores Un vector donde se almacenan los valores separados.
   */
  void separarValoresURL(std::string strValores, std::vector<int64_t>* valores);

  /**
   * @brief Método para crear el cuerpo de una respuesta HTTP para inválidas.
   * @param httpResponse La respuesta HTTP a generar.
   */
  void crearCuerpoInvalidRequest(HttpResponse& httpResponse);
};


#endif  // FACTANAURI_HPP
