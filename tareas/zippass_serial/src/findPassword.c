// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

// Brute-force attack on a encrypted zip file
size_t forceZip(size_t maxSizePassword, char* alfa, char* path) {
  for (size_t passLength = 1; passLength <= maxSizePassword; passLength++) {
    size_t con = pow(strlen(alfa), passLength);
    // Generate password guesses and attempt to open the zip archive
    for (size_t numToChange = 0; numToChange <= con - 1; numToChange++) {
      char* password = getPass(numToChange, passLength, alfa);

      // Attempt to open the zip file with the generated password
      int found = openZip(path, password);
      free(password);  // Free the password guess memory

      if (found == EXIT_SUCCESS) {
        return EXIT_FAILURE;
      }
    }
  }
  printf("%s\n", path);  // Prints the file path if it doesn't have a password
  return EXIT_SUCCESS;  // Return success if no password was found
}
