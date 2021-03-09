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

/**
 * Initialize a queue.
 *
 * @details If the passed queue pointer is NULL, this leads to UB!
 *
 * @param queue the queue to initialize
 * @param capacity the capacity of the queue
 * @param element_size the size of each element in the queue
 *
 * @return QUEUE_ERROR_OK if successful
 *         QUEUE_ERROR_NULL_POINTER_RECEIVED if the queue pointer is NULL
 *         QUEUE_ERROR_ALLOC_FAILED if allocating the elements array failed
 */
static queue_error_t queue_init(queue_ptr queue, size_t capacity, size_t element_size) {
    queue->elements = calloc(capacity, sizeof(void *));
    if (queue->elements == NULL) {
        return QUEUE_ERROR_ALLOC_FAILED;
    }
    queue->capacity = capacity;
    queue->len = 0;
    queue->element_size = element_size;
    return QUEUE_ERROR_OK;
}

queue_error_t queue_new(queue_ptr queue, size_t element_size) {
    return queue_new_with_capacity(queue, QUEUE_DEFAULT_CAPACITY, element_size);
}

queue_error_t queue_new_ptr(queue_ptr * queue, size_t element_size) {
    return queue_new_ptr_with_capacity(queue, QUEUE_DEFAULT_CAPACITY, element_size);
}

