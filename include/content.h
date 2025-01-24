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
#ifndef _CONTENT_H_
#define _CONTENT_H_

#include "defines.h"

#include <stddef.h>
#include <string.h>

EXTERN_C_BEG

/* String data with length. */
struct content_t
{
    /* The pointer of the first element of the string. NULL means null content. */
    char *content;

    /* The length of the string. */
    size_t len;

    /* TRUE if the content is static. */
    int is_static;
};

/* Make a static from literal. */
#define CONTENT(str)                                                                                                   \
    (struct content_t)                                                                                                 \
    {                                                                                                                  \
        .content = (str), .len = (sizeof(str) - 1) / sizeof(char), .is_static = TRUE                                   \
    }

/* Make a static content. Don't write it. */
extern struct content_t static_content(const char *source);

/* Allocate a content from string. Must be free using free_content(). Return null content if allocate failed. */
extern struct content_t alloc_content(size_t length);

/* Checking if the content is null content. Return TRUE if it is. FALSE otherwise. */
#define is_null_content(x) ((x).content == NULL)

/* Free the content data and set it to null. Do nothing if content is NULL. */
extern void free_content(struct content_t *content);

/* Checking if the content is start with the given content. Return TRUE if it is. FALSE otherwise. */
extern int startswith(const struct content_t content, const struct content_t prefix);

/* Checking if the content is end with the given content. Return TRUE if it is. FALSE otherwise.*/
extern int endswith(const struct content_t content, const struct content_t suffix);

/* Remove the space from the start of the content. */
extern int lstrip(struct content_t *content);

/* Remove the space from the end of the content. */
extern int rstrip(struct content_t *content);

/* Remove the space from the start and end of the content. */
extern int strip(struct content_t *content);

/* Initialize a struct to 0. */
#define init_struct(x) memset(&(x), 0, sizeof(x))

/* Null content. */
#define null_content                                                                                                   \
    (struct content_t)                                                                                                 \
    {                                                                                                                  \
        .content = NULL, .len = 0, .is_static = TRUE                                                                   \
    }

EXTERN_C_END

#endif
