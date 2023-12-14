// Copyright 2023 <paula.camachogonzalez@ucr.ac.cr>
#ifndef GOLDBACHANAURI_HPP
#define GOLDBACHANAURI_HPP

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
#include "GoldbachInfo.hpp"
#include "NumeroG.hpp"

/**
 * @class GoldbachAnaUri
 * @brief Clase para analizar y procesar solicitudes HTTP relacionadas 
 con la conjetura de Goldbach.
 *
 * Esta clase se encarga de analizar las URI de las solicitudes HTTP 
 * con la conjetura de Goldbach, separar valores de la URI y generar respuestas
 * en caso de solicitudes inválidas.
 */
class GoldbachAnaUri : public Assembler<reqRes_t, NumeroG>{
 public:
  /**
   * @brief Método principal para ejecutar el analizador de URI relacionado
    con la conjetura de Goldbach.
   * @return código de error 
   */
  int run() override;

  /**
   * @brief Método para consumir y procesar datos de solicitud y respuesta
    relacionados con la conjetura de Goldbach.
   * @param data Los datos de solicitud y respuesta a procesar.
   */
  void consume(reqRes_t data) override;

  /**
   * @brief Método para servir la página de inicio de la aplicación
    relacionada con la conjetura de Goldbach.
   * @param httpRequest La solicitud HTTP recibida.
   * @param httpResponse La respuesta HTTP a enviar.
   * @return la página de inicio con éxito
   */
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /**
   * @brief Método para analizar la URI de una solicitud relacionada con
    la conjetura de Goldbach y dirigirla.
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
   * @brief Método para crear el cuerpo de una respuesta HTTP para solicitudes 
   * inválidas relacionadas con la conjetura de Goldbach.
   * @param httpResponse La respuesta HTTP a generar.
   */
  void crearCuerpoInvalidRequest(HttpResponse& httpResponse);
};

#endif  // GOLDBACHANAURI_HPP
