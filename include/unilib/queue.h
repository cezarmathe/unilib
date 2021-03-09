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
#define QUEUE_DEFAULT_CAPACITY 1

/**
 * Error type return by queue functions.
 */
typedef uint8_t queue_error_t;

/**
 * No error.
 */
#define QUEUE_ERROR_OK                    ((queue_error_t) 0)
/**
 * The function was provided with a null pointer.
 */
#define QUEUE_ERROR_NULL_POINTER_RECEIVED ((queue_error_t) 1)
/**
 * The function could not allocate the required memory.
 */
#define QUEUE_ERROR_ALLOC_FAILED          ((queue_error_t) 2)
/**
 * The queue cannot be resized to a capacity of 0.
 */
#define QUEUE_ERROR_ZERO_CAPACITY_RESIZE  ((queue_error_t) 3)

/**
 * Check whether the result of a function is okay or not.
 */
#define QUEUE_ERROR_IS_OK(err) (err == QUEUE_ERROR_OK)

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
 * @details This calls queue_new_with_capacity with the default capacity.
 * @see queue_new_with_capacity
 * @see UNILIB_QUEUE_DEFAULT_CAPACITY
 *
 * @param queue address to the queue that should be created
 * @param element_size the size of an element in the queue
 *
 * @return QUEUE_ERROR_OK on success
 *         QUEUE_ERROR_NULL_POINTER_RECEIVED if queue is a NULL pointer
 *         QUEUE_ERROR_ALLOC_FAILED if the queue failed to allocate
 */
queue_error_t queue_new(queue_ptr queue, size_t element_size);

/**
 * @brief Create a new queue.
 * @details This calls queue_new_ptr_with_capacity with the default capacity.
 * @see queue_new_ptr_with_capacity
 * @see UNILIB_QUEUE_DEFAULT_CAPACITY

 * @param queue address where to place the address of the newly-created queue
 * @param element_size the size of an element in the queue
 *
 * @return QUEUE_ERROR_OK on success
 *         QUEUE_ERROR_NULL_POINTER_RECEIVED if queue is a NULL pointer
 *         QUEUE_ERROR_ALLOC_FAILED if the queue failed to allocate
 */
queue_error_t queue_new_ptr(queue_ptr * queue, size_t element_size);

/**
 * @brief Create a new queue.
 * @details This creates a new queue with the specified capacity and element size.
 *
 * @param queue address to return value
 * @param capacity the capacity of the queue
 * @param element_size the size of an element in the queue
 *
 * @return QUEUE_ERROR_OK on success
 *         QUEUE_ERROR_NULL_POINTER_RECEIVED if queue is a NULL pointer
 *         QUEUE_ERROR_ALLOC_FAILED if the queue failed to allocate
 */
queue_error_t queue_new_with_capacity(queue_ptr queue, size_t capacity, size_t element_size);

/**
 * @brief Create a new queue.
 * @details This creates a new queue with the specified capacity and element size.
 *          This function is used for allocating the queue entirely on the heap.
 *
 * @param queue address to return value
 * @param capacity the capacity of the queue
 * @param element_size the size of an element in the queue
 *
 * @return QUEUE_ERROR_OK on success
 *         QUEUE_ERROR_NULL_POINTER_RECEIVED if queue is a NULL pointer
 *         QUEUE_ERROR_ALLOC_FAILED if the queue failed to allocate
 */
queue_error_t queue_new_ptr_with_capacity(queue_ptr * queue, size_t capacity, size_t element_size);

/**
 * @brief Get the first element in the queue.
 *
 * @param queue pointer to the queue
 *
 * @return pointer to the element on success
 *         NULL if queue is a NULL pointer
 *         NULL if there are no items in the queue
 */
void * queue_front(queue_ptr queue);

/**
 * @brief Push an item at the front of the queue.
 * @details This function assumes ownership of the data pointed by elem.
 * @see queue_push_front_copy
 *
 * @param queue pointer to the queue
 * @param elem the element to be added to the queue.
 *
 * @return QUEUE_ERROR_OK on success
 *         QUEUE_ERROR_NULL_POINTER_RECEIVED if queue is a NULL pointer
 *         QUEUE_ERROR_NULL_POINTER_RECEIVED if elem is a NULL pointer
 *         QUEUE_ERROR_ALLOC_FAILED if the queue failed to allocate more memory for the new item
 */
queue_error_t queue_push_front(queue_ptr queue, void * elem);

