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

#include <stddef.h>
#include <string.h>

struct content_t
{
    char *content;
    size_t len;
};

extern struct content_t alloc_content(void);

extern int is_null_content(void);

extern struct content_t read_file(const char *path);

extern void free_content(struct content_t *content);

#define init_struct(x) memset(&(x), 0, sizeof(x))

#endif
