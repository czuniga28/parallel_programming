// Copyright 2023 <yeshua.ramirez@ucr.ac.cr>, <paula.camachogonzalez@ucr.ac.cr>
// <juliana.martinezaguilar@ucr.ac.cr>, <christopher.zunigarojas@ucr.ac.cr>

#include <omp.h>
#include <cstdlib>
#include <iostream>
#include "simulacionCalor.hpp"

int main(int argc, char *argv[]) {
  // Verificar que se proporcionó el nombre de algun archivo como argumento
  if (argc != 3) {
    std::cerr << "Uso: " << argv[0] << " <nombre_del_archivo.txt>"
      << " cantidad_de_hilos" << std::endl;
    return 1;
  }
  // Obtener cantidad de hilos
  size_t cantidadHilos = strtoll(argv[2], nullptr, 10);

  std::vector<infoSimulacion> infoSimulaciones;
  // Abrir el archivo
  lecturaArchivoTrabajo(argv[1], infoSimulaciones);

  // se recorren los info para realizar las simulaciones
  #pragma omp parallel for schedule(dynamic) num_threads(cantidadHilos) \
    default(none) shared(infoSimulaciones)
  for (size_t simulacion = 0; simulacion < infoSimulaciones.size();
      simulacion++) {
    prepararSimulacion(infoSimulaciones[simulacion]);
  }
  escrituraArchivoReporte(infoSimulaciones);
  return 0;
}
