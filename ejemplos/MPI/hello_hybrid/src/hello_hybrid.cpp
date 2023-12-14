// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0

#include <mpi.h>
#include <omp.h>
#include <iostream>

int main(int argc, char* argv[]) {
  // Iniciar MPI
  if (MPI_Init(&argc, &argv) == MPI_SUCCESS) { // si MPI_SUCCESS es , eso significa que MPI se inicializó correctamente
    int process_number = -1;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_number); // obtener el nombre del host del proceso

    int process_count = -1;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count); 

    char process_hostname[MPI_MAX_PROCESSOR_NAME] = { '\0' }; // obtener el nombre del host del proceso
    int hostname_length = -1; 
    MPI_Get_processor_name(process_hostname, &hostname_length); // get the hostnae of the process
    // aquí usamos el nombre del host, la cantidad de procesos y el número de proceso para imprimir el mensaje
    std::cout << "Hello from main thread of process " << process_number
      << " of " << process_count << " on " << process_hostname << std::endl;
    // numeros de hilos en la maquina actual
    int thread_count = omp_get_max_threads();
    if (argc == 2) {
      // numero de hilos desde argv
      thread_count = atoi(argv[1]);
    }
    // Establecer la cantidad de hilos a utilizar en la próxima región paralela
    // dentro de cada proceso
    #pragma omp parallel num_threads(thread_count) default(none) \
      shared(std::cout, process_number, process_count, process_hostname)
      // establecer las variables compartidas 
    {  // NOLINT(whitespace/braces)
    // hacer una sección crítica para usar cout
      #pragma omp critical(stdout)
      // imprimir el mensaje usando el número de hilo, número de proceso, cantidad de procesos y nombre del host
      std::cout << "\tHello from thread " << omp_get_thread_num() << " of "
        << omp_get_num_threads() << " of process " << process_number
        << " of " << process_count << " on " << process_hostname << std::endl;
    }
    // Finalizar el entorno MPI
    MPI_Finalize(); 
  } else {
    std::cerr << "error: could not init MPI" << std::endl;
  }
  return 0;
}