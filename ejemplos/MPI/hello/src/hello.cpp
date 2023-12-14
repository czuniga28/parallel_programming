// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0

#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
  // En MPI no llamamos al grupo un equipo de hilos, los llamamos mundo de
  // procesos/
  // El entorno en ejecución (el comunicador)
  // es el encargado de crear el mundo de procesos
  // Inicializamos el entorno MPI mediante el comunicador
  // MPI Init recibe no una copia de los argumentos sino los originales
  // para que MPI pueda modificarlos
  if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
    int process_number = -1;
    // Obtenemos el número de procesos al que pertenezco
    // MPI Comm Rank recibe el número de mundos de procesos y un número
    // para colocar el número de proceso en/
    // MPI_COMM_WORLD es la constante con el número de mundos de procesos
    MPI_Comm_rank(MPI_COMM_WORLD, &process_number);

    int process_count = -1;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    // Obtener el nombre del procesador (nombre del procesador del host)
    char process_hostname[MPI_MAX_PROCESSOR_NAME] = { '\0' };
    int hostname_length = -1;
    // recibir un búfer para poner el nombre del procesador y la longitud del
    // nombre del procesador. Es como un código de error
    MPI_Get_processor_name(process_hostname, &hostname_length);

    std::cout << "Hello from main thread of process " << process_number
      << " of " << process_count << " on " << process_hostname << std::endl;
    // MPI Init y MPI Finalize crean una región de comunicación
    // entre los procesos.
    MPI_Finalize();
  } else {
    std::cerr << "error: could not init MPI" << std::endl;
  }
  return 0;
}