// Copyright 2023 <yeshua.ramirez@ucr.ac.cr>, <paula.camachogonzalez@ucr.ac.cr>
// <juliana.martinezaguilar@ucr.ac.cr>, <christopher.zunigarojas@ucr.ac.cr>

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "simulacionCalor.hpp"

// Función de la página de Jeisson
std::string format_time(const time_t seconds) {
  char text[48];  // YYYY/MM/DD hh:mm:ss
  const std::tm& gmt = * std::gmtime(&seconds);
  snprintf(text, sizeof text, "%04d/%02d/%02d\t%02d:%02d:%02d", gmt.tm_year
    - 70, gmt.tm_mon, gmt.tm_mday - 1, gmt.tm_hour, gmt.tm_min, gmt.tm_sec);
  return text;
}

int escrituraArchivoReporte(std::vector<infoSimulacion_t>& infoSimulaciones) {
  // Concatenar la ruta de la carpeta con el nombre del archivo
  std::string rutaCompleta = infoSimulaciones[0].carpeta + "/output.txt";
  std::ofstream archivoInfo(rutaCompleta, std::ios::trunc);

  // Verificar si archivo se abrió
  if (!archivoInfo) {
    std::cerr << "Error con el archivo de salida" << std::endl;
    return EXIT_FAILURE;
  }

  for (size_t simulacion; simulacion < infoSimulaciones.size(); simulacion++) {
    double totalTiempo = infoSimulaciones[simulacion].estado *
      infoSimulaciones[simulacion].tiempo;
    // Se agregan los datos al archivo output
    archivoInfo << infoSimulaciones[simulacion].binario << "\t";
    archivoInfo << infoSimulaciones[simulacion].tiempo << "\t";
    archivoInfo << infoSimulaciones[simulacion].difusividadTermica << "\t";
    archivoInfo << infoSimulaciones[simulacion].dimensiones << "\t";
    archivoInfo << infoSimulaciones[simulacion].epsilon << "\t";
    archivoInfo << infoSimulaciones[simulacion].estado << "\t";

    // Formatear el tiempo transcurrido
    archivoInfo << format_time(static_cast<time_t>(totalTiempo)) << std::endl;
  }

  // Cerrar archivo
  archivoInfo.close();

  std::cout << "Se ha generado el ouput en la carpeta:" <<
    infoSimulaciones[0].carpeta << std::endl;

  return EXIT_SUCCESS;
}

int lecturaArchivoTrabajo(std::string rutaArchivo, std::vector<infoSimulacion>&
    infoSimulaciones) {
  std::ifstream archivo(rutaArchivo);

  // Verificar si se abrio el archivo correctamente
  if (!archivo) {
      std::cerr << "Error al abrir el archivo." << std::endl;
      return EXIT_FAILURE;
  }

  // Continuar sacando información hasta que se lean todas las líneas
  size_t barra = rutaArchivo.rfind("/");
  std::string linea;
  while (std::getline(archivo, linea)) {
    infoSimulacion_t info;
    info.carpeta = rutaArchivo.substr(0, barra + 1);
    // Almacenar información de la simulación en un vector de infoSimulacion
    if (leerLineaTxt(info, linea)) {
      infoSimulaciones.push_back(info);
    }
  }

  return EXIT_SUCCESS;
}

bool leerLineaTxt(infoSimulacion_t &infoSimulacion, const std::string &linea) {
  std::istringstream ss(linea);  // Trata un string como si fuera un cin
  std::vector<std::string> campos;

  // Dividir la línea en campos
  std::string campo;
  while (ss >> campo) {  // Extrae de ss hacia campo como si se leyera de la std
    campos.push_back(campo);
  }

  // Verificar que haya exactamente 5 campos en la linea del txt
  if (campos.size() != 5) {
      std::cerr << "Error: La línea no tiene 5 campos." << std::endl;
      return false;
  }

  // Asignar valores a los miembros del struct
  infoSimulacion.ruta = infoSimulacion.carpeta + campos[0];
  infoSimulacion.binario = campos[0];
  infoSimulacion.tiempo = std::stod(campos[1]);
  infoSimulacion.difusividadTermica = std::stod(campos[2]);
  infoSimulacion.dimensiones = std::stod(campos[3]);
  infoSimulacion.epsilon = std::stod(campos[4]);

  return true;
}

