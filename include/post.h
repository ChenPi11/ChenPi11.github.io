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

#define TITLE_START "<!-- title: "
#define TITLE_END " -->"
#define DATE_START "<!-- date: "
#define DATE_END " -->"
#define TAG_START "<!-- tag: "
#define TAG_END " -->"
#define TAGS_SEP ","
#define DESC_START "<!-- desc: "
#define DESC_END " -->"
#define LICENSE_START "<!-- license: "
#define LICENSE_END " -->"
#define POST_OUTPUT_DIR "posts/"

/* Tags. */
struct tags_t
{
    /* The first element of the array. */
    struct content_t *first;

    /* The number of elements in the array. */
    size_t num;
};

/* Null tags. */
#define null_tags (struct tags_t){.first = NULL, .num = 0}

/* Post. */
struct post_t
{
    /* The post's file stem name. */
    struct content_t filename;

    /* The post's title. */
    struct content_t title;

    /* The post's publish date. */
    struct content_t date;

    /* The post's markdown content. */
    struct content_t content;

    /* The post's tags. */
    struct tags_t tags;

    /* The post's description */
    struct content_t description;

    /* The posts's license */
    struct content_t license;

    /* The post's last modified time. */
    struct content_t last_modified;
};

/* Null post. */
#define null_post                                                                                                      \
    (struct post_t)                                                                                                    \
    {                                                                                                                  \
        .filename = null_content, .title = null_content, .date = null_content, .content = null_content,                \
        .tags = null_tags, .description = null_content, .license = null_content, .last_modified = null_content         \
    }

/* Checking if the post is null post. Return TRUE if it is. FALSE otherwise. */
#define is_null_post(x) ((x).filename.content == NULL)

/* Initialize the post module. */
extern void post_init(const char *template_file);

/* Load the post from file. */
extern struct post_t load_post(const char *filepath);

/* Save the post's meta to file. */
extern int save_post_meta(struct post_t post, const char *postinfo_filename);

/* Get the post's info HTML from file. */
extern struct content_t get_post_info(const char *filepath, const char *tmp_filename);

/* Save the post to file. */
extern int save_post(struct post_t post);

/* Free the tags. */
extern void free_tags(struct tags_t *tags);

/* Free the post. */
extern void free_post(struct post_t *post);

#endif
