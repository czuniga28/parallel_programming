// Copyright 2023 <yeshua.ramirez@ucr.ac.cr>, <paula.camachogonzalez@ucr.ac.cr>
// <juliana.martinezaguilar@ucr.ac.cr>, <christopher.zunigarojas@ucr.ac.cr>

#include <mpi.h>
#include <omp.h>
#include <cstdlib>
#include <thread>
#include <iostream>
#include "simulacionCalor.hpp"


/**
 * @brief Función principal del programa
 *
 * @param argc Número de argumentos 
 * @param argv Vector de argumentos 
 *
 * @return  EXIT_SUCCESS si el programa se ejecuta correctamente
 */
int main(int argc, char *argv[]) {
  // Verificar que se proporcionó el nombre de archivo
  if (argc < 2) {
    std::cerr << "Uso: " << argv[0] << " <nombre_del_archivo.txt>" << std::endl;
    return EXIT_FAILURE;
  }

  // Obtener cantidad de hilos
  size_t cantidadHilos;

  if (argc >= 3) {
    cantidadHilos = strtoll(argv[2], nullptr, 10);
  } else {
    cantidadHilos = std::thread::hardware_concurrency();
  }

  // Inicializar MPI
  if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
    std::cerr << "Error: No se pudo inicializar los procesos MPI" << std::endl;
    return EXIT_FAILURE;
  }

  // Vector que almacena la información de las simulaciones
  std::vector<infoSimulacion> infoSimulaciones;

  // Abrir el archivo y cargar la información de las simulaciones
  lecturaArchivoTrabajo(argv[1], infoSimulaciones);

  // Obtener información MPI
  int inicio = 0;
  int fin = infoSimulaciones.size();
  int process_count = -1;
  MPI_Comm_size(MPI_COMM_WORLD, &process_count);
  int process_number = -1;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_number);
  int inicio_index = calcular_inicio(process_number, fin, process_count,
  inicio);
  int fin_index = calcular_fin(process_number, fin, process_count, inicio);

  // Realizar simulaciones usando OpenMP
  #pragma omp parallel for schedule(dynamic) num_threads(cantidadHilos) \
    default(none) shared(infoSimulaciones, inicio_index, fin_index)
  for (int simulacion_index = inicio_index; simulacion_index <
  fin_index; simulacion_index++) {
    // Preparar la simulación
    prepararSimulacion(infoSimulaciones[simulacion_index]);
  }

  // Manejar resultados dependiendo del proceso MPI
  int error = EXIT_SUCCESS;
  if (process_number == 0) {
    // Proceso rank 0 recibe estados y escribe el reporte
    if (recibirEstados(infoSimulaciones) == EXIT_FAILURE) {
      error = EXIT_FAILURE;
    }

    escrituraArchivoReporte(infoSimulaciones);
  } else {
    // Otros procesos envían estados al 0
    for (int simulacion_index = inicio_index; simulacion_index <
    fin_index; ++simulacion_index) {
      if (MPI_Send(&infoSimulaciones[simulacion_index].estado, 1,
      MPI_INT64_T, 0, 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
        std::cerr << "Error: No se pudo enviar el recuento de estados"
        << std::endl;
        error = EXIT_FAILURE;
      }
    }
  }

  // Sincronizar todos los procesos MPI
  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Finalize();

  return error;
}
