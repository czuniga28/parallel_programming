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

  #pragma omp parallel num_threads(thread_count) \
    default(none) shared(values, total_sum)
  {
    double my_partial_sum = 0.0;

    #pragma omp for schedule(runtime)
    for (size_t index = 0; index < values.size(); ++index) {
      my_partial_sum += values[index];
    }
    // #pragma omp critical(can_add)
    // la directiva atomic se asegurará de que solo un hilo a la vez
    // realizará la operación dentro de la región. Pero esto se hará
    // a través de instrucciones de hardware, por lo que será más rápido
    // que la región crítica. Está utilizando la instrucción atómica de
    // hardware para controlar la concurrencia.
    // ten en cuenta que no todas las operaciones se pueden realizar con
    // atomic, solo aquellas que ya están implementadas en el hardware.
    // Como asignación, suma, resta, multiplicación, división, y operaciones
    // bit a bit: and, or, xor, not, e incremento y decremento. Consultar
    // la documentación para obtener más detalles.
    #pragma omp atomic
    total_sum += my_partial_sum;
  }

  const double average = values.size() ? total_sum / values.size() : 0.0;
  std::cout << average << std::endl;
}