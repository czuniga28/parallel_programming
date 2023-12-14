// Copyright 2023 Alberto Rojas <alberto.rojassalazar@ucr.ac.cr> CC-BY 4.0
/**
 * @file queue.h
 * @brief Header file for the Queue module.
 *
 * This module defines a simple thread-safe queue data structure for managing
 * passwords or tasks.
 * 
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <stdio.h>

/**
 * @struct queue_element
 * @brief Structure representing an element in the queue.
 */
typedef struct queue_element {
    char* password;               /**< Stores the generated password. */
    struct queue_element* next;  /**< Pointer to the next element. */
} queue_element_t;

/**
 * @struct queue
 * @brief Structure representing the queue itself.
 */
typedef struct queue {
    queue_element_t* head;            /**< Pointer to the head of the queue. */
    queue_element_t* tail;            /**< Pointer to the tail of the queue. */
    sem_t* can_consume;               /**< Semaphore for consumption control. */
    pthread_mutex_t* can_modify;      /**< Mutex for modifying the queue. */
} queue_t;

/**
 * @brief Initialize a queue.
 *
 * This function initializes a queue, preparing it for use.
 *
 * @param queue Pointer to the queue to be initialized.
 */
void queue_init(queue_t* queue);

/**
 * @brief Enqueue a password or task into the queue.
 *
 * This function adds a password or task to the end of the queue.
 *
 * @param queue Pointer to the queue.
 * @param text The password or task to enqueue.
 */
void queue_queue(queue_t* queue, char* text);

/**
 * @brief Dequeue an element from the queue.
 *
 * This function removes and returns the first element from the queue.
 *
 * @param queue Pointer to the queue.
 * @return The password or task removed from the queue.
 */
char* queue_dequeue(queue_t* queue);

/**
 * @brief Destroy a queue.
 *
 * This function deallocates the memory used by the queue and its elements.
 *
 * @param queue Pointer to the queue to be destroyed.
 */
void queue_destroy(queue_t* queue);

/**
 * @brief Check if the queue is empty.
 *
 * This function checks if the queue is empty.
 *
 * @param queue Pointer to the queue.
 * @return True if the queue is empty, false otherwise.
 */
bool queue_is_empty(queue_t* queue);

#endif // QUEUE_H
