// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>

#include "controller.h"

int main(int argc, char* argv[]) {
  // shared_data_t* shared = calloc(1, sizeof(shared_data_t));
  size_t thread_count = 0;
  if (argc >= 2) {
    thread_count = atoi(argv[1]);

  } else {
    // Si no se proporciona un argumento, obtén el número de núcleos del sistema
    long numCPUs = sysconf(_SC_NPROCESSORS_ONLN);

    if (numCPUs == -1) {
      // Error al obtener la cantidad de núcleos, puedes manejarlo aquí.
      perror("Error al obtener la cantidad de núcleos");
      return 0;
    }

    thread_count = (size_t)numCPUs;
  }
  printf("numero de hilos %zu", thread_count);
  controller_run(thread_count);

  return 0;
}