void siguienteEstado(size_t fila, size_t columna,
    infoSimulacion_t& infoSimulacion) {
  double sumaCeldasVecinas = infoSimulacion.placaPasada[fila-1][columna] +
    infoSimulacion.placaPasada[fila][columna+1] +
    infoSimulacion.placaPasada[fila+1][columna] +
    infoSimulacion.placaPasada[fila][columna-1];
  // Calcular la energía perdida por la celda
  double energiaPerdida = 4 * infoSimulacion.placaPasada[fila][columna];
  // Calcular factor de la simulación
  double factor = static_cast<double>((infoSimulacion.tiempo *
    infoSimulacion.difusividadTermica)) /
    static_cast<double>(infoSimulacion.dimensiones*infoSimulacion.dimensiones);
  // infoSimulacion.estado = infoSimulacion.estado - 1;
  double siguienteTemp = infoSimulacion.placaPasada[fila][columna] + factor *
    (sumaCeldasVecinas - energiaPerdida);
  // Almacenar información en placaFutura
  infoSimulacion.placaFutura[fila][columna] = siguienteTemp;
}

int lecturaPlaca(infoSimulacion_t& infoSimulacion) {
  // Obtener la ruta del archivo desde la información de la simulación
  std::string ruta = infoSimulacion.ruta;
  // Abrir el archivo binario para lectura
  std::ifstream file(ruta, std::ios::binary);

  // Verificar si el archivo se abrió correctamente
  if (!file) {
    std::cerr << "Error: No se pudo leer placa " << ruta << std::endl;
    return EXIT_FAILURE;
  }
  // Leer el tamaño de la matriz desde el archivo
  file.read(reinterpret_cast<char*>(&infoSimulacion.filas), sizeof(size_t));
  file.read(reinterpret_cast<char*>(&infoSimulacion.columnas), sizeof(size_t));

  // Crear una matriz temporal dinámica para almacenar los valores leídos
  std::vector<std::vector<double>>* matrizDePaso1 =
    new std::vector<std::vector<double>>;

  // Referencia para facilitar el uso de la matriz temporal
  std::vector<std::vector<double>>&  matrizDePaso2 = *matrizDePaso1;
  // Redimensionar la matriz temporal según las dimensiones leídas
  matrizDePaso1->resize(infoSimulacion.filas);

  // Leer los valores de la matriz desde el archivo
  for (size_t f = 0; f < infoSimulacion.filas; ++f) {
    matrizDePaso2[f].resize(infoSimulacion.columnas);
    for (size_t c = 0; c < infoSimulacion.columnas; ++c) {
      file.read(reinterpret_cast<char*>
          (&(matrizDePaso2[f][c])), sizeof(double));
    }
  }

  file.close();

  // Crear placa actual y placa auxiliar necesarias para la simulacion
  infoSimulacion.placaFutura.resize(infoSimulacion.filas,
    std::vector<double>(infoSimulacion.columnas));
  infoSimulacion.placaPasada.resize(infoSimulacion.filas,
    std::vector<double>(infoSimulacion.columnas));

  // Transferir los valores de la matriz temporal a de la simulación
  for (size_t f = 0; f < infoSimulacion.filas; ++f) {
    for (size_t c = 0; c < infoSimulacion.columnas; ++c) {
      infoSimulacion.placaFutura[f][c] = matrizDePaso2[f][c];
      infoSimulacion.placaPasada[f][c] = matrizDePaso2[f][c];
    }
  }
  delete matrizDePaso1;

  return EXIT_SUCCESS;
}

