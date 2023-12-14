// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include <stdbool.h>
#include <stdio.h>
#include "readData.h"
#include "findPassword.h"

int main() {
  struct dynamicArray_t array;
  dynamicArrayInit(&array);  // Initialize the dynamic array

  char* alfa = (char*)calloc(50, sizeof(char));  // Allocate memory for alfa
  size_t maxNum;
  fscanf(stdin, "%s %zu", alfa, &maxNum);  // Read alfa and maxNum from input

  size_t cont = 0;

  while (true) {
    // Allocate memory for filePath
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
