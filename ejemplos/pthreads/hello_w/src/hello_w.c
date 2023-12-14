#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>

/**
 * @file hello.c
 * @brief Ejemplo sencillo de Hola mundo usando Pthreads
 */

void* race(void* data);  // declaracion greet para implementar despues
int create_threads(uint64_t thread_count);

/**
 * @brief hilo principal del programa (main)
*/
// procedure greet
int main(int argc, char* argv[]) {
#if 0  // Deshabilita el codigo si la condicion da falso 
  for (int index = 0; index < argc; index++) 
    printf("argv[%d] = '%s'\n", index, argv[index]);

#endif

  int error = EXIT_SUCCESS;
  // creater thread_count as result of converting argv[1] to integer
  // thread_count := integer(argv[1])
  uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN); // strtol(argc[1], ...)

  /* extrae un uint64_t de los argumentos brindados al main cuando se ejecuta
  el main y lo guarda en thread_count. Retorna '1' si la operacion fue
  realizada con exito*/
  if (argc == 2) {
    // for thread_number := 0 to thread_count do
    if (sscanf(argv[1], "%" SCNu64, &thread_count) == 1) {
    }else {
      fprintf(stderr, "Error: invalid thread count\n");  /* imprime
        un mensaje en formato error estandar*/
      return EXIT_FAILURE;
    }
  }
  error = create_threads(thread_count);
  return error;  // se reporta si hubo errores a la hora de crear los hilos o no
}  // end procedure


// Subrutina para crear hilos
int create_threads(uint64_t thread_count) {
    int error = EXIT_SUCCESS;
    // Estructura de tipo pthread
  pthread_t* threads = (pthread_t*) malloc(thread_count * sizeof(pthread_t));
  if (threads) {
    for (uint64_t thread_number = 0; thread_number < thread_count;
    thread_number++) {
      // create_thread(greet, thread_number)

      /* se crea el thread y se le dan como parametros: la direccion de memoria
      de la estructura de datos que se define anteriormente, atributos (que se 
      usan para dar prioridad a los hilos) default usando NULL, una subrutina o 
      tarea (en este caso greet) y por ultimo los valores que se den como 
      argumentos son los que va a recibir la subrutina como parametros.
      Se atrapa el codigo error en la variable */
      error = pthread_create(&threads[thread_number], /*attr*/ NULL, race, 
      /*arg*/ (void*) thread_number);
    }

    for (uint64_t thread_number = 0; thread_number < thread_count;
    thread_number++) {
      if (error == EXIT_SUCCESS) {  /* si no hay error (el codigo funcionó)
      se procede a imprimir*/
        pthread_join(threads[thread_number], /*value_ptr*/ NULL);  /* "libera"
        la subrutina cuando termina de ejecutarse y no espera valor de
        retorno*/
      } else {  // se reporta que no se pudo crear un hilo secundario por xrazón
        /* imprime un mensaje en formato error estandar*/
        fprintf(stderr, "Error: could not create secondary thread\n");
        break;
      }
    }
    printf("Hello from main thread\n");  // imprime :o
    free(threads);  // libera la memoria solicitada 
  } else {
    fprintf(stderr, "Error: could not allocte %" PRIu64 "threads\n", 
      thread_count);
    error = EXIT_FAILURE;
  }

  return error;
}

/**
 * @brief hilo secundario declarado anteriormente
 * @param puntero
 * @return puntero
*/
// procedure greet:
void* race(void* data) {
  const uint64_t rank = (uint64_t) data;  /*Castea rank como un uint64_t*/
  // print "Hello from secondary thread"
  printf("Hello from secondary thread %\n" PRIu64, rank);  /*imprime x2 :o; rank
  se refiere a los hilos que recibe pues los mismos encuentran en cierto orden
  y es como si estuvieran rankeados*/ 
  return NULL;  /* Devuelve la direccion de memoria 0 ya que no es necesario
  retornar nada porque la subrutina lo unico que hace es imprimir*/
}  // end procedure
