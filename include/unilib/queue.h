/* MIT License
 *
 * Copyright (c) 2021 Armand-Cezar Mathe <me@cezarmathe.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdint.h>
#include <stdlib.h>

#ifndef UNILIB_QUEUE_H
#define UNILIB_QUEUE_H

/**
 * A generic queue.
 */
typedef struct queue_t {
    // inner list of elements
    void ** elements;
    // the length of the queue
    size_t len;
    // the capacity of the queue (NOT THE SAME AS LENGTH!)
    size_t capacity;
    // the size of each element
    size_t element_size;
} queue_t;

/**
 * Pointer to a generic queue.
 */
typedef queue_t * queue_ptr;

/**
 * Create a new queue.
 *
 * The queue is created with a capacity of 1.
 */
queue_t queue_new();

/**
 * Create a new queue with a certain capacity.
 */
queue_t queue_with_capacity(size_t capacity);

/**
 * Get the first element in the queue.
 *
 * @param queue the queue
 *
 * @return the element, or NULL if there are none.
 */
void * queue_front(queue_ptr queue);

/**
 * Push an item at the front of the queue.
 *
 * Each element MUST be dynamically allocated.
 *
 * Returns the element if no memory could be allocated for it.
 */
void * queue_push_front(queue_ptr queue, void * elem);

/**
 * Pop an item from the front of the queue.
 *
 * This function does not decrease the capacity of the queue.
 *
 * Returns the element, or NULL if there are no elements.
 */
void * queue_pop_front(queue_ptr queue);

/**
 * Get the last element in the queue.
 *
 * Returns the element, or NULL if there are none.
 */
void * queue_back(queue_ptr queue);

/**
 * Push an item at the back of the queue.
 *
 * Each element MUST be dynamically allocated.
 *
 * Returns the element if no memory could be allocated for it.
 */
void * queue_push_back(queue_ptr queue, void * elem);

/**
 * Pop an item from the back of the queue.
 *
 * This function does not decrease the capacity of the queue.
 *
 * Returns the element, or NULL if there are no elements.
 */
void * queue_pop_back(queue_ptr queue);

/**
 * Release the internal memory of the queue.
 */
void queue_free(queue_ptr queue);

/**
 * An iterator over a queue.
 */
typedef struct queue_iter_t {
    queue_ptr queue;
    size_t index;
} queue_iter_t;

/**
 * Pointer to a queue iterator.
 */
typedef queue_iter_t * queue_iter_ptr;

/**
 * Checks whether the iterator has another value.
 *
 * Returns true if there are more elements, or false otherwise.
 */
uint8_t queue_iter_has_next(queue_iter_ptr iter);

/**
 * Returns the next element in the queue.
 *
 * Returns NULL if there are no elements left.
 */
void * queue_iter_next(queue_iter_ptr iter);

/**
 * Get an iterator over a queue.
 */
queue_iter_t queue_iter(queue_ptr queue);

#endif //UNILIB_QUEUE_H
