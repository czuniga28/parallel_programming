// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0
#include <omp.h>
#include <iostream>

int main(int argc, char* argv[]) {
  // Obtenemos el número máximo de hilos disponibles
  int cantidad_hilos = omp_get_max_threads();
  if (argc >= 2) {
    cantidad_hilos = atoi(argv[1]);
  }

  int cantidad_iteraciones = cantidad_hilos;
  if (argc >= 3) {
    cantidad_iteraciones = atoi(argv[2]);
  }
  // Realizamos un bucle paralelo con la cantidad de hilos.
  // Este bucle comparte la variable iteration_count entre los hilos
  // y std::cout es una sección crítica.
  // La palabra clave aquí es for, esto es un bucle paralelo for
  #pragma omp parallel for num_threads(cantidad_hilos) \
    default(none) shared(cantidad_iteraciones, std::cout)
    // Otra palabra clave aquí es default(none), esto significa que omp no
    // asumirá que alguna variable es compartida o privada a menos que lo
    // especifiquemos.
    // Aquí usamos la palabra clave shared para especificar que las variables
    // cantidad_iteraciones y std::cout son compartidas entre los hilos.
    // La palabra clave private se usa para especificar que una variable es
    // privada para cada hilo. Aquí no la usamos porque no tenemos ninguna
    // variable privada.
  for (int iteracion = 0; iteracion < cantidad_iteraciones; ++iteracion) {
    #pragma omp critical(stdout)
    std::cout << omp_get_thread_num() << '/' << omp_get_num_threads()
      << ": iteración " << iteracion << '/' << cantidad_iteraciones << std::endl;
  }
  // El bucle for paralelo tiene varias restricciones:
  // 1. El bucle debe ser un bucle for simple, un bucle contador
  // Esto se debe a que el bucle se divide en fragmentos y cada hilo ejecuta
  // un fragmento del bucle, es una distribución estática por bloques.
}
