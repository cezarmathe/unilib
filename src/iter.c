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

#include <stdlib.h>

#include "iter.h"

iter_t iter_new(void * data, iter_next_ptr next, iter_free_ptr free) {
    iter_t iter;
    iter.data = data;
    iter.next = next;
    iter.free = free;
    return iter;
}

iter_ptr iter_new_ptr(void * data, iter_next_ptr next, iter_free_ptr free) {
    iter_ptr iter = malloc(sizeof(iter_t));
    if (iter == NULL) {
        return NULL;
    }
    iter->data = data;
    iter->next = next;
    iter->free = free;
    return iter;
}

void * iter_next(iter_ptr iter) {
    return iter->next(iter->data);
}

size_t iter_advance_by(iter_ptr iter, size_t count) {
    size_t advanced_by = 0;
    while (advanced_by < count) {
        if (iter_next(iter) != NULL) {
            advanced_by += 1;
        } else {
            break;
        }
    }
    return advanced_by;
}

size_t iter_count(iter_ptr iter) {
    size_t count = 0;
    while (iter_next(iter) != NULL) {
        count += 1;
    }
    return count;
}

void iter_free(iter_ptr iter) {
    iter->free(iter->data);
}
