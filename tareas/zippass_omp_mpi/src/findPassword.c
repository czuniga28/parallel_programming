// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

#include "findPassword.h"


// Generate a password guess based on the given number and alphabet
char* getPass(size_t numToChange, size_t passLength, char* alfa) {
  size_t tamBase = strlen(alfa);  // The base to convert

  char* passGuess = (char*)calloc(passLength + 1, sizeof(char));

  if (passGuess == NULL) {
    perror("Fallo al asignar memoria");
    exit(EXIT_FAILURE);
  }

  // Generate the password guess by selecting characters from the alphabet
  for (int i = (int)passLength - 1; i >= 0; i--) {
    passGuess[i] = alfa[numToChange % tamBase];
    numToChange = numToChange / tamBase;
  }
  passGuess[passLength] = '\0';   // Terminate the password guess

  return passGuess;
}

size_t forceZip(size_t maxSizePassword, char* alfa, char* path) {
  size_t found = EXIT_FAILURE;
  omp_lock_t found_lock;
  omp_init_lock(&found_lock);

  // Move memory allocation outside the parallel loop
  char* password = (char*)calloc(maxSizePassword + 1, sizeof(char));
  if (password == NULL) {
    perror("Fallo al asignar memoria");
    exit(EXIT_FAILURE);
  }

  // Move tzset_internal outside the parallel loop
  // tzset_internal();

  //TODO Parallelize the outer loop using OpenMP
  #pragma omp parallel for
  for (size_t passLength = 1; passLength <= maxSizePassword; passLength++) {
    if (found == EXIT_FAILURE) {
      size_t con = pow(strlen(alfa), passLength);

      // TODO Parallelize the inner loop using OpenMP
      #pragma omp parallel for
      for (size_t numToChange = 0; numToChange <= con - 1; numToChange++) {
        if (found == EXIT_FAILURE) {
          password = getPass(numToChange, passLength, alfa);

          int result = openZip(path, password);

          // Use the lock to protect the critical section
          omp_set_lock(&found_lock);
          if (result == EXIT_SUCCESS) {
            found = EXIT_SUCCESS;
          }
          omp_unset_lock(&found_lock);
        }
      }
    }
  }

  if (found == EXIT_FAILURE) {
    printf("%s\n", path);  // Prints the file path if it doesn't have a password
  }

  free(password);
  omp_destroy_lock(&found_lock);

  return found;  // Return success if any thread found the password
}
