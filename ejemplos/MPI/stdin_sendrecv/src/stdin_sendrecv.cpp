// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0

#include <mpi.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#define fail(msg) throw std::runtime_error(msg)

void process_values(int process_number, int process_count
  , const char* process_hostname);

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
      const double start_time = MPI_Wtime(); // obtenemos el tiempo de inicio
      process_values(process_number, process_count, process_hostname);
      const double elapsed = MPI_Wtime() - start_time; // obtenemos el tiempo transcurrido
      std::cout << process_hostname << ":" << process_number
        << ".m: elapsed time " << elapsed << "s" << std::endl; // imprimimos el tiempo transcurrido
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
// definimos una función para procesar los valores
// pasamos el número de proceso, la cantidad de procesos y el nombre del host como parámetros
/**
 * @brief procesa los valores. recibe los valores del proceso 0 y los envía a los demás procesos
 * 
 * @param process_number el número de proceso
 * @param process_count la cantidad de procesos
 * @param process_hostname el nombre del host
 *
 */
void process_values(int process_number, int process_count
  , const char* process_hostname) {
  std::vector<double> values;
  size_t value_count = 0;
  // leemos los valores desde la entrada estándar
  if (process_number == 0) { // si somos el proceso principal, hacemos la lectura
    double value = 0.0;
     // los almacenamos en el vector valores
    while (std::cin >> value) {
      // añadimos el valor al vector de valores
      values.push_back(value);
    }
    // obtenemos el tamaño del vector de valores
    value_count = values.size();

    for (int target = 1; target < process_count; ++target) {
      // compilación assert, verificamos si la arquitectura de la computadora es de 64 bits
      // si no lo es, lanzamos un error y detenemos la compilación
      static_assert(sizeof(value_count) == sizeof(uint64_t)
        , "update MPI_Send data type to match your architecture");\
        // enviamos la cantidad de valores al proceso destino
        // RECORDAR: MPI envía y recibe mensajes en el orden en que se envían. 
        // Así que podemos contar que el primer mensaje será la cantidad de valores
      if (MPI_Send(&value_count, /*count*/ 1, MPI_UINT64_T, target
        , /*tag*/ 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
        fail("could not send value count");
      }
      // enviamos el array de valores al proceso destino
      if (MPI_Send(&values[0], value_count, MPI_DOUBLE, target
        , /*tag*/ 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
        fail("could not send values");
      }
    }
  } else { // si no somos el proceso principal, hacemos la recepción e impresión
  // recibimos la cantidad de valores del proceso principal
    if (MPI_Recv(&value_count, /*capacity*/ 1, MPI_UINT64_T, /*source*/ 0
      , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
      fail("could not receive value count");
    }
    // redimensionamos el vector de valores para que coincida con la cantidad de valores
    values.resize(value_count);
    // recibimos el array de valores del proceso principal
    if (MPI_Recv(&values[0], /*capacity*/ value_count, MPI_DOUBLE, /*source*/ 0
      , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
      fail("could not receive values");
    }
  }
  for (size_t index = 0; index < values.size(); ++index) {
    std::cout << process_hostname << ":" << process_number << ".m: values["
      << index << "] == " << values[index] << std::endl;
  }
}