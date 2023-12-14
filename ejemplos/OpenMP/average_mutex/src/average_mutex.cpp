// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0
#include <omp.h>
#include <omp.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
  int thread_count = omp_get_max_threads();
  if (argc >= 2) {
    thread_count = atoi(argv[1]);
  }

  std::vector<double> values;

  double value = 0.0;
  // para paralelizar esta operación de lectura, necesitamos usar archivos de
  // acceso aleatorio y no un archivo de acceso secuencial. de esta manera,
  // podemos hacer que varios hilos lean desde diferentes posiciones del archivo.
  while (std::cin >> value) {
    values.push_back(value);
  }

  double sum = 0.0;

  #pragma omp parallel for num_threads(thread_count) schedule(runtime) \
    default(none) shared(values, sum)
  for (size_t index = 0; index < values.size(); ++index) {
    #pragma omp critical(can_add) // aquí estamos utilizando una sección crítica
    // esta es una mutex que se utiliza para asegurarse de que solo un hilo
    // pueda acceder a la sección crítica a la vez. Esto verifica que la
    // variable sum no esté siendo accedida por más de un hilo a la vez.
    sum += values[index];
  }

  const double average = values.size() ? sum / values.size() : 0.0;
  std::cout << average << std::endl;
}