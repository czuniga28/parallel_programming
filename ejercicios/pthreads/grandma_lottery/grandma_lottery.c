#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/**
 * @file grandma_lottery.c
 * @brief abuela como el hilo principal, y los dos nietos como dos hilos 
 * secundarios. Los nietos generan un número pseudoaleatorio para representar 
 * la compra de la fracción de lotería. La espera de la abuela del regreso a 
 * casa de los dos nietos es representado por su join. Los nietos comunican a 
 * la abuela los números obtenidos a través del valor de retorno de la 
 * rutina secundaria.
 * @author Christopher Zuniga C28730
 */

typedef struct Datos_Nieto {  // estructura de datos para almacenar el numero
  int numeroComprado;
} Datos_Nieto;

void* rutina_nieto(void* data);  // declaracion de la rutina del nieto

int main() {
  struct Datos_Nieto *datos_nieto1, *datos_nieto2;
  datos_nieto1 = (Datos_Nieto*) malloc (sizeof(Datos_Nieto));
  datos_nieto2 = (Datos_Nieto*) malloc (sizeof(Datos_Nieto));

  srand(time(NULL));  // usa el tiempo como semilla para generar numeros random

  pthread_t nieto1;
  pthread_t nieto2;

  int error1 = pthread_create(&nieto1, NULL,
    rutina_nieto, datos_nieto1);  // Pasar datos_nieto1 sin el & aquí
  int error2 = pthread_create(&nieto2, NULL,
    rutina_nieto, datos_nieto2);  // Pasar datos_nieto2 sin el & aquí

  if (error1 == EXIT_SUCCESS && error2 == EXIT_SUCCESS) {
    pthread_join(nieto1, NULL);
    printf("El numero del primer nieto es: %d\n", datos_nieto1->numeroComprado);

    pthread_join(nieto2, NULL);
    printf("El numero del segundo nieto es: %d\n", datos_nieto2->numeroComprado);
  } else {  // se reporta que no se pudo crear un nuevo hilo por x o y razón
    // imprime un mensaje en formato error estandar
    fprintf(stderr, "Error: could not create a new thread\n");
  }

  free(datos_nieto1);  // libera memoria
  free(datos_nieto2);  // libera memoria

  return (error1 == EXIT_SUCCESS && error2 == EXIT_SUCCESS)
    ? EXIT_SUCCESS : EXIT_FAILURE;
}

void* rutina_nieto(void* data) {
  Datos_Nieto* datos = (Datos_Nieto*) data;
  int numeroLoteria = rand() % 100;  // se genera un numero random entre 1 y 100
  datos->numeroComprado = numeroLoteria;
  return NULL;
}
