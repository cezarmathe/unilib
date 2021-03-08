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
 * @brief Default queue capacity.
 */
#define UNILIB_QUEUE_DEFAULT_CAPACITY 1

/**
 * @struct queue
 * @brief A generic queue.
 */
typedef struct queue_t {
    // inner list of elements
    void ** elements;
    // the length of the queue
    size_t len;
    // the capacity of the queue (NOT THE SAME AS LENGTH!)
    size_t capacity;
    // the size of an element
    size_t element_size;
} queue_t;

/**
 * @brief Pointer to a generic queue.
 */
typedef queue_t * queue_ptr;

/**
 * @brief Create a new queue.
 *
 * @details The queue is created with a capacity of 1.
 */
queue_t queue_new(size_t element_size);

/**
 * @brief Create a new queue.
 *
 * @details Allocated on the heap. The queue is created with a capacity of 1.
 */
queue_ptr queue_new_ptr(size_t element_size);

/**
 * @brief Create a new queue with a certain capacity.
 */
queue_t queue_new_with_capacity(size_t capacity, size_t element_size);

/**
 * Create a new queue with a certain capacity, allocated on the heap.
 */
queue_ptr queue_new_ptr_with_capacity(size_t capacity, size_t element_size);

/**
 * Get the first element in the queue.
 *
 * @param queue pointer to the queue
 *
 * @return pointer to the first element or NULL if there are none.
 */
void * queue_front(queue_ptr queue);

/**
 * @brief Push an item at the front of the queue.
 *
 * @details The element must be allocated on the heap.
 *
 * @param elem the element to be added to the queue.
 *
 * @return NULL if successful or the pointer to the element if unsuccessful.
 */
void * queue_push_front(queue_ptr queue, void * elem);

/**
 * @brief Push an item at the front of the queue.
 *
 * @details The element will be copied to a new memory location.
 *          This is suitable if you are pushing an element residing on the stack.
 *
 * @param elem the element to be added to the queue.
 *
 * @return NULL if successful or the pointer to the element if unsuccessful.
 */
void * queue_push_front_copy(queue_ptr queue, void * elem);

/**
 * @brief Pop an item from the front of the queue.
 *
 * @details This function does not decrease the capacity of the queue.
 *          The item must be de-allocated.
 *
 * @return the element, or NULL if there are no elements.
 */
void * queue_pop_front(queue_ptr queue);

/**
 * Get the last element in the queue.
 *
 * @param queue pointer to the queue
 *
 * @return pointer to the last element or NULL if there are none.
 */
void * queue_back(queue_ptr queue);

/**
 * @brief Push an item at the back of the queue.
 *
 * @details The element must be allocated on the heap.
 *
 * @param elem the element to be added to the queue.
 *
 * @return NULL if successful or the pointer to the element if unsuccessful.
 */
void * queue_push_back(queue_ptr queue, void * elem);

/**
 * @brief Push an item at the back of the queue.
 *
 * @details The element will be copied to a new memory location.
 *          This is suitable if you are pushing an element residing on the stack.
 *
 * @param elem the element to be added to the queue.
 *
 * @return NULL if successful or the pointer to the element if unsuccessful.
 */
void * queue_push_back_copy(queue_ptr queue, void * elem);

/**
 * @brief Pop an item from the back of the queue.
 *
 * @details This function does not decrease the capacity of the queue.
 *          The item must be de-allocated.
 *
 * @return the element, or NULL if there are no elements.
 */
void * queue_pop_back(queue_ptr queue);

/**
 * @brief Empty a queue.
 *
 * @param queue the queue
 */
void queue_empty(queue_ptr queue);

/**
 * @brief Release the memory used by the queue.
 *
 * @details If the queue was allocated on the heap, it must be de-allocated manually.
 */
void queue_free(queue_ptr queue);

#endif //UNILIB_QUEUE_H
