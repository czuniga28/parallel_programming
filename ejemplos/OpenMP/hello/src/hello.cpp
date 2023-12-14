// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0
#include <iostream>

int main() {
  // Directiva del preprocesador que indica al hilo principal que cree n hilos
  // para ejecutar el siguiente código.
  // n es el número de hilos que se pueden crear en el sistema que ejecuta
  // el programa.
  #pragma omp parallel
  {
    // omp critical es como un mutex
    #pragma omp critical
    std::cout << "Hola desde el hilo secundario" << std::endl;
  }  // Después del bloque paralelo, el hilo principal se unirá a los otros hilos
}