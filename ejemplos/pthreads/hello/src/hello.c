#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @file hello.c
 * @brief Ejemplo sencillo de Hola mundo usando Pthreads
 */

void* race(void* data);  // declaracion greet para implementar despues

/**
 * @brief hilo principal del programa (main)
*/
// procedure greet
int main(void) {
  // create_thread(greet)
  pthread_t thread;  // Estructura de tipo pthread

  int error = pthread_create(&thread, /*attr*/ NULL, race, /*arg*/ NULL);
  /* se crea el thread y se le dan como parametros: la direccion de memoria de
  la estructura de datos que se define anteriormente,
  atributos (que se usan para dar prioridad a los hilos) default usando NULL,
  una subrutina o tarea (en este caso greet)
  y por ultimo los valores que se den como argumentos son los que va a recibir
  la subrutina como parametros.

  se atrapa el codigo error en la variable
  */
  if (error == EXIT_SUCCESS) {  /* si no hay error (el codigo funcionó)
  se procede a imprimir*/
    sleep(2); //  Duerme el hilo primario para verificar que es concurrente
    // print "Hello from main thread"
    printf("Hello from main thread\n");  // imprime :o
    pthread_join(thread, /*value_ptr*/ NULL);  /* "libera" la subrutina cuando
    termina de ejecutarse y no espera valor de retorno*/
  } else {  // se reporta que no se pudo crear un hilo secundario por x razón
    fprintf(stderr, "Error: could not create secondary thread\n");  /* imprime
    un mensaje en formato error estandar*/
  }
  return error;  // se reporta si hubo errores a la hora de crear los hilos o no
}  // end procedure

/**
 * @brief hilo secundario declarado anteriormente
 * @param puntero
 * @return puntero
*/
// procedure greet:
void* race(void* data) {
  (void) data;  /* "engañar" al compilador para hacer como que data
  se está usando en algo*/
  // print "Hello from secondary thread"
  printf("Hello from secondary thread\n");  // imprime x2 :o
  return NULL;  /* Devuelve la direccion de memoria 0 ya que no es necesario
  retornar nada porque la subrutina lo unico que hace es imprimir*/
}  // end procedure
