#include <mpi.h>
#include <iostream>
#include <stdexcept>

#include "UniformRandom.hpp"

#define fail(msg) throw std::runtime_error(msg)

void generate_lucky_statistics(int process_number, int process_count);

int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
    try {
      int process_number = -1;
      MPI_Comm_rank(MPI_COMM_WORLD, &process_number);

      int process_count = -1;
      MPI_Comm_size(MPI_COMM_WORLD, &process_count);

      char process_hostname[MPI_MAX_PROCESSOR_NAME] = { '\0' };
      int hostname_length = -1;
      MPI_Get_processor_name(process_hostname, &hostname_length);

      generate_lucky_statistics(process_number, process_count);
    } catch (const std::runtime_error& exception) {
      std::cout << exception.what() << std::endl;
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
 * @brief Genera números de la suerte y estadísticas para un proceso dado y reduce
 *        los resultados al proceso principal. Obtiene la suma de todos los números de la suerte,
 *        el número de la suerte mínimo y máximo.
 * 
 * @param process_number Número del proceso.
 * @param process_count Número de procesos.
 */
void generate_lucky_statistics(int process_number, int process_count) {
  // Generar my lucky number
  UniformRandom<int> uniformRandom(process_number);
  const int my_lucky_number = uniformRandom.between(0, 100);

  std::cout << "Process " << process_number << ": my lucky number is "
    << my_lucky_number << std::endl;

  int all_min = -1;
  int all_max = -1;
  int all_sum = -1;

  // Actualiza estadísticas distribuidas desde los números de la suerte de los procesos
  // La función MPI_Reduce toma los siguientes argumentos:
  // 1. La dirección de los datos a reducir (entrada)
  // 2. La dirección de los datos reducidos (salida)
  // 3. El número de elementos a reducir
  // 4. El tipo de datos a reducir
  // 5. La operación a realizar
  // 6. El rango del proceso que recibirá los datos reducidos
  // 7. El comunicador (que es el grupo de procesos que participará en la reducción)
  if (MPI_Reduce(/*input*/ &my_lucky_number, /*output*/ &all_min, /*count*/ 1
    , MPI_INT, MPI_MIN, /*root*/ 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
    fail("error: could not reduce min");
  }
  // Aquí reducimos el número de la suerte máximo
  if (MPI_Reduce(/*input*/ &my_lucky_number, /*output*/ &all_max, /*count*/ 1
    , MPI_INT, MPI_MAX, /*root*/ 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
    fail("error: could not reduce max");
  }
  // Aquí reducimos la suma de todos los números de la suerte
  if (MPI_Reduce(/*input*/ &my_lucky_number, /*output*/ &all_sum, /*count*/ 1
    , MPI_INT, MPI_SUM, /*root*/ 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
    fail("error: could not reduce sum");
  }
  // Informamos nuestros hallazgos a través del proceso principal
  // porque es el único que tiene todos los datos
  // los demás procesos no tienen all_min, all_max y all_sum porque
  // solo redujimos los datos al proceso principal
  if (process_number == 0) {
    const double all_average = double(all_sum) / process_count;
    std::cout << "Process " << process_number << ": all minimum = "
      << all_min << std::endl;
    std::cout << "Process " << process_number << ": all average = "
      << all_average << std::endl;
    std::cout << "Process " << process_number << ": all maximum = "
      << all_max << std::endl;
  }
}