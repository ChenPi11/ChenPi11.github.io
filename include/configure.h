/*
 * Copyright (C) 2025 ChenPi11
 * This file is part of the chenpi11-blog.
 *
 * chenpi11-blog is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * chenpi11-blog is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with chenpi11-blog.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once
#ifndef _CONFIGURE_H_
#define _CONFIGURE_H_

#include "content.h"
#include "defines.h"

#include <stddef.h>

EXTERN_C_BEG

/* Configure key-value pair. */
struct configure_t
{
    /* Key. */
    struct content_t key;

    /* Value. */
    struct content_t value;
};

#define PAIR(k, v)                                                                                                     \
    (struct configure_t)                                                                                               \
    {                                                                                                                  \
        .key = static_content(k), .value = static_content(v)                                                                         \
    }

/* Configure key-value pairs. Use create_configures() to create. */
struct configures_t
{
    /* The first element of the array. */
    struct configure_t *first;

    /* The number of elements in the array. */
    size_t num;
};

/* Create configures_t. */
#define create_configures(array)                                                                                       \
    (struct configures_t)                                                                                              \
    {                                                                                                                  \
        .first = array, .num = sizeof(array) / sizeof(struct configure_t)                                              \
    }

/* Configure a file with configures. All @{key}@ will be replaced with {value}.
   Return RET_SUCCESS if succeed. RET_ERROR otherwise. */
extern int configure(struct configures_t configs, const char *filepath);

EXTERN_C_END

#endif
