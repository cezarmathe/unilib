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

#include "dequeue.h"

#include <assert.h>
#include <string.h>

#define SIZES_LEN 5
size_t sizes[SIZES_LEN] = {
        sizeof(int),
        sizeof(double),
        sizeof(float),
        sizeof(char),
        sizeof(char *)};

void test_dequeue_new(dequeue_ptr dequeue, size_t capacity, size_t element_size) {
    assert(dequeue->elements != NULL);
    assert(*dequeue->elements == NULL);
    assert(dequeue->capacity == capacity);
    assert(dequeue->len == 0);
    assert(dequeue->element_size == element_size);
}

int main() {
    for (int i = 0; i < SIZES_LEN; i++) {
        dequeue_t dequeue = dequeue_new(sizes[i]);
        test_dequeue_new(&dequeue, DEQUEUE_DEFAULT_CAPACITY, sizes[i]);
        dequeue_free(&dequeue);
    }
    for (int i = 0; i < SIZES_LEN; i++) {
        dequeue_ptr dequeue = dequeue_new_ptr(sizes[i]);
        test_dequeue_new(dequeue, DEQUEUE_DEFAULT_CAPACITY, sizes[i]);
        dequeue_free(dequeue);
        free(dequeue);
    }
    for (int i = 0; i < SIZES_LEN; i++) {
        size_t capacity = 1024;
        dequeue_t dequeue = dequeue_new_with_capacity(capacity, sizes[i]);
        test_dequeue_new(&dequeue, capacity, sizes[i]);
        dequeue_free(&dequeue);
    }
    for (int i = 0; i < SIZES_LEN; i++) {
        size_t capacity = 1024;
        dequeue_ptr dequeue = dequeue_new_ptr_with_capacity(capacity, sizes[i]);
        test_dequeue_new(dequeue, capacity, sizes[i]);
        dequeue_free(dequeue);
        free(dequeue);
    }

    dequeue_t dequeue = dequeue_new(sizeof(int));
    for (int i = 0; i < 1024; i++) {
        assert(dequeue_push_back_copy(&dequeue, &i) == NULL);
    }
    assert(dequeue.len == 1024);
    assert(*((int *) dequeue_front(&dequeue)) == 0);
    assert(*((int *) dequeue_back(&dequeue)) == 1023);
    dequeue_empty(&dequeue);
    assert(dequeue.len == 0);
    dequeue_free(&dequeue);
}
