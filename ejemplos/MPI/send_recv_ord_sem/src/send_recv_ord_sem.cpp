// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0

#include <mpi.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept> // standard exceptions

// Macro para lanzar excepciones
#define fail(msg) throw std::runtime_error(msg)

void greet(int process_number, int process_count, const char* process_hostname);

int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
    int process_number = -1;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_number);

    int process_count = -1;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);

    char process_hostname[MPI_MAX_PROCESSOR_NAME] = { '\0' };
    int hostname_length = -1;
    MPI_Get_processor_name(process_hostname, &hostname_length);

    try {
      greet(process_number, process_count, process_hostname);
    } catch (const std::runtime_error& exception) {
      std::cerr << "error: " << exception.what() << std::endl;
      error = EXIT_FAILURE;
    }

    MPI_Finalize();
  } else {
    std::cerr << "error: could not init MPI" << std::endl;
    error = EXIT_FAILURE;
  }
  return error;
}
/**
 * @brief Saludo desde los procesos usando MPI
 * 
 * @param numero_proceso Número del proceso
 * @param cantidad_procesos Cantidad de procesos
 * @param nombre_procesador Nombre del host
 */
void greet(int process_number, int process_count
    , const char* process_hostname) {
  const int previous_process = (process_count + process_number - 1)
    % process_count; // previous process
  const int next_process = (process_number + 1) % process_count;
  bool can_print = true; // boolean flag to send to no next process

  if (process_number > 0) {
    // MPI_Recv(&puede_imprimir, 1, MPI_C_BOOL, proceso_anterior, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE)
    // Aquí usamos MPI_Recv para recibir la bandera booleana, la colocamos en la
    // variable puede_imprimir, recibimos solo un elemento, y recibimos de
    // indicamos que estamos recibiendo un MPI_C_BOOL, y recibimos del
    // proceso anterior, también colocamos MPI_STATUS_IGNORE porque no nos
    // interesa el estado del mensaje ni guardarlo
    // por lo que si somos el proceso 1, recibimos del proceso 0
    // si recibimos correctamente, imprimimos el mensaje, si no, lanzamos
    // una excepción distribuida
    if (MPI_Recv(&can_print, /*count*/ 1, MPI_C_BOOL, previous_process
      , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
      fail("could not receive message"); // excepcion distribuida
    }
  }

  std::cout << "Hello from main thread of process " << process_number
    << " of " << process_count << " on " << process_hostname << std::endl;

  // MPI_Send(&puede_imprimir, 1, MPI_C_BOOL, siguiente_proceso, 0, MPI_COMM_WORLD)
  // Aquí usamos MPI_Send para enviar la bandera booleana, la enviamos desde la
  // variable puede_imprimir, enviamos solo un elemento, y enviamos a
  // el siguiente proceso de tipo MPI_C_BOOL
  // por lo que si somos el proceso 0, enviamos al proceso 1
  // si se envía correctamente, pasamos, si no, lanzamos una excepción distribuida
  // el siguiente proceso pertenece a mi equipo de procesos
  if (MPI_Send(&can_print, /*count*/ 1, MPI_C_BOOL, next_process, /*tag*/ 0
    , MPI_COMM_WORLD) != MPI_SUCCESS) {
    fail("could not send message");// distributed exception
  }
}