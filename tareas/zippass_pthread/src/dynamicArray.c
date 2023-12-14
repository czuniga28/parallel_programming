// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dynamicArray.h"

// Declares unction to increase the capacity of the dynamic array
size_t dynamicArrayAddCapacity(dynamicArray_t* array);

// Initialize the dynamic array
void dynamicArrayInit(dynamicArray_t* array) {
  assert(array);  // Make sure the input pointer is not NULL
  array->capacityOfArray = 0;   // Initalize the capacity of the array on 0
  array->count = 0;  // Initalize the count on 0
  array->dynamicArrayInner = NULL;  // Initialize the inner array to NULL
}

// Append a new element to the dynamic array
size_t dynamicArrayAppend(dynamicArray_t* array, char* texto) {
  assert(array);  // Make sure the input pointer is not NULL
  size_t error = EXIT_SUCCESS;

  // Check if the array is full and needs a capacity expansion
  if (array->count == array->capacityOfArray) {
    dynamicArrayAddCapacity(array);  // Increase array capacity
  }

  // Allocate memory for a new string and copy the given text
  char* newStr = (char*)calloc(50, sizeof(char));
  strcpy(newStr, texto);

  if (newStr == NULL) {
    return EXIT_FAILURE;  // Memory allocation failed
  }

  // If no error occurred and memory allocation was successful
  if (error == EXIT_SUCCESS) {
    // Add the new string to the dynamic array and update count
    array->dynamicArrayInner[array->count].element = newStr;
    array->dynamicArrayInner[array->count].password = NULL;
    array->count++;
  }

  return error;  // Return error status
}

// Function to increase the capacity of the dynamic array
size_t dynamicArrayAddCapacity(dynamicArray_t* array) {
  assert(array);  // Make sure the input pointer is not NULL
  size_t error = EXIT_SUCCESS;

  // Calculate new capacity as x10 the current capacity
  size_t newCapacity = 10*(array->capacityOfArray ? array->capacityOfArray : 1);

  // Reallocate memory to increase the capacity of the inner array
  element* newArray = (element*) realloc(array->dynamicArrayInner,
    newCapacity * sizeof(element));

  if (newArray) {
    array->capacityOfArray = newCapacity;  // Update the array capacity
    array->dynamicArrayInner = newArray;  // Update the inner array pointer
  } else {
    error = EXIT_FAILURE;  // Memory reallocation failed
  }
  return error;  // Return error status
}

// Make sure the input pointer is not NULL
void dynamicArrayFinalize(dynamicArray_t* array) {
  assert(array);  // Make sure the input pointer is not NULL
  if (array == NULL) {
    return;  // If the array is NULL, there's nothing to finalize
  }

  // Free allocated memory for each element's string and additional data
  for (size_t i = 0; i < array->count; i++) {
    free(array->dynamicArrayInner[i].element);
    if (array->dynamicArrayInner[i].password != NULL) {
      free(array->dynamicArrayInner[i].password);
    }
  }
  // Reset the count and capacity, and free the inner array
  array->count = 0;
  array->count = 0;
  array->capacityOfArray = 0;
  free(array->dynamicArrayInner);  // Frees the memory occuped by the D.Array
  array->dynamicArrayInner = NULL;  // Set the inner array pointer to NULL
}

