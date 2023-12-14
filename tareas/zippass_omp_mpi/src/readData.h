// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#ifndef READDATA_H
#define READDATA_H

#include "dynamicArray.h"

/**
 * @brief Stores data into a dynamic array. *
 * @return The dynamic array containing the stored data.
 */
dynamicArray_t storeData();

/**
 * @brief Opens a ZIP file and extracts data into the dynamic array.
 * @param filePath The character array that contains the path to be  used.
 * @param filePassword The password given to be tried on the file.
 * @return An integer indicating the success or failure of the operation.
 *         - EXIT_SUCCESS: Success
 *         - EXIT_FAILURE: Error code
 */
int openZip(char* filePath, char* filePassword);

#endif  // READDATA_H
