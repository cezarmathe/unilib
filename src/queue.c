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
#include <string.h>

#include "queue.h"

queue_t queue_new() {
    return queue_with_capacity(1);
}

queue_t queue_with_capacity(size_t capacity) {
    queue_t queue;
    queue.elements = malloc(capacity * sizeof(void *));
    queue.capacity = capacity;
    queue.len = 0;
    return queue;
}

void * queue_front(queue_ptr queue) {
    return queue->len != 0 ? queue->elements[0] : NULL;
}

void * queue_push_front(queue_ptr queue, void * elem) {
    // if the queue is full, allocate for one more element
    if (queue->len == queue->capacity) {
        queue->capacity += 1;
        void ** elements_new = realloc(queue->elements, queue->capacity);
        if (elements_new == NULL) {
            return elem;
        }
        queue->elements = elements_new;
    }
    memmove(queue->elements + 1, queue->elements, queue->len);
    queue->elements[0] = elem;
    queue->len += 1;
    return NULL;
}

void * queue_pop_front(queue_ptr queue) {
    if (queue->len == 0) {
        return NULL;
    }
    void * elem = queue->elements[0];
    if (queue->len > 1) {
        memmove(queue->elements, queue->elements + 1, queue->len - 1);
    }
    queue->elements[queue->len - 1] = NULL;
    queue->len -= 1;
    return elem;
}

void * queue_back(queue_ptr queue) {
    return queue->len != 0 ? queue->elements[queue->len - 1] : NULL;
}

void * queue_push_back(queue_ptr queue, void * elem) {
    // if the queue is full, allocate for one more element
    if (queue->len == queue->capacity) {
        void ** elements_new = realloc(queue->elements, queue->capacity + 1);
        if (elements_new == NULL) {
            return elem;
        }
        queue->capacity += 1;
        queue->elements = elements_new;
    }
    queue->elements[queue->len] = elem;
    queue->len += 1;
    return NULL;
}

void * queue_pop_back(queue_ptr queue) {
    if (queue->len == 0) {
        return NULL;
    }
    void * elem = queue->elements[queue->len - 1];
    queue->elements[queue->len - 1] = NULL;
    queue->len -= 1;
    return elem;
}

void queue_free(queue_ptr queue) {
    for (size_t i = 0; i < queue->capacity; i++) {
        free(queue->elements[i]);
    }
    free(queue->elements);
}

queue_iter_t queue_iter(queue_ptr queue) {
    queue_iter_t iter;
    iter.queue = queue;
    iter.index = 0;
    return iter;
}

uint8_t queue_iter_has_next(queue_iter_ptr iter) {
    return iter->index < iter->queue->len;
}

void * queue_iter_next(queue_iter_ptr iter) {
    if (iter->index >= iter->queue->len) {
        return NULL;
    }
    void * elem = iter->queue->elements[iter->index];
    iter->index += 1;
    return elem;
}
