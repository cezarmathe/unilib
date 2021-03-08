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

#include "queue.h"

#include <assert.h>
#include <string.h>

#define SIZES_LEN 5
size_t sizes[SIZES_LEN] = {
        sizeof(int),
        sizeof(double),
        sizeof(float),
        sizeof(char),
        sizeof(char *)};

void test_queue_new(queue_ptr queue, size_t capacity, size_t element_size) {
    assert(queue->elements != NULL);
    assert(*queue->elements == NULL);
    assert(queue->capacity == capacity);
    assert(queue->len == 0);
    assert(queue->element_size == element_size);
}

int main() {
    for (int i = 0; i < SIZES_LEN; i++) {
        queue_t queue = queue_new(sizes[i]);
        test_queue_new(&queue, UNILIB_QUEUE_DEFAULT_CAPACITY, sizes[i]);
        queue_free(&queue);
    }
    for (int i = 0; i < SIZES_LEN; i++) {
        queue_ptr queue = queue_new_ptr(sizes[i]);
        test_queue_new(queue, UNILIB_QUEUE_DEFAULT_CAPACITY, sizes[i]);
        queue_free(queue);
        free(queue);
    }
    for (int i = 0; i < SIZES_LEN; i++) {
        size_t capacity = 1024;
        queue_t queue = queue_new_with_capacity(capacity, sizes[i]);
        test_queue_new(&queue, capacity, sizes[i]);
        queue_free(&queue);
    }
    for (int i = 0; i < SIZES_LEN; i++) {
        size_t capacity = 1024;
        queue_ptr queue = queue_new_ptr_with_capacity(capacity, sizes[i]);
        test_queue_new(queue, capacity, sizes[i]);
        queue_free(queue);
        free(queue);
    }

    queue_t queue = queue_new(sizeof(int));
    for (int i = 0; i < 1024; i++) {
        assert(queue_push_back_copy(&queue, &i) == NULL);
    }
    assert(queue.len == 1024);
    assert(*((int *) queue_front(&queue)) == 0);
    assert(*((int *) queue_back(&queue)) == 1023);
    queue_empty(&queue);
    assert(queue.len == 0);
    queue_free(&queue);
}
