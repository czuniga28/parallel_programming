// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/**
 * @struct element
 * @brief Represents an element with various properties.
 */
typedef struct element {
    char* element; /**< The string where the paths are stored. */
    char* password; /**< The password associated with the element. */
} element;

/**
 * @struct dynamicArray_t
 * @brief Represents a dynamic array composed by elements.
 */
typedef struct dynamicArray_t {
    size_t capacityOfArray; /**< The capacity of the dynamic array. */
    size_t count; /**< The current count of elements in the array. */
    element* dynamicArrayInner; /**< Pointer to the dynamic array elements. */
} dynamicArray_t;

/**
 * @brief Initializes a dynamic array.
 *
 * @param array Pointer to the dynamic array to be initialized.
 */
void dynamicArrayInit(dynamicArray_t* array);

/**
 * @brief Appends a string to the dynamic array.
 *
 * @param array Pointer to the dynamic array to which the string is appended.
 * @param string The string to be appended.
 * @return The index where the string is appended.
 */
size_t dynamicArrayAppend(dynamicArray_t* array, char* string);

/**
 * @brief Finalizes a dynamic array, releasing its resources.
 *
 * @param array Pointer to the dynamic array to be finalized.
 */
void dynamicArrayFinalize(dynamicArray_t* array);

#endif  // DYNAMICARRAY_H
