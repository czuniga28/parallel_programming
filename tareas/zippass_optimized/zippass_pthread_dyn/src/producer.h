// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
/**
 * @file producer.h
 * @brief Header file for the Producer module.
 *
 * This module defines the interface for the producer thread function.
 * 
 */

#ifndef PRODUCER_H
#define PRODUCER_H

/**
 * @brief The producer thread function.
 *
 * This function is responsible for producing the passwords and store them in
 * the buffer.
 *
 * @param data Pointer to the data needed for the producer thread (shared).
 * @return A pointer to NULL.
 */
void* produce(void* data);

#endif  // PRODUCER_H
