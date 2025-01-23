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

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int exists(const char *path)
{
    struct stat path_stat;

    return stat(path, &path_stat) == 0;
}

int is_file(const char *path)
{
    struct stat path_stat;

    return stat(path, &path_stat) == 0 && S_ISREG(path_stat.st_mode);
}

int is_dir(const char *path)
{
    struct stat path_stat;

    return stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode);
}

int remove_file(const char *path)
{
    return remove(path);
}

#define CHECK(x) if (!(x)) goto NOT

int is_chenpi11_blog_rootdir(void)
{
    CHECK(is_dir("."));
    CHECK(is_file("requirements.txt") && is_file("pyproject.toml"));
    CHECK(is_file("Cargo.toml") && is_file("Makefile.toml"));
    CHECK(is_file("configure.ac") && is_file("autogen.sh"));
    CHECK(is_file("CMakeLists.txt"));
    CHECK(is_file("package.json"));

    return 1;
NOT:
    return 0;
}
