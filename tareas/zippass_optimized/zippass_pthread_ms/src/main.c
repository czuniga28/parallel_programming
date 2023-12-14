// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
#include "readData.h"
#include "findPassword.h"
#include "controller.h"

int main(int argc, char* argv[]) {
  // create thread_count = system_num_threads()
  size_t thread_count = 0;
  if (argc == 2) {
    sscanf(argv[1], "%" SCNu64, &thread_count);
    controller_run(thread_count);
  } else {
    fprintf(stderr, "not expected arguments\n");
  }

  struct dynamicArray_t array;
  dynamicArrayInit(&array);  // Initialize the dynamic array

  shared_data_t* shared_data = calloc(1, sizeof(shared_data_t));
  // create can_access_pass_found = mutex_init()
  pthread_mutex_init(&shared_data->can_access_passFound, /*attr*/ NULL);

  // create alpha[]
  char* alfa = (char*)calloc(50, sizeof(char));  // Allocate memory for alfa

  // create alpha_len
  size_t maxNum;
  fscanf(stdin, "%s %zu", alfa, &maxNum);  // Read alfa and maxNum from input

  size_t cont = 0;

  while (true) {
    // create file_path[]
    char* filePath = (char*)calloc(50, sizeof(char));
    int size = fscanf(stdin, "%s", filePath);  // Read file path from input
    if (size != 1) {
      free(filePath);
      break;  // Exit the loop if reading fails
    }
    dynamicArrayAppend(&array, filePath);  // Append file path to dynamic array

    cont++;
    free(filePath);
  }

  for (size_t i = 0; i < array.count; i++) {
    char* path = array.dynamicArrayInner[i].element;  // Get file path
    forceZip(maxNum, alfa, path);
  }

  free(alfa);
  dynamicArrayFinalize(&array);
  return 0;
}
