// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include <stdbool.h>
#include <stdio.h>
#include "readData.h"
#include "findPassword.h"

int main() {
  struct dynamicArray_t array;
  dynamicArrayInit(&array);  // Initialize the dynamic array

  char alfa[50];
  size_t maxNum;

  if (fscanf(stdin, "%49s %zu", alfa, &maxNum) != 2) {
    fprintf(stderr, "Error reading alfa and maxNum\n");
    return 1;
  }

  char filePath[50];
  size_t cont = 0;

  while (fscanf(stdin, "%49s", filePath) == 1) {
    dynamicArrayAppend(&array, filePath);  // Append file path to dynamic array
    cont++;
  }

  for (size_t i = 0; i < array.count; i++) {
    char* path = array.dynamicArrayInner[i].element;  // Get file path
    forceZip(maxNum, alfa, path);
  }

  dynamicArrayFinalize(&array);
  return 0;
}
