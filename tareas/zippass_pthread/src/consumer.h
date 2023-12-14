// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
/**
 * @file consumer.h
 * @brief Header file for the Consumer module.
 *
 * This module defines the interface for the consumer thread function.
 */

#ifndef CONSUMER_H
#define CONSUMER_H

/**
 * @brief The consumer thread function.
 *
 * This function is responsible for consuming data from the buffer
 *
 * @param data Pointer to the data needed for the consumer thread (shared).
 * @return A pointer NULL.
 */
void* consume(void* data);

#endif  // CONSUMER_H
