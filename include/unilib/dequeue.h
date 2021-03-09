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

#ifndef UNILIB_DEQUEUE_H
#define UNILIB_DEQUEUE_H

/**
 * @brief Default dequeue capacity.
 */
#define DEQUEUE_DEFAULT_CAPACITY 1

/**
 * Error type return by dequeue functions.
 */
typedef uint8_t dequeue_error_t;

/**
 * No error.
 */
#define DEQUEUE_ERROR_OK                    ((dequeue_error_t) 0)
/**
 * The function was provided with a null pointer.
 */
#define DEQUEUE_ERROR_NULL_POINTER_RECEIVED ((dequeue_error_t) 1)
/**
 * The function could not allocate the required memory.
 */
#define DEQUEUE_ERROR_ALLOC_FAILED          ((dequeue_error_t) 2)
/**
 * The dequeue cannot be resized to a capacity of 0.
 */
#define DEQUEUE_ERROR_ZERO_CAPACITY_RESIZE  ((dequeue_error_t) 3)

/**
 * Check whether the result of a function is okay or not.
 */
#define DEQUEUE_ERROR_IS_OK(err) (err == DEQUEUE_ERROR_OK)

/**
 * @struct dequeue
 * @brief A generic dequeue.
 */
typedef struct dequeue_t {
    // inner list of elements
    void ** elements;
    // the length of the dequeue
    size_t len;
    // the capacity of the dequeue (NOT THE SAME AS LENGTH!)
    size_t capacity;
    // the size of an element
    size_t element_size;
} dequeue_t;

/**
 * @brief Pointer to a generic dequeue.
 */
typedef dequeue_t * dequeue_ptr;

/**
 * @brief Create a new dequeue.
 * @details This calls dequeue_new_with_capacity with the default capacity.
 * @see dequeue_new_with_capacity
 * @see UNILIB_DEQUEUE_DEFAULT_CAPACITY
 *
 * @param dequeue address to the dequeue that should be created
 * @param element_size the size of an element in the dequeue
 *
 * @return DEQUEUE_ERROR_OK on success
 *         DEQUEUE_ERROR_NULL_POINTER_RECEIVED if dequeue is a NULL pointer
 *         DEQUEUE_ERROR_ALLOC_FAILED if the dequeue failed to allocate
 */
dequeue_error_t dequeue_new(dequeue_ptr dequeue, size_t element_size);

/**
 * @brief Create a new dequeue.
 * @details This calls dequeue_new_ptr_with_capacity with the default capacity.
 * @see dequeue_new_ptr_with_capacity
 * @see UNILIB_DEQUEUE_DEFAULT_CAPACITY

 * @param dequeue address where to place the address of the newly-created dequeue
 * @param element_size the size of an element in the dequeue
 *
 * @return DEQUEUE_ERROR_OK on success
 *         DEQUEUE_ERROR_NULL_POINTER_RECEIVED if dequeue is a NULL pointer
 *         DEQUEUE_ERROR_ALLOC_FAILED if the dequeue failed to allocate
 */
dequeue_error_t dequeue_new_ptr(dequeue_ptr * dequeue, size_t element_size);

/**
 * @brief Create a new dequeue.
 * @details This creates a new dequeue with the specified capacity and element size.
 *
 * @param dequeue address to return value
 * @param capacity the capacity of the dequeue
 * @param element_size the size of an element in the dequeue
 *
 * @return DEQUEUE_ERROR_OK on success
 *         DEQUEUE_ERROR_NULL_POINTER_RECEIVED if dequeue is a NULL pointer
 *         DEQUEUE_ERROR_ALLOC_FAILED if the dequeue failed to allocate
 */
dequeue_error_t dequeue_new_with_capacity(dequeue_ptr dequeue, size_t capacity, size_t element_size);

/**
 * @brief Create a new dequeue.
 * @details This creates a new dequeue with the specified capacity and element size.
 *          This function is used for allocating the dequeue entirely on the heap.
 *
 * @param dequeue address to return value
 * @param capacity the capacity of the dequeue
 * @param element_size the size of an element in the dequeue
 *
 * @return DEQUEUE_ERROR_OK on success
 *         DEQUEUE_ERROR_NULL_POINTER_RECEIVED if dequeue is a NULL pointer
 *         DEQUEUE_ERROR_ALLOC_FAILED if the dequeue failed to allocate
 */
dequeue_error_t dequeue_new_ptr_with_capacity(dequeue_ptr * dequeue, size_t capacity, size_t element_size);

/**
 * @brief Get the first element in the dequeue.
 *
 * @param dequeue pointer to the dequeue
 *
 * @return pointer to the element on success
 *         NULL if dequeue is a NULL pointer
 *         NULL if there are no items in the dequeue
 */
void * dequeue_front(dequeue_ptr dequeue);

/**
 * @brief Push an item at the front of the dequeue.
 * @details This function assumes ownership of the data pointed by elem.
 * @see dequeue_push_front_copy
 *
 * @param dequeue pointer to the dequeue
 * @param elem the element to be added to the dequeue.
 *
 * @return DEQUEUE_ERROR_OK on success
 *         DEQUEUE_ERROR_NULL_POINTER_RECEIVED if dequeue is a NULL pointer
 *         DEQUEUE_ERROR_NULL_POINTER_RECEIVED if elem is a NULL pointer
 *         DEQUEUE_ERROR_ALLOC_FAILED if the dequeue failed to allocate more memory for the new item
 */
