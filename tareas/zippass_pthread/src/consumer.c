  // Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
  #define _GNU_SOURCE

  #include <stdio.h>
  #include <stdlib.h>
  #include <pthread.h>
  #include <semaphore.h>

  #include "consumer.h"
  #include "controller.h"
  #include "findPassword.h"

  // Function to be executed by consumer threads
  void* consume(void* data) {
    private_data_t* private = (private_data_t*) data;
    // Attempt to open the ZIP file with the dequeued password

    // Infinite loop until a password is found or all work is done
    while (true) {
      // Lock the mutex to check if a password has been found
      pthread_mutex_lock(&private->shared_data->can_search_pass);
      if (private->shared_data->passFound) {
        // If a password is found, unlock the mutex and break out of the loop
        pthread_mutex_unlock(&private->shared_data->can_search_pass);
        break;
      }
      // If a password is not found, unlock the mutex
      pthread_mutex_unlock(&private->shared_data->can_search_pass);

      // Wait for permission to consume (signaled by the producer)
      sem_wait(&private->shared_data->can_consume);

      // Dequeue a password to try
      char* pass = queue_dequeue(private->shared_data->queue);

      // If the queue is empty, break out of the loop
      if (pass == NULL) {
        break;
      }

      // Attempt to open the ZIP file with the dequeued password
      size_t error = openZip(private->shared_data->path, pass
        , private->shared_data);

      if (error == EXIT_SUCCESS) {
        // If the ZIP file is successfully opened, lock the mutex to set passFound
        pthread_mutex_lock(&private->shared_data->can_search_pass);
        private->shared_data->passFound = true;
        private->shared_data->password = pass;
        pthread_mutex_unlock(&private->shared_data->can_search_pass);
        free(pass);
        break;
        return NULL;  // Exit the thread
      }

      free(pass);  // Free memory allocated for the dequeued password
    }

    return NULL;  // Exit the thread
  }
