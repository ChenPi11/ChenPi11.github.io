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

#include "file-util.h"

#include "content.h"
#include "i18n.h"
#include "log.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int exists(const char *path)
{
    struct stat path_stat;

    init_struct(path_stat);

    return stat(path, &path_stat) == 0;
}

int is_file(const char *path)
{
    struct stat path_stat;

    init_struct(path_stat);

    return stat(path, &path_stat) == 0 && S_ISREG(path_stat.st_mode);
}

int is_dir(const char *path)
{
    struct stat path_stat;

    init_struct(path_stat);

    return stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode);
}

int remove_file(const char *path)
{
    return remove(path);
}

size_t get_file_size(const char *path)
{
    struct stat path_stat;

    init_struct(path_stat);

    return stat(path, &path_stat) == 0 ? (size_t)path_stat.st_size : (size_t)(-1);
}

#define CHECK(x)                                                                                                       \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            goto NOT;                                                                                                  \
        }                                                                                                              \
    } while (FALSE)

int is_chenpi11_blog_rootdir(void)
{
    CHECK(is_dir("."));
    CHECK(is_file("requirements.txt") && is_file("pyproject.toml")); /* It's a Python project. */
    CHECK(is_file("Cargo.toml") && is_file("Makefile.toml"));        /* It's a Rust project. */
    CHECK(is_file("configure.ac") && is_file("autogen.sh"));         /* It's an Autotools project. */
    CHECK(is_file("CMakeLists.txt"));                                /* It's a CMake project. */
    CHECK(is_file("package.json"));                                  /* It's a Node.js project. */
    CHECK(is_file("Makefile.in"));                                   /* It's an Autoconf+Makefile project. */
    CHECK(is_file("repo.json"));                                     /* It's a Rubisco project. */

    errno = 0;

    return TRUE;

NOT:
    errno = 0;

    return FALSE;
}

struct content_t read_file(const char *path)
{
    size_t file_size = 0;
    struct content_t content = null_content;
    FILE *file = NULL;

    file_size = get_file_size(path);
    if (file_size == (size_t)(-1))
    {
        return null_content;
    }

    content = alloc_content(file_size);
    if (is_null_content(content))
    {
        return null_content;
    }

    file = fopen(path, "r");
    if (file == NULL)
    {
        die(_("Cannot open file: %s\n"), path);
    }

    if (fread(content.content, content.len, 1, file) != 1)
    {
        fclose(file);
        free_content(&content);
        die(_("I/O Error: %s.\n"), path);
    }
    if (ferror(file) != 0 && fclose(file) != 0)
    {
        free_content(&content);
        die(_("I/O Error: %s.\n"), path);
    }

    return content;

ERROR:
    close_file(file);
    free_content(&content);

    return null_content;
}

struct content_t read_line(FILE *file, const char *path)
{
    struct content_t content = null_content;
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    read = getline(&line, &len, file);
    if (read == -1)
    {
        if (feof(file))
        {
            die(_("EOF reached.\n"));
        }
        else
        {
            die(_("Cannot getline: %s\n"), path);
        }
    }

    if (line[read - 1] == '\n')
    {
        line[read - 1] = '\0';
    }

    content.len = (size_t)read - 1;
    content.content = line;
    content.is_static = FALSE;

    return content;

ERROR:
    content.content = line;
    free_content(&content);

    return null_content;
}

const char *file_basename(const char *path)
{
    const char *slash = NULL;

    slash = strrchr(path, '/');
    if (slash)
    {
        return slash + 1;
    }

    return path;
}

int copy_file(const char *from, const char *to)
{
    FILE *from_file = NULL;
    size_t from_size = 0;
    FILE *to_file = NULL;
    char buffer[BUFSIZ];
    size_t read = 0;

    init_struct(buffer);

    from_file = fopen(from, "rb");
    if (from_file == NULL)
    {
        die(_("Cannot open file: %s\n"), from);
    }

    from_size = get_file_size(from);
    if (from_size == (size_t)(-1))
    {
        die(_("Cannot get file size: %s\n"), from);
    }

    to_file = fopen(to, "wb");
    if (to_file == NULL)
    {
        die(_("Cannot open file: %s\n"), to);
    }

    while ((read = fread(buffer, sizeof(char), BUFSIZ, from_file)) > 0)
    {
        fwrite(buffer, sizeof(char), read, to_file);
    }

    close_file(from_file);
    close_file(to_file);

    return RET_SUCCESS;

ERROR:
    close_file(from_file);
    close_file(to_file);

    return RET_ERROR;
}
