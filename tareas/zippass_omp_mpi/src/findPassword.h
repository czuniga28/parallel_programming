// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#ifndef FINDPASSWORD_H
#define FINDPASSWORD_H

#include "dynamicArray.h"
#include "readData.h"
#include <stddef.h>

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
 * @brief Attempts to force open a ZIP file using password combinations.
 * @param maxSizePassword The maximum size that the password can have
 * @param alfa The character array containing possible characters 
 * for the password.
 * @return The number of attempts made before successful opening
 */
size_t forceZip(size_t maxSizePassword, char* alfa, char* path);

#endif  // FINDPASSWORD_H
