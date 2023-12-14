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
    size_t thread_count;       /**< Number of threads. */
    size_t maxSizePassword;    /**< Maximum size of the password. */
    char* alfa;                /**< Alphabet for password generation. */
    char* path;                /**< Path to the zip file. */
    queue_t* queue;            /**< Pointer to the shared queue for tasks. */
    pthread_mutex_t can_search_pass;/**< Mutex for password search. */
    pthread_mutex_t can_open_zip;/**< Mutex for coordinating zip file access. */
    sem_t can_consume;         /**< Semaphore for task consumption. */
    char* password;            /**< Pointer to the discovered password. */
} shared_data_t;

/**
 * @struct private_data
 * @brief Structure to hold private data for individual threads.
 */
typedef struct private_data {
    size_t thread_number;          /**< Thread number or identifier. */
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
