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

#include <content.h>

#include <log.h>

#include <malloc.h>
#include <stdio.h>
#include <sys/stat.h>

struct content_t read_file(const char *path)
{
    struct content_t content;
    struct stat file_stat;
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        die("Cannot open file: %s\n", path);
    }
    if (stat(path, &file_stat) == -1)
    {
        fclose(file);
        die("Cannot stat file %s\n", path);
    }
    content.len = (size_t)file_stat.st_size;
    content.content = malloc(content.len);
    if (content.content == NULL)
    {
        fclose(file);
        die("Cannot allocate memory.\n");
    }
    if (fread(content.content, content.len, 1, file) != 1)
    {
        fclose(file);
        free(content.content);
        die("I/O Error: %s.\n", path);
    }
    if (fclose(file) != 0)
    {
        free(content.content);
        die("I/O Error: %s.\n", path);
    }

    return content;
}

void free_content(struct content_t *content)
{
    if (content == NULL)
    {
        return;
    }
    free(content->content);
    content->content = NULL;
    content->len = 0;
}
