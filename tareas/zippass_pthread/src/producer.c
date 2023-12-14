// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <semaphore.h>

#include "findPassword.h"
#include "controller.h"
#include "producer.h"

// Function to generate password guesses and add them to the queue
void* produce(void* data) {
  shared_data_t* shared = (shared_data_t*) data;

  // Iterate through different password lengths
  for (size_t passLength = 1; passLength <= shared->maxSizePassword
      ; passLength++) {
    // Calculate the total number of possible password combinations
    size_t con = pow(strlen(shared->alfa), passLength);

    // Generate password guesses and attempt to open the zip archive
    for (size_t numToChange = 0; numToChange <= con - 1; numToChange++) {
      // Generate a password guess based on the current iteration
      char* password = getPass(numToChange, passLength, shared->alfa);

      // Add the generated password to the queue for consumers to process
      queue_queue(shared->queue, password);

      // Signal that a new password is available for consumers
      sem_post(&shared->can_consume);
    }
  }

  // Signal the end of password generation to consumers
  for (size_t thread_number = 0; thread_number < shared->thread_count
    ; thread_number++) {
    // Add a special NULL value to the queue to indicate the end of work
    queue_queue(shared->queue, NULL);

    // Signal consumers that there is work to be done
    sem_post(&shared->can_consume);
  }

  return NULL;
}
