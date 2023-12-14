// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "findPassword.h"

// Generate a password guess based on the given number and alphabet
void getPass(size_t numToChange, size_t passLength, const char* alfa, 
    char* passGuess) {
  size_t tamBase = strlen(alfa);

  for (int i = (int)passLength - 1; i >= 0; i--) {
    passGuess[i] = alfa[numToChange % tamBase];
    numToChange /= tamBase;
  }
  passGuess[passLength] = '\0';   // Terminate the password guess
}

// Brute-force attack on an encrypted zip file
size_t forceZip(size_t maxSizePassword, const char* alfa, const char* path) {
  size_t tamBase = strlen(alfa);

  char* password = (char*)malloc(maxSizePassword + 1);
  if (password == NULL) {
    perror("Failed to allocate memory");
    exit(EXIT_FAILURE);
  }

  for (size_t passLength = 1; passLength <= maxSizePassword; passLength++) {
    size_t con = (size_t)pow(tamBase, passLength);
    for (size_t numToChange = 0; numToChange < con; numToChange++) {
      getPass(numToChange, passLength, alfa, password);
      if (openZip(path, password) == EXIT_SUCCESS) {
        free(password);
        return EXIT_FAILURE;
      }
    }
  }
  free(password);

  printf("%s\n", path);  // Prints the file path if it doesn't have a password
  return EXIT_SUCCESS;  // Return success if no password was found
}