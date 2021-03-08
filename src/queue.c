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

#include <stdlib.h>
#include <string.h>

#include "queue.h"

queue_t queue_new(size_t element_size) {
    return queue_new_with_capacity(UNILIB_QUEUE_DEFAULT_CAPACITY, element_size);
}

queue_ptr queue_new_ptr(size_t element_size) {
    return queue_new_ptr_with_capacity(UNILIB_QUEUE_DEFAULT_CAPACITY, element_size);
}

queue_t queue_new_with_capacity(size_t capacity, size_t element_size) {
    queue_t queue;
    queue.elements = malloc(capacity * sizeof(void *));
    queue.capacity = capacity;
    queue.len = 0;
    queue.element_size = element_size;
    memset(queue.elements, 0, queue.capacity * sizeof(void *));
    return queue;
}

queue_ptr queue_new_ptr_with_capacity(size_t capacity, size_t element_size) {
    queue_ptr queue = malloc(sizeof(queue_t));
    if (queue == NULL) {
        return NULL;
    }
    queue->elements = malloc(capacity * sizeof(void *));
    queue->capacity = capacity;
    queue->len = 0;
    queue->element_size = element_size;
    memset(queue->elements, 0, queue->capacity * sizeof(void *));
    return queue;
}

void * queue_front(queue_ptr queue) {
    return queue->len != 0 ? queue->elements[0] : NULL;
}

void * queue_push_front(queue_ptr queue, void * elem) {
    // if the queue is full, allocate for one more element
    if (queue->len == queue->capacity) {
        queue->capacity += 1;
        void * elements_new = realloc(queue->elements, queue->capacity * sizeof(void *));
        if (elements_new == NULL) {
            return elem;
        }
        queue->elements = elements_new;
    }
    memmove(queue->elements + sizeof(void *), queue->elements, queue->len);
    queue->elements[0] = elem;
    queue->len += 1;
    return NULL;
}

void * queue_push_front_copy(queue_ptr queue, void * elem) {
    void * elem_copy = malloc(sizeof(queue->element_size));
    if (elem_copy == NULL) {
        return elem;
    }
    memcpy(elem_copy, elem, queue->element_size);
    if (queue_push_front(queue, elem_copy) != NULL) {
        free(elem_copy);
        return elem;
    }
    return NULL;
}

void * queue_pop_front(queue_ptr queue) {
    if (queue->len == 0) {
        return NULL;
    }
    void * elem = queue->elements[0];
    if (queue->len > 1) {
        memmove(queue->elements, queue->elements + sizeof(void *), queue->len - 1);
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
        queue->capacity += 1;
        void ** elements_new = realloc(queue->elements, queue->capacity * sizeof(void *));
        if (elements_new == NULL) {
            return elem;
        }
        queue->elements = elements_new;
    }
    queue->elements[queue->len] = elem;
    queue->len += 1;
    return NULL;
}

void * queue_push_back_copy(queue_ptr queue, void * elem) {
    void * elem_copy = malloc(sizeof(queue->element_size));
    if (elem_copy == NULL) {
        return elem;
    }
    memcpy(elem_copy, elem, queue->element_size);
    if (queue_push_back(queue, elem_copy) != NULL) {
        free(elem_copy);
        return elem;
    }
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

void queue_empty(queue_ptr queue) {
    if (queue->len == 0) {
        return;
    }
    for (size_t i = 0; i < queue->len; i++) {
        free(queue->elements[i]);
    }
    queue->len = 0;
}

void queue_free(queue_ptr queue) {
    if (queue->len > 0) {
        queue_empty(queue);
    }
    free(queue->elements);
}