queue_error_t queue_new_with_capacity(queue_ptr queue, size_t capacity, size_t element_size) {
    if (queue == NULL) {
        return QUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    return queue_init(queue, capacity, element_size);
}

queue_error_t queue_new_ptr_with_capacity(queue_ptr * queue, size_t capacity, size_t element_size) {
    if (queue == NULL) {
        return QUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    queue_ptr new_queue = malloc(sizeof(queue_t));
    if (new_queue == NULL) {
        *queue = NULL;
        return QUEUE_ERROR_ALLOC_FAILED;
    }
    uint8_t result = queue_init(new_queue, capacity, element_size);
    switch(result) {
        case QUEUE_ERROR_OK:
            *queue = new_queue;
        case QUEUE_ERROR_NULL_POINTER_RECEIVED:
            *queue = NULL;
        case QUEUE_ERROR_ALLOC_FAILED:
            *queue = NULL;
            free(new_queue);
        default:
            // this should not happen
            *queue = NULL;
    }
    return result;
}

void * queue_front(queue_ptr queue) {
    if (queue == NULL) {
        return NULL;
    }
    return queue->len != 0 ? queue->elements[0] : NULL;
}

queue_error_t queue_push_front(queue_ptr queue, void * elem) {
    if (queue == NULL) {
        return QUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    if (elem == NULL) {
        return QUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    // if the queue is full, allocate for one more element
    if (queue->len == queue->capacity) {
        queue_error_t err = queue_resize(queue, queue->capacity + 1);
        if (!QUEUE_ERROR_IS_OK(err)) {
            return err;
        }
    }
    memmove(queue->elements + sizeof(void *), queue->elements, queue->len);
    queue->elements[0] = elem;
    queue->len += 1;
    return QUEUE_ERROR_OK;
}

queue_error_t queue_push_front_copy(queue_ptr queue, void * elem) {
    if (queue == NULL) {
        return QUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    if (elem == NULL) {
        return QUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    void * elem_copy = malloc(sizeof(queue->element_size));
    if (elem_copy == NULL) {
        return QUEUE_ERROR_ALLOC_FAILED;
    }
    memcpy(elem_copy, elem, queue->element_size);
    queue_error_t err = queue_push_front(queue, elem_copy);
    if (!QUEUE_ERROR_IS_OK(err)) {
        free(elem_copy);
        return err;
    }
    return QUEUE_ERROR_OK;
}

void * queue_pop_front(queue_ptr queue) {
    if (queue == NULL) {
        return NULL;
    }
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
    if (queue == NULL) {
        return NULL;
    }
    return queue->len != 0 ? queue->elements[queue->len - 1] : NULL;
}

queue_error_t queue_push_back(queue_ptr queue, void * elem) {
    if (queue == NULL) {
        return QUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    if (elem == NULL) {
        return QUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    // if the queue is full, allocate for one more element
    if (queue->len == queue->capacity) {
        queue_error_t err = queue_resize(queue, queue->capacity + 1);
        if (!QUEUE_ERROR_IS_OK(err)) {
            return err;
        }
    }
    queue->elements[queue->len] = elem;
    queue->len += 1;
    return QUEUE_ERROR_OK;
}

queue_error_t queue_push_back_copy(queue_ptr queue, void * elem) {
    if (queue == NULL) {
        return QUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    if (elem == NULL) {
        return QUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    void * elem_copy = malloc(sizeof(queue->element_size));
    if (elem_copy == NULL) {
        return QUEUE_ERROR_ALLOC_FAILED;
    }
    memcpy(elem_copy, elem, queue->element_size);
    queue_error_t err = queue_push_back(queue, elem_copy);
    if (!QUEUE_ERROR_IS_OK(err)) {
        free(elem_copy);
        return err;
    }
    return QUEUE_ERROR_OK;
}

void * queue_pop_back(queue_ptr queue) {
    if (queue == NULL) {
        return NULL;
    }
    if (queue->len == 0) {
        return NULL;
    }
    void * elem = queue->elements[queue->len - 1];
    queue->elements[queue->len - 1] = NULL;
    queue->len -= 1;
    return elem;
}

queue_error_t queue_resize(queue_ptr queue, size_t capacity) {
    if (queue == NULL) {
        return QUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    if (capacity == 0) {
        return QUEUE_ERROR_ZERO_CAPACITY_RESIZE;
    }
    if (capacity == queue->capacity) {
        return QUEUE_ERROR_OK;
    }

    // intermediate buffer for either truncated items or extension items
    void ** buf = NULL;
    // if the length is < -1 then the items must be freed
    // otherwise, the items must be added at the end of the future queue
    ssize_t buf_len = 0;

    // if the future capacity is less than the current length of the queue, add items that shall be
    // removed in the intermediate buffer
    if (capacity < queue->len) {
        buf_len = queue->len - queue->capacity;
        buf = malloc(buf_len * sizeof(void *));
        if (buf == NULL) {
            return QUEUE_ERROR_ALLOC_FAILED;
        }
        void ** surplus_start = queue->elements + (capacity - 1) * sizeof(void *);
        memcpy(buf, surplus_start, buf_len);
        buf_len *= -1;
    } else if (capacity > queue->capacity) {
        buf_len = capacity - queue->capacity;
        buf = malloc(buf_len * sizeof(void *));
        if (buf == NULL) {
            return QUEUE_ERROR_ALLOC_FAILED;
        }
        memset(buf, 0, buf_len * sizeof(void *));
    }

    void ** elements_new = realloc(queue->elements, capacity * sizeof(void *));
    if (elements_new == NULL) {
        if (buf != NULL) {
            free(buf);
        }
        return QUEUE_ERROR_ALLOC_FAILED;
    }
    queue->elements = elements_new;
    queue->capacity = capacity;

    if (buf_len < 0) {
        buf_len *= -1;
        for (size_t i = 0; i < buf_len; i++) {
            free(buf[i]);
        }
        free(buf);
    } else if (buf_len > 0) {
        memcpy(queue->elements + queue->len, buf, buf_len * sizeof(void *));
        free(buf);
    }

    return QUEUE_ERROR_OK;
}

queue_error_t queue_empty(queue_ptr queue) {
    if (queue == NULL) {
        return QUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    if (queue->len == 0) {
        return QUEUE_ERROR_OK;
    }
    for (size_t i = 0; i < queue->len; i++) {
        memset(queue->elements[i], 0, queue->element_size);
    }
    queue->len = 0;
    return QUEUE_ERROR_OK;
}

queue_error_t queue_free(queue_ptr queue) {
    if (queue == NULL) {
        return QUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    for (size_t i = 0; i < queue->len; i++) {
        free(queue->elements[i]);
    }
    free(queue->elements);
    queue->capacity = 0;
    queue->len = 0;
    return QUEUE_ERROR_OK;
}
