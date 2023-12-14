// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0
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
  while (std::cin >> value) {
    values.push_back(value);
  }

  double total_sum = 0.0;
  // realizamos una región paralela
  #pragma omp parallel num_threads(cantidad_hilos) \
    default(none) shared(values, total_sum)
  {
    // cada hilo tendrá su propia variable de suma parcial
    // esta variable se almacenará en la pila del hilo
    double my_partial_sum = 0.0;

    #pragma omp for schedule(runtime)
    for (size_t index = 0; index < values.size(); ++index) {
      // cada hilo añadirá su propia suma parcial a los valores que se le asignan
      my_partial_sum += values[index];
    }

    #pragma omp critical(can_add)  // finalmente, un hilo a la vez sumará
    // la suma parcial al total de sumas
    total_sum += my_partial_sum;
  }

  const double average = values.size() ? total_sum / values.size() : 0.0;
  std::cout << average << std::endl;
}