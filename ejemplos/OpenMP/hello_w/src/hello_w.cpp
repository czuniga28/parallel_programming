// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0
#include <omp.h>

#include <iostream>

int main(int argc, char* argv[]) {
  // omp_get_max_threads devuelve el número de hilos que se pueden crear en un
  // sistema
  int cantidad_hilos = omp_get_max_threads();
  if (argc == 2) {
    cantidad_hilos = atoi(argv[1]);
  }
  // Directiva del preprocesador que indica al hilo principal que cree
  // cantidad_hilos hilos con la función num_threads(cantidad_hilos).
  #pragma omp parallel num_threads(cantidad_hilos)
  {
    #pragma omp critical(stdout)
    // omp_get_thread_num devuelve el id del hilo que está ejecutando el
    // omp_get_num_threads devuelve el número de hilos que están ejecutando
    std::cout << "Hola desde el hilo secundario " << omp_get_thread_num()
      << " de " << omp_get_num_threads() << std::endl;
  }
}