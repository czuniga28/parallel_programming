// Copyright 2023 <yeshua.ramirez@ucr.ac.cr>, <paula.camachogonzalez@ucr.ac.cr>
// <juliana.martinezaguilar@ucr.ac.cr>, <christopher.zunigarojas@ucr.ac.cr>

#include <iostream>

#include "simulacionCalor.hpp"

int main(int argc, char *argv[]) {
  // Verificar que se proporcionó el nombre de algun archivo como argumento
  if (argc != 2) {
    std::cerr << "Uso: " << argv[0] << " <nombre_del_archivo.txt>" << std::endl;
    return 1;
  }
  std::vector<infoSimulacion> infoSimulaciones;
  // Abrir el archivo
  lecturaArchivoTrabajo(argv[1], infoSimulaciones);
  // se recorren los info para realizar las simulaciones
  for (auto& info : infoSimulaciones) {
    if (prepararSimulacion(info) == EXIT_SUCCESS) {
    } else {
      std::cerr << "Error en la simulacion" << std::endl;
    }
  }
  escrituraArchivoReporte(infoSimulaciones);
  return 0;
}
