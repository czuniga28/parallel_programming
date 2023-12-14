// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
/**
 * @file controller.h
 * @brief Header file for the Controller module.
 *
 * This module defines data structures and functions related to controlling
 * parallel password cracking threads.
 */

/**
 * @struct shared_data
 * @brief Structure to hold shared data among threads.
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "queue.h"
#include "pthread.h"

typedef struct shared_data {
    bool passFound;            /**< indicataes if the password is found. */
    pthread_mutex_t can_access_passFound;/**< Mutex for password search. */
} shared_data_t;

/**
 * @struct private_data
 * @brief Structure to hold private data for individual threads.
 */
typedef struct private_data {
    shared_data_t* shared_data;    /**< Pointer to shared data structure. */
} private_data_t;

/**
 * @brief Run the controller with a specified number of threads.
 *
 * This function initializes and manages a pool of worker threads to perform
 * password cracking tasks in parallel.
 *
 * @param thread_count The number of threads to create.
 * @return 0 on success, -1 on failure.
 */
int controller_run(size_t thread_count);

#endif  // CONTROLLER_H