int escrituraPlaca(infoSimulacion_t& infoSimulacion) {
  // Obtener la ruta del archivo
  std::string ruta = infoSimulacion.ruta.substr(0,
    infoSimulacion.ruta.length() - 4);
  ruta += "-" + std::to_string(infoSimulacion.estado) + ".bin";
  // Abrir el archivo binario para escritura
  std::ofstream file(ruta, std::ios::binary);

  if (!file) {
    std::cerr << "Error: No se pudo crear archivo para la placa " << ruta
      << std::endl;
    return EXIT_FAILURE;
  }
  // Escribir el tamaño de la matriz en el archivo
  file.write(reinterpret_cast<char*>(&infoSimulacion.filas), sizeof(size_t));
  file.write(reinterpret_cast<char*>(&infoSimulacion.columnas),
    sizeof(size_t));

  for (size_t f = 0; f < infoSimulacion.filas; f++) {
    for (size_t c = 0; c < infoSimulacion.columnas; c++) {
      // Escribir en el archivo el valor [f][c] de la placa
      file.write(reinterpret_cast<char*>(&infoSimulacion.placaFutura[f][c]),
        sizeof(double));
    }
  }
  // Cerrar archivo
  file.close();

  return EXIT_SUCCESS;
}

int prepararSimulacion(infoSimulacion_t& infoSimulacion) {
  // Inicializar las dimensiones de la placa y las matrices de la simulación
  infoSimulacion.filas = 0;
  infoSimulacion.columnas = 0;
  infoSimulacion.placaFutura.resize(infoSimulacion.filas,
    std::vector<double>(infoSimulacion.columnas));
  infoSimulacion.placaPasada.resize(infoSimulacion.columnas,
    std::vector<double>(infoSimulacion.columnas));

  // Leer placa de entrada
  if (!(lecturaPlaca(infoSimulacion) == EXIT_SUCCESS)) {
    std::cerr << "Error en archivo binario" <<std::endl;
  }

  // Empezar simulación de calor
  infoSimulacion.estado = empezarSimulacion(infoSimulacion);

  // Escribir en archivo placa con valores obtenidos
  escrituraPlaca(infoSimulacion);

  return EXIT_SUCCESS;
}

int64_t empezarSimulacion(infoSimulacion_t& infoSimulacion) {
  while (true) {
    infoSimulacion.estado++;
    // Pasar celdas de la placa al siguiente estado
    for (size_t indexI = 1; indexI <= infoSimulacion.filas-2; indexI++) {
      for (size_t indexJ = 1; indexJ <= infoSimulacion.columnas-2; indexJ++) {
        siguienteEstado(indexI, indexJ, infoSimulacion);
      }
    }
    // Verificar si la tempertatua esta equilibrada
    if (temperaturaEquilibrada(infoSimulacion) == true) {
      // retorna el estado k en el que se equilibro la temperatura
      return infoSimulacion.estado;
    }

    // Almacenar valores de la placa creada en la placa actual si no se ha
    // equilibrado
    igualarPlacas(infoSimulacion.filas-1, infoSimulacion.columnas-1,
      infoSimulacion);
  }
  return 0;
}

void igualarPlacas(size_t ultimaFila, size_t ultimaColumna,
    infoSimulacion& infoSimulacion) {
  for (size_t i = 0; i < ultimaFila; i++) {
    for (size_t j = 0; j < ultimaColumna; j++) {
      // Celda de placa pasada pasa a ser igual a celda de placa futura
      infoSimulacion.placaPasada[i][j] = infoSimulacion.placaFutura[i][j];
    }
  }
}

bool temperaturaEquilibrada(infoSimulacion& infoSimulacion) {
  for (size_t indexI = 1; indexI <= infoSimulacion.filas-2; indexI++) {
    for (size_t indexJ = 1; indexJ <= infoSimulacion.columnas-2; indexJ++) {
      // Diferencia entre placa anterior y futura es mayor a epsilon la placa
      // no esta equilibrada
      if (std::abs(infoSimulacion.placaFutura[indexI][indexJ] -
        infoSimulacion.placaPasada[indexI][indexJ]) > infoSimulacion.epsilon) {
          return false;
      }
    }
  }
  return true;
}
