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
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
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

#ifndef UNILIB_ITER_H
#define UNILIB_ITER_H

/**
 * Pointer to the `next` function of an iterator.
 */
typedef void * (* iter_next_ptr)(void *);

/**
 * Pointer to the `free` function of an iterator.
 */
typedef void (* iter_free_ptr)(void *);

/**
 * @struct iter
 * @brief A generic iterator.
 */
typedef struct iter_t {
    // pointer to the data of the iterator
    void * data;
    // pointer to the `next` function of an iterator
    iter_next_ptr next;
    // pointer to the `free` function of an iterator
    iter_free_ptr free;
} iter_t;

/**
 * Pointer to an iterator.
 */
typedef iter_t * iter_ptr;

/**
 * @brief Create a new iterator.
 * @param data pointer to the data of the iterator
 * @param next pointer to the `next` function of the iterator
 * @param free pointer to the `free` function of the iterator
 * @return a new iterator
 */
iter_t iter_new(void * data, iter_next_ptr next, iter_free_ptr free);

/**
 * @brief Create a new iterator, allocated on the heap.
 * @param data pointer to the data of the iterator
 * @param next pointer to the `next` function of the iterator
 * @param free pointer to the `free` function of the iterator
 * @return a new iterator, or NULL if memory could not be allocated
 */
iter_ptr iter_new_ptr(void * data, iter_next_ptr next, iter_free_ptr free);

/**
 * @brief Get the next value in the collection.
 * @param iter pointer to the iterator
 * @return pointer to the element or NULL if none remain
 */
void * iter_next(iter_ptr iter);

/**
 * @brief Advance the iterator by `count` elements.
 * @param iter pointer to the iterator
 * @param count the number of items to advance the iterator by
 * @return the number of items the iterator advanced by
 */
size_t iter_advance_by(iter_ptr iter, size_t count);

/**
 * @brief Consume the iterator, returning the number of items.
 * @param iter pointer to the iterator
 * @return the number of items
 */
size_t iter_count(iter_ptr iter);

/**
 * @brief Clear up the memory used by the iterator.
 * @details the iterator pointer must be freed manually if it was created with
 *          `iter_new_ptr`.
 * @param iter the iterator to free
 */
void iter_free(iter_ptr iter);

#endif //UNILIB_ITER_H
