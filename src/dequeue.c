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

#include "dequeue.h"

/**
 * Initialize a dequeue.
 *
 * @details If the passed dequeue pointer is NULL, this leads to UB!
 *
 * @param dequeue the dequeue to initialize
 * @param capacity the capacity of the dequeue
 * @param element_size the size of each element in the dequeue
 *
 * @return DEQUEUE_ERROR_OK if successful
 *         DEQUEUE_ERROR_NULL_POINTER_RECEIVED if the dequeue pointer is NULL
 *         DEQUEUE_ERROR_ALLOC_FAILED if allocating the elements array failed
 */
static dequeue_error_t dequeue_init(dequeue_ptr dequeue, size_t capacity, size_t element_size) {
    dequeue->elements = calloc(capacity, sizeof(void *));
    if (dequeue->elements == NULL) {
        return DEQUEUE_ERROR_ALLOC_FAILED;
    }
    dequeue->capacity = capacity;
    dequeue->len = 0;
    dequeue->element_size = element_size;
    return DEQUEUE_ERROR_OK;
}

dequeue_error_t dequeue_new(dequeue_ptr dequeue, size_t element_size) {
    return dequeue_new_with_capacity(dequeue, DEQUEUE_DEFAULT_CAPACITY, element_size);
}

dequeue_error_t dequeue_new_ptr(dequeue_ptr * dequeue, size_t element_size) {
    return dequeue_new_ptr_with_capacity(dequeue, DEQUEUE_DEFAULT_CAPACITY, element_size);
}

