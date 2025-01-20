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
#ifndef _POST_H_
#define _POST_H_

#include "content.h"

#include <stddef.h>

#define TITLE_START "# "
#define DATE_START "<!-- date: "
#define DATE_END " -->"
#define TAG_START "<!-- tag: "
#define TAG_END " -->"
#define TAGS_SEP ","
#define POST_OUTPUT_DIR "posts/"

struct tags_t
{
    struct content_t *first;
    size_t num;
};

struct post_t
{
    struct content_t filename;
    struct content_t title;
    struct content_t date;
    struct content_t content; // The post's markdown content.
    struct tags_t tags;
};

extern void post_init(const char *template_file);

extern struct post_t load_post(const char *filepath);

extern void save_post(struct post_t post);

extern void free_tags(struct tags_t *tags);

extern void free_post(struct post_t *post);

#endif
