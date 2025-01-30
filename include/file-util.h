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
#ifndef _FILE_UTIL_H_
#define _FILE_UTIL_H_

#include "content.h"
#include "defines.h"

#include <stddef.h>
#include <stdio.h>

EXTERN_C_BEG

/* Return TRUE if the path exists. FALSE otherwise.  */
extern int exists(const char *path);

/* Return TRUE if the path is a regular file. FALSE otherwise.  */
extern int is_file(const char *path);

/* Return TRUE if the path is a directory. FALSE otherwise.  */
extern int is_dir(const char *path);

/* Get the file size. Return (size_t)(-1) if failed. */
extern size_t get_file_size(const char *path);

/* Remove a file or an empty directory. Return RET_SUCCESS if success. RET_ERROR otherwise. */
extern int remove_file(const char *path);

/* Checking if the current working directory is ChenPi11's blog root directory.
   Return TRUE if it is. FALSE otherwise. */
extern int is_chenpi11_blog_rootdir(void);

/* Read all data from a file to a content. Return null content if failed. */
extern struct content_t read_file(const char *path);

/* Read a line from a file stream. Return null content if failed. */
extern struct content_t read_line(FILE *file, const char *path);

/* Get the file's basename. file_basename("/a/b.c") -> "b.c" */
extern const char *file_basename(const char *path);

/* Copy a file. Return RET_SUCCESS if success. RET_ERROR otherwise. */
extern int copy_file(const char *src, const char *dst);

/* Close a file stream, and set it to NULL. */
#define close_file(file)                                                                                               \
    do                                                                                                                 \
    {                                                                                                                  \
        if (file != NULL)                                                                                              \
        {                                                                                                              \
            fclose(file);                                                                                              \
        }                                                                                                              \
        file = NULL;                                                                                                   \
    } while (0)

EXTERN_C_END

#endif
