// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#ifndef FINDPASSWORD_H
#define FINDPASSWORD_H

#include "controller.h"
/**
 * @brief Retrieves a password based on specified conditions.
 * @param numToChange The number of characters to change in the\ password.
 * @param passLength The length of the password to generate.
 * @param alfa The character array containing possible characters 
 * for the password.
 * @return The generated password.
 */
char* getPass(size_t numToChange, size_t passLength, char* alfa);

/**
 * @brief Opens a ZIP file and extracts data into the dynamic array.
 * @param filePath The character array that contains the path to be  used.
 * @param filePassword The password given to be tried on the file.
 * @return An integer indicating the success or failure of the operation.
 *         - EXIT_SUCCESS: Success
 *         - EXIT_FAILURE: Error code
 */
int openZip(char* filePath, char* filePassword, shared_data_t* shared);

#endif  // FINDPASSWORD_H