dequeue_error_t dequeue_new_with_capacity(dequeue_ptr dequeue, size_t capacity, size_t element_size) {
    if (dequeue == NULL) {
        return DEQUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    return dequeue_init(dequeue, capacity, element_size);
}

dequeue_error_t dequeue_new_ptr_with_capacity(dequeue_ptr * dequeue, size_t capacity, size_t element_size) {
    if (dequeue == NULL) {
        return DEQUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    dequeue_ptr new_dequeue = malloc(sizeof(dequeue_t));
    if (new_dequeue == NULL) {
        *dequeue = NULL;
        return DEQUEUE_ERROR_ALLOC_FAILED;
    }
    dequeue_error_t result = dequeue_init(new_dequeue, capacity, element_size);
    switch(result) {
        case DEQUEUE_ERROR_OK:
            *dequeue = new_dequeue;
            break;
        case DEQUEUE_ERROR_NULL_POINTER_RECEIVED:
            *dequeue = NULL;
            break;
        case DEQUEUE_ERROR_ALLOC_FAILED:
            free(new_dequeue);
            *dequeue = NULL;
            break;
        default:
            // this should not happen
            *dequeue = NULL;
            break;
    }
    return result;
}

void * dequeue_front(dequeue_ptr dequeue) {
    if (dequeue == NULL) {
        return NULL;
    }
    return dequeue->len != 0 ? dequeue->elements[0] : NULL;
}

dequeue_error_t dequeue_push_front(dequeue_ptr dequeue, void * elem) {
    if (dequeue == NULL) {
        return DEQUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    if (elem == NULL) {
        return DEQUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    // if the dequeue is full, allocate for one more element
    if (dequeue->len == dequeue->capacity) {
        dequeue_error_t err = dequeue_resize(dequeue, dequeue->capacity + 1);
        if (!DEQUEUE_ERROR_IS_OK(err)) {
            return err;
        }
    }
    memmove(dequeue->elements + sizeof(void *), dequeue->elements, dequeue->len);
    dequeue->elements[0] = elem;
    dequeue->len += 1;
    return DEQUEUE_ERROR_OK;
}

dequeue_error_t dequeue_push_front_copy(dequeue_ptr dequeue, void * elem) {
    if (dequeue == NULL) {
        return DEQUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    if (elem == NULL) {
        return DEQUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    void * elem_copy = malloc(sizeof(dequeue->element_size));
    if (elem_copy == NULL) {
        return DEQUEUE_ERROR_ALLOC_FAILED;
    }
    memcpy(elem_copy, elem, dequeue->element_size);
    dequeue_error_t err = dequeue_push_front(dequeue, elem_copy);
    if (!DEQUEUE_ERROR_IS_OK(err)) {
        free(elem_copy);
        return err;
    }
    return DEQUEUE_ERROR_OK;
}

void * dequeue_pop_front(dequeue_ptr dequeue) {
    if (dequeue == NULL) {
        return NULL;
    }
    if (dequeue->len == 0) {
        return NULL;
    }
    void * elem = dequeue->elements[0];
    if (dequeue->len > 1) {
        memmove(dequeue->elements, dequeue->elements + sizeof(void *), dequeue->len - 1);
    }
    dequeue->elements[dequeue->len - 1] = NULL;
    dequeue->len -= 1;
    return elem;
}

void * dequeue_back(dequeue_ptr dequeue) {
    if (dequeue == NULL) {
        return NULL;
    }
    return dequeue->len != 0 ? dequeue->elements[dequeue->len - 1] : NULL;
}

dequeue_error_t dequeue_push_back(dequeue_ptr dequeue, void * elem) {
    if (dequeue == NULL) {
        return DEQUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    if (elem == NULL) {
        return DEQUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    // if the dequeue is full, allocate for one more element
    if (dequeue->len == dequeue->capacity) {
        dequeue_error_t err = dequeue_resize(dequeue, dequeue->capacity + 1);
        if (!DEQUEUE_ERROR_IS_OK(err)) {
            return err;
        }
    }
    dequeue->elements[dequeue->len] = elem;
    dequeue->len += 1;
    return DEQUEUE_ERROR_OK;
}

dequeue_error_t dequeue_push_back_copy(dequeue_ptr dequeue, void * elem) {
    if (dequeue == NULL) {
        return DEQUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    if (elem == NULL) {
        return DEQUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    void * elem_copy = malloc(sizeof(dequeue->element_size));
    if (elem_copy == NULL) {
        return DEQUEUE_ERROR_ALLOC_FAILED;
    }
    memcpy(elem_copy, elem, dequeue->element_size);
    dequeue_error_t err = dequeue_push_back(dequeue, elem_copy);
    if (!DEQUEUE_ERROR_IS_OK(err)) {
        free(elem_copy);
        return err;
    }
    return DEQUEUE_ERROR_OK;
}

void * dequeue_pop_back(dequeue_ptr dequeue) {
    if (dequeue == NULL) {
        return NULL;
    }
    if (dequeue->len == 0) {
        return NULL;
    }
    void * elem = dequeue->elements[dequeue->len - 1];
    dequeue->elements[dequeue->len - 1] = NULL;
    dequeue->len -= 1;
    return elem;
}

dequeue_error_t dequeue_resize(dequeue_ptr dequeue, size_t capacity) {
    if (dequeue == NULL) {
        return DEQUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    if (capacity == 0) {
        return DEQUEUE_ERROR_ZERO_CAPACITY_RESIZE;
    }
    if (capacity == dequeue->capacity) {
        return DEQUEUE_ERROR_OK;
    }

    // intermediate buffer for either truncated items or extension items
    void ** buf = NULL;
    // if the length is < -1 then the items must be freed
    // otherwise, the items must be added at the end of the future dequeue
    ssize_t buf_len = 0;

    // if the future capacity is less than the current length of the dequeue, add items that shall be
    // removed in the intermediate buffer
    if (capacity < dequeue->len) {
        buf_len = dequeue->len - dequeue->capacity;
        buf = malloc(buf_len * sizeof(void *));
        if (buf == NULL) {
            return DEQUEUE_ERROR_ALLOC_FAILED;
        }
        void ** surplus_start = dequeue->elements + (capacity - 1) * sizeof(void *);
        memcpy(buf, surplus_start, buf_len);
        buf_len *= -1;
    } else if (capacity > dequeue->capacity) {
        buf_len = capacity - dequeue->capacity;
        buf = malloc(buf_len * sizeof(void *));
        if (buf == NULL) {
            return DEQUEUE_ERROR_ALLOC_FAILED;
        }
        memset(buf, 0, buf_len * sizeof(void *));
    }

    void ** elements_new = realloc(dequeue->elements, capacity * sizeof(void *));
    if (elements_new == NULL) {
        if (buf != NULL) {
            free(buf);
        }
        return DEQUEUE_ERROR_ALLOC_FAILED;
    }
    dequeue->elements = elements_new;
    dequeue->capacity = capacity;

    if (buf_len < 0) {
        buf_len *= -1;
        for (size_t i = 0; i < buf_len; i++) {
            free(buf[i]);
        }
        free(buf);
    } else if (buf_len > 0) {
        memcpy(dequeue->elements + dequeue->len, buf, buf_len * sizeof(void *));
        free(buf);
    }

    return DEQUEUE_ERROR_OK;
}

dequeue_error_t dequeue_empty(dequeue_ptr dequeue) {
    if (dequeue == NULL) {
        return DEQUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    if (dequeue->len == 0) {
        return DEQUEUE_ERROR_OK;
    }
    for (size_t i = 0; i < dequeue->len; i++) {
        memset(dequeue->elements[i], 0, dequeue->element_size);
    }
    dequeue->len = 0;
    return DEQUEUE_ERROR_OK;
}

dequeue_error_t dequeue_free(dequeue_ptr dequeue) {
    if (dequeue == NULL) {
        return DEQUEUE_ERROR_NULL_POINTER_RECEIVED;
    }
    for (size_t i = 0; i < dequeue->len; i++) {
        free(dequeue->elements[i]);
    }
    free(dequeue->elements);
    dequeue->capacity = 0;
    dequeue->len = 0;
    return DEQUEUE_ERROR_OK;
}
