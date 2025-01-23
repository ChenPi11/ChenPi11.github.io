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

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Return 1 if the path exists. 0 otherwise.  */
extern int exists(const char *path);

/* Return 1 if the path is a regular file. 0 otherwise.  */
extern int is_file(const char *path);

/* Return 1 if the path is a directory. 0 otherwise.  */
extern int is_dir(const char *path);

/* Get the file size. Return (size_t)(-1) if failed. */
extern size_t get_file_size(const char *path);

/* Remove a file or an empty directory. Return 0 if success. 0 otherwise. */
extern int remove_file(const char *path);

/* Checking if he current path is ChenPi11's blog root directory. Return 1 if it is. 0 otherwise. */
extern int is_chenpi11_blog_rootdir(void);

#ifdef __cplusplus
}
#endif

#endif
