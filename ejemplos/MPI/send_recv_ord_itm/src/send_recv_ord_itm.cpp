// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0

#include <mpi.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#define fail(msg) throw std::runtime_error(msg)

const size_t MESSAGE_CAPACITY = 512; // definimos un tamaño máximo para el mensaje

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
    // errores
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
 * @brief Saluda desde el proceso 0 a todos los demás procesos enviando un mensaje
 *        para ser impreso por el proceso principal. Esto se hace utilizando funciones
 *        de envío y recepción para imponer un orden específico a los mensajes.
 * 
 * @param porcess_number el número del proceso
 * @param process_count el número de procesos
 * @param process_hostname el nombre del host
 *
 */
void greet(int process_number, int process_count
    , const char* process_hostname) {
  std::stringstream buffer; // creamos un buffer para almacenar el mensaje usando un flujo de cadena
  // luego escribimos el mensaje en el buffer
  buffer << "Hello from main thread of process " << process_number 
      << " of " << process_count << " running on " << process_hostname
    << " of " << process_count << " on " << process_hostname;
  // importante porque no podemos enviar mensajes a nosotros mismos ya que no funciona
  // y utiliza toda la CPU esperando a que llegue el mensaje
  if (process_number != 0) { // si no somos el proceso principal  
    // enviamos el mensaje al proceso principal
    const std::string& message = buffer.str(); // obtenemos el mensaje del buffer
    // y lo enviamos al proceso principal
    // enviamos message.data() usando la función send y su longitud
    if (MPI_Send(message.data(), message.length(), MPI_CHAR, /*target*/ 0
      , /*tag*/ 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
      fail("could not send message"); // si no se pudo enviar el mensaje, lanzamos un error usando la macro fail
    }
  } else { // si no somos el proceso principal 
  // imprimimos nuestro propio mensaje
    std::cout << process_number << " said " << buffer.str() << std::endl;
  // y luego recibimos los mensajes de los otros procesos e imprimimos
    for (int source = 1; source < process_count; ++source) {
      std::vector<char> message(MESSAGE_CAPACITY); // creamos un vector de chars para almacenar el mensaje
      // de tamaño MESSAGE_CAPACITY
      // para obtener el char* usamos &mensaje y accedemos al primer elemento
      // como &mensaje[0] esto
      // no conocemos el tamaño del mensaje, así que usamos un búfer, esperando que el mensaje sea
      // más pequeño que el búfer, aquí es MESSAGE_CAPACITY
      if (MPI_Recv(&message[0], MESSAGE_CAPACITY, MPI_CHAR, source
        , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
        fail("could not receive message");
      }
      std::cout << source << " sent " << &message[0] << std::endl;
    }
  }
}