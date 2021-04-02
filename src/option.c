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

#include "option.h"

option_t option_new(option_e type, void * value) {
    option_t option;
    option.type = type;
    if (type == OPTION_SOME) {
        option.value = value;
    }
    return option;
}

option_ptr option_new_ptr(option_e type, void * value) {
    option_ptr option = malloc(sizeof(option_t));
    option->type = type;
    if (type == OPTION_SOME) {
        option->value = value;
    }
    return option;
}

option_t option_none() {
    return option_new(OPTION_NONE, NULL);
}

option_ptr option_ptr_none() {
    return option_new_ptr(OPTION_NONE, NULL);
}

option_t option_some(void * value) {
    return option_new(OPTION_SOME, value);
}

option_ptr option_ptr_some(void * value) {
    return option_new_ptr(OPTION_SOME, value);
}

uint8_t option_is_none(option_ptr option) {
    return option->type == OPTION_NONE;
}

uint8_t option_is_some(option_ptr option) {
    return option->type == OPTION_SOME;
}

void option_free(option_ptr option) {
    if (option_is_some(option)) {
        free(option->value);
    }
}
