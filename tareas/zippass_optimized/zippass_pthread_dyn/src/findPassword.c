// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <zip.h>

#include "dynamicArray.h"
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

// Function to open and read files from a zip archive
int openZip(char* filePath, char* filePassword, shared_data_t* shared) {
  int errorp = 0;
  zip_t* arch = NULL;
  char* path = filePath;
  struct zip_stat finfo;
  pthread_mutex_lock(&shared->can_open_zip);
  arch = zip_open(path, 0, &errorp);  // Open the ZIP archive
  pthread_mutex_unlock(&shared->can_open_zip);
  if (arch == NULL) {
    fprintf(stderr, "Error abriendo el archivo ZIP\n");
    return -1;
  }

  // Gives information about the first file in the ZIP archive
  zip_stat_init(&finfo);
  zip_stat_index(arch, 0, 0, &finfo);

  // Allocate memory to read the file content
  char* txt = calloc(finfo.size + 1, sizeof(char));
  if (txt == NULL) {
    fprintf(stderr, "Error asignando memoria\n");
    zip_close(arch);
    return -1;
  }

  pthread_mutex_lock(&shared->can_open_zip);
  // Open and read the file from the ZIP archive
  zip_file_t* fd = zip_fopen_index_encrypted(arch, 0, 0, filePassword);
  pthread_mutex_unlock(&shared->can_open_zip);
  if (fd == NULL) {
    free(txt);
    zip_close(arch);
    return EXIT_FAILURE;
  }

  zip_fread(fd, txt, finfo.size);  // Read the file content

  if (strcmp(txt, "CI0117-23a") != 0) {
    free(txt);  // Free memory allocated for file content
    zip_close(arch);  // Close the ZIP archive
    zip_fclose(fd);  // Close the ZIP archive
    return EXIT_FAILURE;
  }

  free(txt);  // Free memory allocated for file content
  zip_close(arch);  // Close the ZIP archive
  zip_fclose(fd);  // Close the ZIP archive


  return EXIT_SUCCESS;
}