dequeue_error_t dequeue_push_front(dequeue_ptr dequeue, void * elem);

/**
 * @brief Push an item at the front of the dequeue.
 * @details The element will be copied to a new memory location.
 *          This is suitable if you are pushing an element residing on the stack.
 * @see dequeue_push_front
 *
 * @param dequeue pointer to the dequeue
 * @param elem the element to be added to the dequeue.
 *
 * @return DEQUEUE_ERROR_OK on success
 *         DEQUEUE_ERROR_NULL_POINTER_RECEIVED if dequeue is a NULL pointer
 *         DEQUEUE_ERROR_NULL_POINTER_RECEIVED if elem is a NULL pointer
 *         DEQUEUE_ERROR_ALLOC_FAILED if the dequeue failed to allocate more memory for the new item
 */
dequeue_error_t dequeue_push_front_copy(dequeue_ptr dequeue, void * elem);

/**
 * @brief Pop an item from the front of the dequeue.
 * @details This function does not decrease the capacity of the dequeue.
 *          The dequeue gives up ownership over the memory of the element, so it should be
 *          deallocated when no longer used.
 *
 * @param dequeue pointer to the dequeue
 *
 * @return pointer to the element removed from the dequeue on success
 *         NULL if dequeue is a NULL pointer
 *         NULL if there are no items in the dequeue
 */
void * dequeue_pop_front(dequeue_ptr dequeue);

/**
 * @brief Get the last element in the dequeue.
 *
 * @param dequeue pointer to the dequeue
 *
 * @return pointer to the element on success
 *         NULL if dequeue is a NULL pointer
 *         NULL if there are no items in the dequeue
 */
void * dequeue_back(dequeue_ptr dequeue);

/**
 * @brief Push an item at the back of the dequeue.
 * @details This function assumes ownership of the data pointed by elem.
 * @see dequeue_push_back_copy
 *
 * @param dequeue pointer to the dequeue
 * @param elem the element to be added to the dequeue.
 *
 * @return DEQUEUE_ERROR_OK on success
 *         DEQUEUE_ERROR_NULL_POINTER_RECEIVED if dequeue is a NULL pointer
 *         DEQUEUE_ERROR_NULL_POINTER_RECEIVED if elem is a NULL pointer
 *         DEQUEUE_ERROR_ALLOC_FAILED if the dequeue failed to allocate more memory for the new item
 */
dequeue_error_t dequeue_push_back(dequeue_ptr dequeue, void * elem);

/**
 * @brief Push an item at the back of the dequeue.
 * @details The element will be copied to a new memory location.
 *          This is suitable if you are pushing an element residing on the stack.
 * @see dequeue_push_back
 *
 * @param dequeue pointer to the dequeue
 * @param elem the element to be added to the dequeue.
 *
 * @return DEQUEUE_ERROR_OK on success
 *         DEQUEUE_ERROR_NULL_POINTER_RECEIVED if dequeue is a NULL pointer
 *         DEQUEUE_ERROR_NULL_POINTER_RECEIVED if elem is a NULL pointer
 *         DEQUEUE_ERROR_ALLOC_FAILED if the dequeue failed to allocate more memory for the new item
 */
dequeue_error_t dequeue_push_back_copy(dequeue_ptr dequeue, void * elem);

/**
 * @brief Pop an item from the back of the dequeue.
 * @details This function does not decrease the capacity of the dequeue.
 *          The dequeue gives up ownership over the memory of the element, so it should be
 *          deallocated when no longer used.
 *
 * @param dequeue pointer to the dequeue
 *
 * @return pointer to the element removed from the dequeue on success
 *         NULL if dequeue is a NULL pointer
 *         NULL if there are no items in the dequeue
 */
void * dequeue_pop_back(dequeue_ptr dequeue);

/**
 * Resize a dequeue for the specified capacity.
 * @details Capacity must be at least 1.
 *          If the new capacity is smaller than the older capacity, the surplus items will be
 *          deallocated.
 *
 * @param dequeue pointer to the dequeue
 * @param capacity the new capacity
 *
 * @return DEQUEUE_ERROR_OK on success
 *         DEQUEUE_ERROR_NULL_POINTER_RECEIVED if dequeue is a NULL pointer
 *         DEQUEUE_ERROR_ALLOC_FAILED if memory could not be allocated
 *         DEQUEUE_ERROR_ZERO_CAPACITY_RESIZE if the provided new capacity is 0
 */
dequeue_error_t dequeue_resize(dequeue_ptr dequeue, size_t capacity);

/**
 * @brief Empty a dequeue.
 *
 * @param dequeue pointer to the dequeue
 *
 * @return DEQUEUE_ERROR_OK on success
 *         DEQUEUE_ERROR_NULL_POINTER_RECEIVED if dequeue is a NULL pointer
 */
dequeue_error_t dequeue_empty(dequeue_ptr dequeue);

/**
 * @brief Release the memory used by the dequeue.
 * @details If the dequeue was allocated on the heap, it must be de-allocated manually.
 *
 * @param dequeue pointer to the dequeue
 *
 * @return DEQUEUE_ERROR_OK on success
 *         DEQUEUE_ERROR_NULL_POINTER_RECEIVED if dequeue is a NULL pointer
 */
dequeue_error_t dequeue_free(dequeue_ptr dequeue);

#endif //UNILIB_DEQUEUE_H
