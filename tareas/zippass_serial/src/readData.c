// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#define _GNU_SOURCE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <zip.h>

#include "readData.h"

// Function to open and read files from a zip archive
int openZip(char* filePath, char* filePassword) {
  int errorp = 0;
  zip_t* arch = NULL;
  char* path = filePath;
  struct zip_stat finfo;

  arch = zip_open(path, 0, &errorp);  // Open the ZIP archive
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

  // Open and read the file from the ZIP archive
  zip_file_t* fd = zip_fopen_index_encrypted(arch, 0, 0, filePassword);
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

  printf("%s  %s\n", path, filePassword);  // Print file information and content

  free(txt);  // Free memory allocated for file content
  zip_close(arch);  // Close the ZIP archive
  zip_fclose(fd);  // Close the ZIP archive


  return EXIT_SUCCESS;
}
