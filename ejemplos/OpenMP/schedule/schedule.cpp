// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0
#include <omp.h>
#include <iostream>
#include <vector>
// en este método utilizamos la referencia constante para imprimir el vector.
// recibimos el vector como una referencia constante para evitar copiarlo y para
// evitar modificarlo.
void print_mapping(const char* type, const std::vector<int>& mapping);

int main(int argc, char* argv[]) {
  int thread_count = omp_get_max_threads();
  if (argc >= 2) {
    thread_count = atoi(argv[1]);
  }

  int iteration_count = thread_count;
  if (argc >= 3) {
    iteration_count = atoi(argv[2]);
  }

  int block_size = 0;
  if (argc >= 4) {
    block_size = atoi(argv[3]);
  }
  // declaramos un vector con elementos de iteration_count inicializados a 0
  // aquí guardamos el mapping de las iteraciones a los threads
  std::vector<int> mapping(iteration_count);

  #pragma omp parallel num_threads(thread_count) \
    default(none) shared(iteration_count, mapping, block_size)
    // aquí estamos pasando block_size como una variable compartida entre los
    // threads.
  {
    if (block_size == 0) {
      // la palabra clave schedule se usa para especificar cómo se distribuirán
      // las iteraciones del bucle for entre los threads
      // la palabra static se utiliza para especificar que las iteraciones
      // se distribuirán entre los threads de manera Estática en Bloques
      #pragma omp for schedule(static)
      for (int iteration = 0; iteration < iteration_count; ++iteration) {
        mapping[iteration] = omp_get_thread_num();
      }

      #pragma omp single
      print_mapping("estático   ", mapping);
      // aquí la palabra clave dynamic se utiliza para especificar que las
      // iteraciones se distribuirán entre los threads de manera dinámica.
      // su tamaño de bloque predeterminado es 1
      #pragma omp for schedule(dynamic)
      for (int iteration = 0; iteration < iteration_count; ++iteration) {
        mapping[iteration] = omp_get_thread_num();
      }

      #pragma omp single
      print_mapping("dinámico  ", mapping);
      // aquí la palabra clave guided se utiliza para especificar que las
      // iteraciones se distribuirán entre los threads de manera guiada, esto es
      // similar a la distribución dinámica pero el tamaño de los bloques no es
      // constante
      // al principio el tamaño de los bloques es grande y luego se reduce
      // a medida que se distribuyen las iteraciones.
      // Piden trozos tan pronto como terminan. Su tamaño de bloque
      // predeterminado es 1
      #pragma omp for schedule(guided)
      for (int iteration = 0; iteration < iteration_count; ++iteration) {
        mapping[iteration] = omp_get_thread_num();
      }

      #pragma omp single
      print_mapping("guiado    ", mapping);
    } else {
      // aquí la palabra clave static se utiliza para especificar que las
      // iteraciones se distribuirán entre los threads de manera estática usando
      // bloques fijos
      // usar bloques con la distribución estática es similar a usar la
      // distribución cíclica estática o la distribución cíclica estática
      // con bloques
      #pragma omp for schedule(static, block_size)
      for (int iteration = 0; iteration < iteration_count; ++iteration) {
        mapping[iteration] = omp_get_thread_num();
      }

      #pragma omp single
      print_mapping("estático,N ", mapping);
      // aquí la palabra clave dynamic se utiliza para especificar que las
      // iteraciones se distribuirán entre los threads de manera dinámica usando
      // bloques fijos
      // por ejemplo, si tenemos 10 iteraciones y 3 threads y usamos un tamaño de
      // bloque de 3, el primer thread que obtenga trabajo obtendrá 3 unidades
      // de trabajo.
      #pragma omp for schedule(dynamic, block_size)
      for (int iteration = 0; iteration < iteration_count; ++iteration) {
        mapping[iteration] = omp_get_thread_num();
      }

      #pragma omp single
      print_mapping("dinámico,N", mapping);
      // en el caso de la distribución guiada, el tamaño del bloque no es constante
      // pero se calcula como el número de iteraciones dividido por el número de
      // threads y se reduce a medida que se distribuyen las iteraciones. Cuando
      // pasamos un tamaño de bloque a la distribución guiada, el tamaño mínimo del
      // bloque será el tamaño del bloque.
      #pragma omp for schedule(guided, block_size)
      for (int iteration = 0; iteration < iteration_count; ++iteration) {
        mapping[iteration] = omp_get_thread_num();
      }

      #pragma omp single
      print_mapping("guiado,N  ", mapping);
    }
  }
}

void print_mapping(const char* type, const std::vector<int>& mapping) {
  std::cout << type;
  for (size_t index = 0; index < mapping.size(); ++index) {
    std::cout << mapping[index] << (index == mapping.size() - 1 ? '\n' : ' ');
  }
}