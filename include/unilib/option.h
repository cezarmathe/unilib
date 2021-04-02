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

#ifndef UNILIB_OPTION_H
#define UNILIB_OPTION_H

/**
 * The optional value status.
 */
typedef enum option_status_t {
    OPTION_NONE = 0,
    OPTION_SOME = 1,
} option_status_t;

/**
 * An optional value.
 */
typedef struct option_t {
    option_status_t status;
    void * value;
} option_t;

/**
 * Pointer to an optional value.
 */
typedef option_t * option_ptr;

/**
 * Create a new optional value.
 * @param status the status of the optional value
 * @param value the value (can be NULL if the status is OPTION_NONE)
 * @return an optional value
 */
option_t option_new(option_status_t status, void * value);

/**
 * Create a new optional value, allocated on the heap.
 * @param status the status of the optional value
 * @param value the value (can be NULL if the status is OPTION_NONE)
 * @return an optional value
 */
option_ptr option_new_ptr(option_status_t status, void * value);

/**
 * Create an empty optional value.
 * @return an empty optional value
 */
option_t option_none();

/**
 * Create an empty optional value, allocated on the heap.
 * @return an empty optional value
 */
option_ptr option_ptr_none();

/**
 * Create an optional value with a value inside.
 * @param value the value inside
 * @return a full optional value
 */
option_t option_some(void * value);

/**
 * Create an optional value with a value inside, allocated on the heap.
 * @param value the value inside
 * @return a full optional value
 */
option_ptr option_ptr_some(void * value);

/**
 * Check if an optional value has no value inside.
 * @param option the optional value
 * @return 1 if empty, 0 if full
 */
uint8_t option_is_none(option_ptr option);

/**
 * Check if an optional value has a inside.
 * @param option the optional value
 * @return 1 if full, 0 if empty
 */
uint8_t option_is_some(option_ptr option);

/**
 * Free the memory occupied by an optional value.
 * @param option the optional value
 */
void option_free(option_ptr option);

#endif //UNILIB_OPTION_H
