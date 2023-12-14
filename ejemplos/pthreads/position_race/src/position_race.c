#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>

// thread_shared_data
typedef struct shared_data {
  uint64_t thread_count; // todos los hilos tiene acceso a este dato
  uint64_t position;  // siguiente thread para el busy wait
  pthread_mutex_t can_access_position;
} shared_data_t;

// thread_private_data Crea un registro que puede alojar campos de distinto tipo
typedef struct private_data {
  uint64_t thread_number; // rank
  shared_data_t* shared_data;  // puntero a los datos compartidos
}private_data_t;  // el compilador cada que ve el nombre lo cambia por esto

/**
 * @file hello.c
 * @brief Ejemplo sencillo de Hola mundo usando Pthreads
 */

void* race(void* data);  // declaracion greet para implementar despues
int create_threads(shared_data_t* shared_data);

/**
 * @brief hilo principal del programa (main)
*/
// procedure greet
int main(int argc, char* argv[]) {

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

  shared_data_t* shared_data = (shared_data_t*) calloc
    (1, sizeof(shared_data_t));  // pide memoria para almacenar el # de hilos
  if (shared_data) {
    shared_data->position = 0;  // inicializa en 0 la memoria compartida
    shared_data->thread_count = thread_count;
    error = pthread_mutex_init(&shared_data->can_access_position, 
      /*attr*/ NULL);  // inicaliza el mutex

    if (error == EXIT_SUCCESS) {

      // inicializacion del registro para almacenar
      struct timespec start_time, finish_time;

      /* Primer argumento es el tipo de reloj que va a usar la funcion (en este
      caso el monotonico) y luego se le pasa un registro previamente definido
      para guardar este tiempo*/

      clock_gettime(CLOCK_MONOTONIC, &start_time);

      error = create_threads(shared_data);  // adentro tiene el thread count

      clock_gettime(CLOCK_MONOTONIC, &finish_time);  // se almacena cuanto duro

      // Resta las diferencias de tiempo para calcular el tiempo de duracion
      double elapsed_time = finish_time.tv_sec - start_time.tv_sec + 
        (finish_time.tv_nsec - start_time.tv_nsec) / 1e9;

      printf("Execution time: %.9lfs\n", elapsed_time);

      pthread_mutex_destroy(&shared_data->can_access_position);
      free(shared_data);  // libera la memoria solicitada de la cantidad de hilo

    } else {
      fprintf(stderr, "Error: could not inint mutex\n");
      return 13;
    }
  } else {
    fprintf(stderr, "Error: could not allocate shared data\n");
    return 12;
  }
  return error;  // se reporta si hubo errores a la hora de crear los hilos o no
}  // end procedure


// Subrutina para crear hilos
int create_threads(shared_data_t* shared_data) {
  int error = EXIT_SUCCESS;
  // Estructura de tipo pthread
  pthread_t* threads = (pthread_t*)
    malloc(shared_data->thread_count * sizeof(pthread_t));

  // Vector con memoria privada para cada hilo
  private_data_t* private_data = (private_data_t*) 
    calloc(shared_data->thread_count, sizeof(private_data_t));

  if (threads && private_data) {
    for (uint64_t thread_number = 0; thread_number < shared_data->thread_count;
    thread_number++) {
      private_data[thread_number].thread_number = thread_number;  // asigna los
      // valores a los hilos

      // accesa a los datos compartidos con un puntero
      private_data[thread_number].shared_data = shared_data;
      
      // create_thread(greet, thread_number)

      /* se crea el thread y se le dan como parametros: la direccion de memoria
      de la estructura de datos que se define anteriormente, atributos (que se 
      usan para dar prioridad a los hilos) default usando NULL, una subrutina o 
      tarea (en este caso greet) y por ultimo los valores que se den como 
      argumentos son los que va a recibir la subrutina como parametros.34
      Se atrapa el codigo error en la variable. Se envia la direccion de memoria
      de private data para poder pasar el registro como argumento */
      error = pthread_create(&threads[thread_number], /*attr*/ NULL, race, 
      /*arg*/ &private_data[thread_number]);
      if (error == EXIT_SUCCESS) {  /* si no hay error (el codigo funcionó)
      se procede a imprimir*/
      } else {  // se reporta que no se pudo crear un hilo secundario por xrazón
        /* imprime un mensaje en formato error estandar*/
        fprintf(stderr, "Error: could not create secondary thread\n");
        error = 21;  // asigna un codigo de error
        break;
      }
    }

    printf("Hello from main thread\n");  // imprime :o

    for (uint64_t thread_number = 0; thread_number < shared_data->thread_count;
    thread_number++) {
        pthread_join(threads[thread_number], /*value_ptr*/ NULL);  /* "libera"
        la subrutina cuando termina de ejecutarse y no espera valor de
        retorno*/
    }

    free(private_data);  // la memoria se libera en orden inverso a como se pide
    free(threads);  // libera la memoria solicitada 
  } else {
    fprintf(stderr, "Error: could not allocte %" PRIu64 "threads\n", 
      shared_data->thread_count);
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
  assert(data);
  private_data_t* private_data = (private_data_t*) data;  /* Recibe una
  direccion de memoria que apunta un registro de tipo private_data_t*/
  shared_data_t* shared_data = private_data->shared_data;

  // lock(can_access_position)
  pthread_mutex_lock(&shared_data->can_access_position);

    //position := position + 1
    uint64_t my_position = ++shared_data->position;  // post-incremento

    // print "Hello from secondary thread"
    /*rank se refiere a los hilos que recibe pues los mismos encuentran en cierto 
    orden y es como si estuvieran rankeados*/
    // Doble nivel de indireccion
    printf("Thread %" PRId64 "/%" PRId64 ": I arrived at position %" PRId64 "\n", 
    private_data->thread_number, shared_data->thread_count, my_position);

  // unlock(can_access_position)
  pthread_mutex_unlock(&shared_data->can_access_position); 



  return NULL;  /* Devuelve la direccion de memoria 0 ya que no es necesario
  retornar nada porque la subrutina lo unico que hace es imprimir*/
}  // end procedure
