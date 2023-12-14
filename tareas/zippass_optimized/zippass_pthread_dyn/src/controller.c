// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include <stdbool.h>
#include <stdio.h>

#include "controller.h"
#include "dynamicArray.h"
#include "consumer.h"
#include "producer.h"

int controller_run(size_t thread_count) {
  struct dynamicArray_t array;
  dynamicArrayInit(&array);  // Initialize the dynamic array

  // allocates memory for the shared data
  shared_data_t* shared_data = calloc(1, sizeof(shared_data_t));

  // allocates memory fo the queue
  shared_data->queue = (queue_t*) calloc(1, sizeof(queue_t));
  queue_init(shared_data->queue);  // Initialize the queue

  // allocates memory for the private data
  private_data_t* private_data = (private_data_t*) calloc(thread_count,
    sizeof(private_data_t));
  for (size_t i=0; i < thread_count; ++i) {
    // asings the shared data form the previously allocated one
    private_data[i].shared_data = shared_data;
    // takes the thread number from the given parameters
    private_data[i].thread_number = i;
  }

  // init the mutex and semaphores
  pthread_mutex_init(&shared_data->can_search_pass, /*attr*/ NULL);
  pthread_mutex_init(&shared_data->can_open_zip, /*attr*/ NULL);
  sem_init(&shared_data->can_consume, 0, 0);

  // asings the thread count from the parameters
  shared_data->thread_count = thread_count;
  printf("hilos: %zu", shared_data->thread_count);

  // producer thread
  pthread_t producer;
  // allocate memory for consumer threads
  pthread_t* consumers = (pthread_t*) calloc(thread_count
    , sizeof(pthread_t));

  char* alfa = (char*)calloc(50, sizeof(char));  // Allocate memory for alfa
  shared_data->alfa = alfa;

  // Read alfa and maxNum from input
  fscanf(stdin, "%s %zu", alfa, &shared_data->maxSizePassword);

  size_t cont = 0;

  while (true) {
    // Allocate memory for filePath
    char* filePath = (char*)calloc(50, sizeof(char));
    shared_data->path = filePath;
    // Read file path from input
    int size = fscanf(stdin, "%s", shared_data->path);
    if (size != 1) {
      free(filePath);
      break;  // Exit the loop if reading fails
    }

    // Append file path to dynamic array
    dynamicArrayAppend(&array, shared_data->path);
    cont++;
    free(filePath);
  }

  for (size_t fileNumber = 0; fileNumber < array.count; fileNumber++) {
      // Create a producer thread
      pthread_create(&producer, NULL, produce, shared_data);
      // Wait for the producer thread to finish
      pthread_join(producer, NULL);

      // Reset the flag indicating whether a password was found
      shared_data->passFound = false;
      // Get the file path from the dynamic array
      char* path = array.dynamicArrayInner[fileNumber].element;
      shared_data->path = path;
      shared_data->password = NULL;

      // Create consumer threads
      for (size_t i = 0; i < thread_count; i++) {
          private_data[i].thread_number = i;
          pthread_create(&consumers[i], NULL, consume, &private_data[i]);
      }

      // Wait for all consumer threads to finish
      for (size_t i = 0; i < thread_count; i++) {
          pthread_join(consumers[i], NULL);
      }

      // If a password was found, copy it to the dynamic array
      if (shared_data->password != NULL) {
          size_t size = strlen(shared_data->password);
          // Allocate memory for the password in the dynamic array
          array.dynamicArrayInner[fileNumber].password = (char*)calloc(size + 1
            , sizeof(char));
          // Copy the password to the dynamic array
          strcpy(array.dynamicArrayInner[fileNumber].password
            , shared_data->password);
          // Free the memory allocated for the password in shared_data
          free(shared_data->password);
      }
  }

  // Print the file paths and passwords (if found)
  for (size_t fileNumber = 0; fileNumber < array.count; fileNumber++) {
      printf("%s ", array.dynamicArrayInner[fileNumber].element);
      if (array.dynamicArrayInner[fileNumber].password != NULL) {
          printf("%s\n", array.dynamicArrayInner[fileNumber].password);
      } else {
          printf("\n");
      }
  }

  // frees all the memory
  free(alfa);
  free(consumers);
  pthread_mutex_destroy(&shared_data->can_open_zip);
  pthread_mutex_destroy(&shared_data->can_search_pass);
  free(private_data);
  queue_destroy(shared_data->queue);
  free(shared_data->queue);
  free(shared_data);
  dynamicArrayFinalize(&array);

  return 0;

  return EXIT_SUCCESS;
}
