// Copyright 2023 <yeshua.ramirez@ucr.ac.cr>, <paula.camachogonzalez@ucr.ac.cr>
// <juliana.martinezaguilar@ucr.ac.cr>, <christopher.zunigarojas@ucr.ac.cr>
#include <mpi.h>
#include <inttypes.h>
#include <string>
#include <sstream>
#include <vector>


#ifndef SIMULADORCALOR_HPP
#define SIMULADORCALOR_HPP

/**
 * @brief Estructura que almacena la información relacionada 
 * a la simulación de calor.
 */
typedef struct infoSimulacion {
  /// Ruta del archivo de entrada.
  std::string ruta;
  /// Carpeta de destino para archivos de salida.
  std::string carpeta;
  /// Nombre del archivo binario resultante.
  std::string binario;
  /// Coeficiente de difusividad térmica.
  double difusividadTermica = 0;
  /// Número de filas en la placa de simulación.
  size_t filas = 0;
  /// Número de columnas en la placa de simulación.
  size_t columnas = 0;
  /// Dimensiones de la placa.
  double dimensiones = 0;
  /// Tiempo total de la simulación.
  double tiempo = 0;
  /// Valor de epsilon para determinar equilibrio térmico.
  double epsilon = 0;
  /// Estado actual de la simulación.
  size_t estado = 0;
  /// Matriz que representa la placa en el estado anterior.
  std::vector<std::vector<double>> placaPasada;
  /// Matriz que representa la placa en el estado futuro.
  std::vector<std::vector<double>> placaFutura;
} infoSimulacion_t;


/**
 * @brief Función que recibe estados de simulación de otros procesos MPI
 *
 * @param infoSimulaciones Referencia al vector para almacenar los
 * infoSimulacion
 * 
 * @return EXIT_SUCCESS si se recibieron los estados correctamente 
 */
int recibirEstados(std::vector<infoSimulacion>& infoSimulaciones);

/**
 * @brief Lee información de simulación del archivo y se crea un vector de
 * objetos infoSimulacion.
 *
 * @param rutaArchivo La ruta del archivo de donde se obtienen los datos
 * @param infoSimulaciones Referencia al vector para almacenar los
 * infoSimulacion
 * @return EXIT_SUCCESS si todo fue procesado correctamente y no hubo errores
 */
int lecturaArchivoTrabajo(const std::string rutaArchivo,
std::vector<infoSimulacion>& infoSimulaciones);

/**
 * @brief Lee una línea de un archivo de texto y se obtienen los datos del 
 objeto infoSimulacion
 *
 * @param infoSimulacion Referencia al objeto infoSimulacion_t
 * @param linea La línea que se leerá del archivo de texto
 * @return true si la línea se lee correctamente y el objeto infoSimulacion
 * obtiene todos los datos a procesar
 */
bool leerLineaTxt(infoSimulacion_t& infoSimulacion, const std::string& linea);

/**
 * @brief Lee información de placas y se almacena en el objeto infoSimulacion_t
 *
 * @param infoSimulacion Referencia al objeto infoSimulacion_t
 * @return EXIT_SUCCESS si el binario fue procesado correctamente y no hubo 
 * errores
 */
int lecturaPlaca(infoSimulacion_t& infoSimulacion);

/**
 * @brief Prepara la simulación para el objeto infoSimulacion
 *
 * @param infoSimulacion Referencia al objeto infoSimulacion_t 
 * @return EXIT_SUCCESS si la preparación no tuvo erroes
 */
int prepararSimulacion(infoSimulacion_t& infoSimulacion);

/**
 * @brief Inicia la simulación de calor para infoSimulacion
 *
 * @param infoSimulacion Referencia al objeto infoSimulacion_t
 * @return El estado k en el que se equilibró la temperatura
 */
int64_t empezarSimulacion(infoSimulacion_t& infoSimulacion);

/**
 * @brief Calcula el siguiente estado de una celda en la simulación
 * térmica de placas
 *
 * @param fila Índice de fila de la celda
 * @param columna Índice de columna de la celda
 * @param infoSimulacion Referencia al objeto infoSimulacion_t
 *
 */
void siguienteEstado(size_t fila, size_t columna, infoSimulacion_t&
infoSimulacion);

/**
 * @brief Verifica si la temperatura en la simulación está equilibrada
 *
 * @param infoSimulacion Referencia al objeto infoSimulacion 
 * @return true si la temperatura está equilibrada
 *
 * Si la diferencia es menor o igual al valor de epsilon, se 
 * considera que la temperatura está equilibrada
 */
bool temperaturaEquilibrada(infoSimulacion& infoSimulacion);

/**
 * @brief Ajusta la temperatura de las placas para igualarlas
 *
 * @param ultimaFila El índice de fila
 * @param ultimaColumna El índice de columna
 * @param infoSimulacion Referencia al objeto infoSimulacion q
 */
void igualarPlacas(size_t ultimaFila, size_t ultimaColumna, infoSimulacion&
infoSimulacion);

/**
 * @brief Se escribe el archivo binario con la información de la placa futura 
 * en la ruta de infoSimulacion
 *
 * @param infoSimulacion Referencia al objeto infoSimulacion_t 
 * @return EXIT_SUCCESS si se escribe correctamente
 *
 */
int escrituraPlaca(infoSimulacion_t& infoSimulacion);

/**
 * @brief Formatea el tiempo en formato "YYYY/MM/DD hh:mm:ss"
 *
 * @param seconds Tiempo en segundos
 * @return Cadena de caracteres formateada representando la fecha y hora
 */
std::string format_time(const time_t seconds);

/**
 * @brief Escribe la información de simulaciones en el output
 *
 * @param infoSimulaciones Vector que contiene objetos infoSimulacion_t 
 * @return EXIT_SUCCESS si todo fue escrito correctamente y no hubo errores
 */
int escrituraArchivoReporte(std::vector<infoSimulacion_t>& infoSimulaciones);

/**
 * @brief Determina el inicio del trabajo del hilo
 * @param rank Rango del trabajo
 * @param end Final del trabajo
 * @param workers Número de hilos
 * @param begin Punto de inicio del trabajo
 * @return Entero que representa el inicio del trabajo del hilo
 */
int calcular_inicio(int rank, int end, int workers, int begin);

/**
 * @brief Determina el punto final del trabajo del hilo
 * @param rank Rango del trabajo
 * @param end Final del trabajo
 * @param workers Número de hilos
 * @param begin Punto de inicio del trabajo
 * @return Entero que representa el punto final del trabajo del hilo
 */
int calcular_fin(int rank, int end, int workers, int begin);


#endif