/**
 * @brief Push an item at the front of the queue.
 * @details The element will be copied to a new memory location.
 *          This is suitable if you are pushing an element residing on the stack.
 * @see queue_push_front
 *
 * @param queue pointer to the queue
 * @param elem the element to be added to the queue.
 *
 * @return QUEUE_ERROR_OK on success
 *         QUEUE_ERROR_NULL_POINTER_RECEIVED if queue is a NULL pointer
 *         QUEUE_ERROR_NULL_POINTER_RECEIVED if elem is a NULL pointer
 *         QUEUE_ERROR_ALLOC_FAILED if the queue failed to allocate more memory for the new item
 */
queue_error_t queue_push_front_copy(queue_ptr queue, void * elem);

/**
 * @brief Pop an item from the front of the queue.
 * @details This function does not decrease the capacity of the queue.
 *          The queue gives up ownership over the memory of the element, so it should be
 *          deallocated when no longer used.
 *
 * @param queue pointer to the queue
 *
 * @return pointer to the element removed from the queue on success
 *         NULL if queue is a NULL pointer
 *         NULL if there are no items in the queue
 */
void * queue_pop_front(queue_ptr queue);

/**
 * @brief Get the last element in the queue.
 *
 * @param queue pointer to the queue
 *
 * @return pointer to the element on success
 *         NULL if queue is a NULL pointer
 *         NULL if there are no items in the queue
 */
void * queue_back(queue_ptr queue);

/**
 * @brief Push an item at the back of the queue.
 * @details This function assumes ownership of the data pointed by elem.
 * @see queue_push_back_copy
 *
 * @param queue pointer to the queue
 * @param elem the element to be added to the queue.
 *
 * @return QUEUE_ERROR_OK on success
 *         QUEUE_ERROR_NULL_POINTER_RECEIVED if queue is a NULL pointer
 *         QUEUE_ERROR_NULL_POINTER_RECEIVED if elem is a NULL pointer
 *         QUEUE_ERROR_ALLOC_FAILED if the queue failed to allocate more memory for the new item
 */
queue_error_t queue_push_back(queue_ptr queue, void * elem);

/**
 * @brief Push an item at the back of the queue.
 * @details The element will be copied to a new memory location.
 *          This is suitable if you are pushing an element residing on the stack.
 * @see queue_push_back
 *
 * @param queue pointer to the queue
 * @param elem the element to be added to the queue.
 *
 * @return QUEUE_ERROR_OK on success
 *         QUEUE_ERROR_NULL_POINTER_RECEIVED if queue is a NULL pointer
 *         QUEUE_ERROR_NULL_POINTER_RECEIVED if elem is a NULL pointer
 *         QUEUE_ERROR_ALLOC_FAILED if the queue failed to allocate more memory for the new item
 */
queue_error_t queue_push_back_copy(queue_ptr queue, void * elem);

/**
 * @brief Pop an item from the back of the queue.
 * @details This function does not decrease the capacity of the queue.
 *          The queue gives up ownership over the memory of the element, so it should be
 *          deallocated when no longer used.
 *
 * @param queue pointer to the queue
 *
 * @return pointer to the element removed from the queue on success
 *         NULL if queue is a NULL pointer
 *         NULL if there are no items in the queue
 */
void * queue_pop_back(queue_ptr queue);

/**
 * Resize a queue for the specified capacity.
 * @details Capacity must be at least 1.
 *          If the new capacity is smaller than the older capacity, the surplus items will be
 *          deallocated.
 *
 * @param queue pointer to the queue
 * @param capacity the new capacity
 *
 * @return QUEUE_ERROR_OK on success
 *         QUEUE_ERROR_NULL_POINTER_RECEIVED if queue is a NULL pointer
 *         QUEUE_ERROR_ALLOC_FAILED if memory could not be allocated
 *         QUEUE_ERROR_ZERO_CAPACITY_RESIZE if the provided new capacity is 0
 */
queue_error_t queue_resize(queue_ptr queue, size_t capacity);

/**
 * @brief Empty a queue.
 *
 * @param queue pointer to the queue
 *
 * @return QUEUE_ERROR_OK on success
 *         QUEUE_ERROR_NULL_POINTER_RECEIVED if queue is a NULL pointer
 */
queue_error_t queue_empty(queue_ptr queue);

/**
 * @brief Release the memory used by the queue.
 * @details If the queue was allocated on the heap, it must be de-allocated manually.
 *
 * @param queue pointer to the queue
 *
 * @return QUEUE_ERROR_OK on success
 *         QUEUE_ERROR_NULL_POINTER_RECEIVED if queue is a NULL pointer
 */
queue_error_t queue_free(queue_ptr queue);

#endif //UNILIB_QUEUE_H
