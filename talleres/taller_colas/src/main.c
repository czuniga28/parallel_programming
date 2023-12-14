#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "queue.h"

// thread_shared_data_t
typedef struct shared_data {
  uint64_t consumer_count;
  queue_t* queue;
} shared_data_t;

// thread_private_data_t
typedef struct private_data {
  uint64_t consumer_number;  // rank
  shared_data_t* shared_data;
} private_data_t;

void* producir (void* datos);
void* consumir (void* datos);

int main() {

  shared_data_t* shared_data = calloc(1, sizeof(shared_data_t));
  private_data_t* pri_data = calloc(2, sizeof(private_data_t));

  // printf("Hola mundo\n");
  shared_data->consumer_count = 2;
  shared_data->queue = (queue_t*) calloc(1, sizeof(queue_t));
  queue_init(shared_data->queue);

  pthread_t productor;
  pthread_t* consumidores = (pthread_t*) calloc(2, sizeof(pthread_t));

  pthread_create(&productor, NULL, producir, shared_data);

  for (size_t consumer_number = 0
      ; consumer_number < shared_data->consumer_count; consumer_number++) {
    pri_data[consumer_number].shared_data = shared_data;
    pri_data[consumer_number].consumer_number = consumer_number;
    pthread_create(&consumidores[consumer_number], NULL, consumir
        , &pri_data[consumer_number]);
  }


  // for (size_t i = 0; i < 10; i++) {
  //   char* text = (char*) calloc(21, sizeof(char));
  //   strcpy(text, "Hola me llamo Peter!");
  //   queue_queue(queue, text);
  // }

  // for (size_t i = 0; i < 10; i++) {
  //   char* text = queue_dequeue(queue);
  //   printf("%s\n", text);
  //   free(text);
  // }

  for (size_t i = 0; i < shared_data->consumer_count; i++) {
    pthread_join(consumidores[i], NULL);
  }

  pthread_join(productor, NULL);

  queue_destroy(shared_data->queue);

  free(consumidores);
  free(pri_data);
  free(shared_data->queue);
  free(shared_data);
  return EXIT_SUCCESS;
}

void* producir (void* datos) {
  shared_data_t* share = (shared_data_t*) datos;
  printf("Productor: trabajando!\n");
  for (size_t i = 0; i < 20; i++) {
    char* num = (char*) calloc(3, sizeof(char));
    sprintf(num,"%zu", i);
    printf("Produciendo: %s\n", num);
    queue_queue(share->queue, num);
    usleep(50);
  }
  // Producir condicion de parada
  for (size_t i = 0; i < share->consumer_count; i++) {
    char* text = (char*) calloc(3, sizeof(char));
    strcpy(text, "-q");
    queue_queue(share->queue, text);
  }
  return NULL;
}

void* consumir (void* datos) {
  private_data_t* pri_data = (private_data_t*) datos;
  shared_data_t* sha_data = (shared_data_t*) pri_data->shared_data;
  while (true) {
    char* text = queue_dequeue(sha_data->queue);
    if (strcmp(text, "-q") == 0) {
      free(text);
      break;
    }
    printf("\tConsumiento %zu: %s\n", pri_data->consumer_number, text);
    usleep(100);
    free(text);
  }
  return NULL;
}